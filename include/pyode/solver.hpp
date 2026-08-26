#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <sstream>
#include "ode.hpp"

class SolverException : public std::exception {
    public:
        SolverException(const char* msg);
        virtual const char* what() const throw();

    private:
        const char* msg;
};

enum FixedStepsizeSolverType {
    Euler,
    BackwardEuler,
    RK4,
    AdamBash
};

class FixedStepsizeSolver {
    public:
        FixedStepsizeSolver(FixedStepsizeSolverType type, ODE ode);

        void setInitialConditions(DoubleVector initial, double t0 = 0.0);
        DoubleVector getCurrentSolution();
        virtual void step(double stepsize) = 0; 

        friend std::ostream& operator<<(std::ostream &strm, const FixedStepsizeSolver& fss);

    protected:
        const FixedStepsizeSolverType type;
        const ODE ode;
        DoubleVector current;
        double t = 0.0;
};

class EulerSolver : public FixedStepsizeSolver {
    public:
        EulerSolver(ODE ode);

        void step(double stepsize) override;
};

class BackwardEulerSolver : public FixedStepsizeSolver {
    
    static inline const unsigned int MAX_ITERATION_STEPS = 1000;
    static inline const double MAX_ERROR = 1e-6;

    public:
        BackwardEulerSolver(ODE ode);

        void step(double stepsize) override;
};

class RK4Solver : public FixedStepsizeSolver {
    public:
        RK4Solver(ODE ode);

        void step(double stepsize) override;

    private:   
        static inline const DoubleVector constants = {1.0 / 6.0, 1.0 / 3.0, 1.0 / 3.0, 1.0 / 6.0};
};

class AdamsBashforthSolver : public FixedStepsizeSolver {
    static inline const DoubleVector s1 = {1.0};
    static inline const DoubleVector s2 = {3.0/2.0, -1.0/2.0};
    static inline const DoubleVector s3 = {23.0/12.0, -16.0/12.0, 5.0/12.0};
    static inline const DoubleVector s4 = {55.0/24.0, -59.0/24.0, 37.0/24.0, -9.0/24.0};
    static inline const DoubleVector s5 = {1901.0/720.0, -2774.0/720.0, 2616.0/720.0, -1274.0/720.0, 251.0/720.0};

    public:
        AdamsBashforthSolver(ODE ode, unsigned int s = 2);

        void step(double stepsize) override;

    private:
        VectorContainer priorValues;
        unsigned int s;
        DoubleVector constants;
};

#endif