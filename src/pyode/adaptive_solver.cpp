#include "adaptive_solver.hpp"

AdaptiveStepsizeSolver::AdaptiveStepsizeSolver(AdaptiveStepsizeSolverType type, ODE ode) : type(type), ode(ode) {};

void AdaptiveStepsizeSolver::setInitialConditions(std::vector <double> initial, double t0) {
    this->current = initial;
    this->t = t0;
};

DoubleVector AdaptiveStepsizeSolver::getCurrentSolution() {
    return this->current;
};

void AdaptiveStepsizeSolver::setInitialStepsize(double initial_stepsize) {
    this->h = initial_stepsize;
};

double AdaptiveStepsizeSolver::getCurrentTime() {
    return this->t;
};

std::ostream& operator<<(std::ostream &strm, const AdaptiveStepsizeSolver& ass) {
    strm << "Adaptive stepsize solver of type ";

    switch(ass.type) {
        case AdaptiveStepsizeSolverType::RK45:
            strm << "'Runge-Kutta 4(5)'";
            break;  
        default:
            strm << "Unknown";
            break;
    };

    return strm << std::endl;
};

RK45Solver::RK45Solver(ODE ode, double epsilon) : AdaptiveStepsizeSolver(AdaptiveStepsizeSolverType::RK45, ode) {
    this->epsilon = epsilon;
};

void RK45Solver::step() {
    double h = this->h;
    double h_new = h;
    double truncation_error = INFINITY;

    DoubleVector k1;
    DoubleVector k2;
    DoubleVector k3;
    DoubleVector k4;
    DoubleVector k5;
    DoubleVector k6;

    DoubleVector weighted_average;

    while (truncation_error > this->epsilon) {
        // find all k_i's
        k1 = h*this->ode(this->t + this->A(1) * h, this->current);
        k2 = h*this->ode(this->t + this->A(2) * h, this->current + this->B(2, 1) * k1);
        k3 = h*this->ode(this->t + this->A(3) * h, this->current + this->B(3, 1) * k1 + this->B(3, 2) * k2);
        k4 = h*this->ode(this->t + this->A(4) * h, this->current + this->B(4, 1) * k1 + this->B(4, 2) * k2 + this->B(4,3) * k3);
        k5 = h*this->ode(this->t + this->A(5) * h, this->current + this->B(5, 1) * k1 + this->B(5, 2) * k2 + this->B(5,3) * k3 + this->B(5,4) * k4);
        k6 = h*this->ode(this->t + this->A(6) * h, this->current + this->B(6, 1) * k1 + this->B(6, 2) * k2 + this->B(6,3) * k3 + this->B(6,4) * k4 + this->B(6,5) * k4);

        // get the weighted average
        weighted_average = this->current + this->c_hat(1) * k1 + this->c_hat(2) * k2 + this->c_hat(3) * k3 + this->c_hat(4) * k4 + this->c_hat(5) * k5 + this->c_hat(6) * k6;

        // find the truncation error
        DoubleVector err = (this->c_hat(1) - this->c(1)) * k1
        + (this->c_hat(2) - this->c(2)) * k2
        + (this->c_hat(3) - this->c(3)) * k3
        + (this->c_hat(4) - this->c(4)) * k4
        + (this->c_hat(5) - this->c(5)) * k5
        + (this->c_hat(6) - this->c(6)) * k6;

        truncation_error = abs(err);

        // calculate the new stepsize
        h_new = 0.9 * h * pow(this->epsilon/truncation_error, 0.5);

        if (truncation_error <= this->epsilon) 
            break;
        else
            h = h_new;
    }

    this->h = h;
    this->current = weighted_average;
    this->t += h;
};

double RK45Solver::A(unsigned int index) {
    unsigned int idx = index - 1;
    if (idx > 5)
        throw SolverException("Index must be between 1 and 6! Check Butcher tableau for 'A'.");
    return this->butcher_tableau_alpha[idx];
};

double RK45Solver::c_hat(unsigned int index) {
    unsigned int idx = index - 1;
    if (idx > 5)
        throw SolverException("Index must be between 1 and 6! Check Butcher tableau for 'c^'.");
    return this->butcher_tableau_c_hat[idx];
};

double RK45Solver::c(unsigned int index) {
    unsigned int idx = index - 1;
    if (idx > 5)
        throw SolverException("Index must be between 1 and 6! Check Butcher tableau for 'c'.");
    return this->butcher_tableau_c[idx];
};

double RK45Solver::B(unsigned int i, unsigned int j) {
    unsigned int a = i - 2; 
    unsigned int b = j - 1;

    // if (a == b)
    //     throw SolverException("Indices i and j cannot be identical! Check Butcher tableau for 'B.");
    if (a > 4)
        throw SolverException("Index i must be between 2 and 6! Check Butcher tableau for 'B.");
    else if (a < b) 
        throw SolverException("Index i cannot be smaller than index j! Check Butcher tableau for 'B.");

    return this->butcher_tableau_beta[a][b];
};