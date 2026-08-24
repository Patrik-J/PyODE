#include "solver.hpp"

FixedStepsizeSolver::FixedStepsizeSolver(FixedStepsizeSolverType type, ODE ode) : type(type), ode(ode), t(0.0) {};

void FixedStepsizeSolver::setInitialConditions(std::vector <double> initial, double t0) {
    this->current = initial;
    this->t = t0;
};

std::vector<double> FixedStepsizeSolver::getCurrentSolution() {
    return this->current;
};

std::ostream& operator<<(std::ostream &strm, const FixedStepsizeSolver& fss) {
    strm << "Fixed stepsize solver of type ";

    switch(fss.type) {
        case FixedStepsizeSolverType::EULER:
            strm << "EULER";
            break;
        case FixedStepsizeSolverType::RK4:
            strm << "RK4";
            break;
        default:
            strm << "Unknown";
            break;
    };

    return strm;
};

EulerSolver::EulerSolver(ODE ode) : FixedStepsizeSolver(FixedStepsizeSolverType::EULER, ode) {};

void EulerSolver::step(double stepsize) {
    this->t += stepsize; 
    std::vector<double> next = this->ode(this->t, this->current);

    this->current += stepsize * next;
};

RK4Solver::RK4Solver(ODE ode) : FixedStepsizeSolver(FixedStepsizeSolverType::RK4, ode) {};

void RK4Solver::step(double stepsize) {
    std::vector<double> k1 = this->ode(this->t, this->current);
    std::vector<double> k2 = this->ode(this->t + stepsize/2, this->current + k1*stepsize/2);
    std::vector<double> k3 = this->ode(this->t + stepsize/2, this->current + k2*stepsize/2);
    std::vector<double> k4 = this->ode(this->t + stepsize, this->current + k3 * stepsize);

    this->current += stepsize * this->constants[0] * k1;
    this->current += stepsize * this->constants[1] * k2;
    this->current += stepsize * this->constants[2] * k3;
    this->current += stepsize * this->constants[3] * k4;

    this->t += stepsize;
};