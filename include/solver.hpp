#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <sstream>
#include "ode.hpp"

enum FixedStepsizeSolverType {
    EULER,
    RK4
};

class FixedStepsizeSolver {
    public:
        FixedStepsizeSolver(FixedStepsizeSolverType type, ODE ode);

        void setInitialConditions(std::vector<double> initial, double t0 = 0.0);
        std::vector<double> getCurrentSolution();
        virtual void step(double stepsize) = 0; 

        friend std::ostream& operator<<(std::ostream &strm, const FixedStepsizeSolver& fss);

    protected:
        const FixedStepsizeSolverType type;
        const ODE ode;
        std::vector<double> current;
        double t = 0.0;
};

class EulerSolver : public FixedStepsizeSolver {
    public:
        EulerSolver(ODE ode);

        void step(double stepsize) override;
};

class RK4Solver : public FixedStepsizeSolver {
    public:
        RK4Solver(ODE ode);

        void step(double stepsize) override;

    private:   
        static inline const std::vector<double> constants = {1.0 / 6.0, 1.0 / 3.0, 1.0 / 3.0, 1.0 / 6.0};
    };

#endif