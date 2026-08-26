#include "solver.hpp"

SolverException::SolverException(const char* msg) : msg(msg) {};

const char* SolverException::what() const throw() {
    return this->msg;
};

FixedStepsizeSolver::FixedStepsizeSolver(FixedStepsizeSolverType type, ODE ode) : type(type), ode(ode), t(0.0) {};

void FixedStepsizeSolver::setInitialConditions(std::vector <double> initial, double t0) {
    this->current = initial;
    this->t = t0;
};

DoubleVector FixedStepsizeSolver::getCurrentSolution() {
    return this->current;
};

std::ostream& operator<<(std::ostream &strm, const FixedStepsizeSolver& fss) {
    strm << "Fixed stepsize solver of type ";

    switch(fss.type) {
        case FixedStepsizeSolverType::EULER:
            strm << "'Euler'";
            break;
        case FixedStepsizeSolverType::RK4:
            strm << "'Runge-Kutta 4'";
            break;
        case FixedStepsizeSolverType::AdamBash:
            strm << "'Adams-Bashforth'";
            break;     
        default:
            strm << "Unknown";
            break;
    };

    return strm << std::endl;
};

EulerSolver::EulerSolver(ODE ode) : FixedStepsizeSolver(FixedStepsizeSolverType::EULER, ode) {};

void EulerSolver::step(double stepsize) {
    this->t += stepsize; 
    DoubleVector next = this->ode(this->t, this->current);

    this->current += stepsize * next;
};

BackwardEulerSolver::BackwardEulerSolver(ODE ode) : FixedStepsizeSolver(FixedStepsizeSolverType::EULER, ode) {};

void BackwardEulerSolver::step(double stepsize) {
    // y_n+1 = y_n + f(t_n+1, y_n+1)
    // g(y_n+1) = f(t_n+1, y_n+1) + y_n
    // y_n+1 = g(y_n+1) 

    // the initial guess for the method is calculated by a forward Euler step
    DoubleVector guess = this->current + stepsize*this->ode(this->t, this->current);

    // t_n -> t_n+1
    this->t += stepsize;

    // define g
    auto g = [this, stepsize](const DoubleVector& guess) {
        return this->current + stepsize*this->ode(this->t, guess); 
    };

    // fixpoint iteration
    for (int i = 0; i < BackwardEulerSolver::MAX_ITERATION_STEPS; i++) {
        bool converged = true;
        
        DoubleVector next_guess = g(guess);
        
        // convergence check
        for (unsigned int j = 0; j < guess.size(); j++) {
            if (std::abs(next_guess[j] - guess[j]) > BackwardEulerSolver::MAX_ERROR) {
                converged = false;
                break;
            }
        }

        guess = next_guess;

        if (converged == true)
            break;
    }

    this->current = guess;
};

RK4Solver::RK4Solver(ODE ode) : FixedStepsizeSolver(FixedStepsizeSolverType::RK4, ode) {};

void RK4Solver::step(double stepsize) {
    DoubleVector k1 = this->ode(this->t, this->current);
    DoubleVector k2 = this->ode(this->t + stepsize/2, this->current + k1*stepsize/2);
    DoubleVector k3 = this->ode(this->t + stepsize/2, this->current + k2*stepsize/2);
    DoubleVector k4 = this->ode(this->t + stepsize, this->current + k3 * stepsize);

    this->current += stepsize * this->constants[0] * k1;
    this->current += stepsize * this->constants[1] * k2;
    this->current += stepsize * this->constants[2] * k3;
    this->current += stepsize * this->constants[3] * k4;

    this->t += stepsize;
};

AdamsBashforthSolver::AdamsBashforthSolver(ODE ode, unsigned int s) : FixedStepsizeSolver(FixedStepsizeSolverType::AdamBash, ode) {
    if (s < 1 || s > 5) 
        throw SolverException("Invalid argument: s for Adams-Bashforth must be between 1 and 5!");
    
    this->priorValues = VectorContainer(s - 1);
    this->s = s;

    switch(s) {
        case 1:
            this->constants = AdamsBashforthSolver::s1;
            break;
        case 2:
            this->constants = AdamsBashforthSolver::s2;
            break;
        case 3:
            this->constants = AdamsBashforthSolver::s3;
            break;
        case 4:
            this->constants = AdamsBashforthSolver::s4;
            break;
        case 5:
            this->constants = AdamsBashforthSolver::s5;
            break;
    }
};

void AdamsBashforthSolver::step(double stepsize) {
    // the values in the container are in the descending order, 
    // i.e. index 0: y_n+s (e.g. s = 5), index 1: y_n+s-1, ..., index s-2: y_n
    // e.g. s = 3:
    // index 0: y_2; index 1: y_1 

    bool full_history_available = true;
    unsigned int s = this->s;
    DoubleVector prior;

    // 1. Check if all values in the container are non-empty
    // if there is at least one further Euler step
    for (int i = s-2; i >= 0; i--) {
        prior = this->priorValues.getItem(i);
        if (prior.size() == 0) {
            full_history_available = false;

            this->priorValues.setItem(i, this->current);
            
            DoubleVector next = this->ode(this->t, this->current);
            this->current += stepsize*next;
            break;
        }
    }

    // 2. Perform the Adams-Bashforth steps
    if (full_history_available == true) {
        DoubleVector next = this->current;
        DoubleVector f;
        double t = this->t;
        double c;

        // perform the steps
        for (unsigned int i = 1; i < s; i++) {
            // get f(t_i, y_i)
            f =  this->ode(this->t - i*stepsize, this->priorValues.getItem(i-1));
            // get the respective
            c = this->constants[i];

            // add to the next value
            next += stepsize*c*f;
        }
        next += stepsize*this->constants[0]*this->ode(this->t, this->current);

        // shift the values
        unsigned int idx;
        for (int i = s-2; i >= 1; i--) {
            this->priorValues.setItem(i, this->priorValues.getItem(i - 1));
        }
        this->priorValues.setItem(0, this->current);

        this->current = next;
    }

    this->t += stepsize;
};