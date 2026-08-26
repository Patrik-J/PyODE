#include "adaptive_solver.hpp"

AdaptiveStepsizeSolver::AdaptiveStepsizeSolver(AdaptiveStepsizeSolverType type, ODE ode) : type(type), ode(ode) {};

void AdaptiveStepsizeSolver::setInitialConditions(std::vector <double> initial, double t0) {
    this->current = initial;
    this->t = t0;
};

DoubleVector AdaptiveStepsizeSolver::getCurrentSolution() {
    return this->current;
};

std::ostream& operator<<(std::ostream &strm, const AdaptiveStepsizeSolver& ass) {
    strm << "Fixed stepsize solver of type ";

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

RK45Solver::RK45Solver(ODE ode) : AdaptiveStepsizeSolver(AdaptiveStepsizeSolverType::RK45, ode) {

};

void RK45Solver::step(double max_stepsize) {

};