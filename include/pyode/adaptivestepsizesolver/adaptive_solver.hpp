#ifndef ADAPTIVE_SOLVER_HPP
#define ADAPTIVE_SOLVER_HPP

#include <sstream>
#include "ode.hpp"
#include "solver_exceptions.hpp"

enum AdaptiveStepsizeSolverType {
    RK45
};

class AdaptiveStepsizeSolver {
    public:
        AdaptiveStepsizeSolver(AdaptiveStepsizeSolverType type, ODE ode);

        void setInitialConditions(DoubleVector initial, double t0 = 0.0);
        void setInitialStepsize(double initial_stepsize = 0.001);
        DoubleVector getCurrentSolution();
        double getCurrentTime();
        virtual void step() = 0; 

        friend std::ostream& operator<<(std::ostream &strm, const AdaptiveStepsizeSolver& ass);

    protected:
        const AdaptiveStepsizeSolverType type;
        const ODE ode;
        DoubleVector current;
        double t = 0.0;
        double h = 0.001;
};

class RK45Solver : public AdaptiveStepsizeSolver {
    static inline constexpr double butcher_tableau_alpha[6] = {
        0.0, 2.0/9.0, 1.0/3.0, 3.0/4.0, 1.0, 5.0/6.0
    };

    static inline constexpr double butcher_tableau_beta[6][5] = {
        {0.0},
        {2.0/9.0},
        {1.0/12.0,   1.0/4.0},
        {69.0/128.0, -243.0/128.0, 135.0/64.0},
        {-17.0/12.0,  27.0/4.0,   -27.0/5.0, 16.0/15.0},
        {65.0/432.0, -5.0/16.0,   13.0/16.0, 4.0/27.0, 5.0/144.0}
    };

    static inline constexpr double butcher_tableau_c_hat[6] = {
        47.0/450.0, 0.0, 12.0/25.0, 32.0/225.0, 1.0/30.0, 6.0/25.0
    };

    static inline constexpr double butcher_tableau_c[6] = {
        1.0/9.0, 0.0, 9.0/20.0, 16.0/45.0, 1.0/12.0, 0.0
    };

    public:
        RK45Solver(ODE ode, double epsilon = 1e-6);

        void step() override;

    private:
        double epsilon;

        double A(unsigned int index);
        double B(unsigned int i, unsigned int j);
        double c_hat(unsigned int index);
        double c(unsigned int index);
};

#endif 