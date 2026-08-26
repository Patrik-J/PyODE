#ifndef ADAPTIVE_SOLVER_HPP
#define ADAPTIVE_SOLVER_HPP

#include <sstream>

#include "ode.hpp"

enum AdaptiveStepsizeSolverType {
    RK45
};

class AdaptiveStepsizeSolver {
    public:
        AdaptiveStepsizeSolver(AdaptiveStepsizeSolverType type, ODE ode);

        void setInitialConditions(DoubleVector initial, double t0 = 0.0);
        DoubleVector getCurrentSolution();
        virtual void step(double max_stepsize) = 0; 

        friend std::ostream& operator<<(std::ostream &strm, const AdaptiveStepsizeSolver& ass);

    protected:
        const AdaptiveStepsizeSolverType type;
        const ODE ode;
        DoubleVector current;
        double t = 0.0;

};

class RK45Solver : public AdaptiveStepsizeSolver {
    public:
        RK45Solver(ODE ode);

        void step(double max_stepsize) override;
};

#endif 