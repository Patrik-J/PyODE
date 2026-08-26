#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include "ode.hpp"
#include "fixedstepsizesolver/solver.hpp"
#include "adaptivestepsizesolver/adaptive_solver.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.doc() = "Bindings for the ODE class";

    // ODE class
    py::class_<ODE>(m, "ODE")
        .def(py::init<std::function<double(double, std::vector<double>)>>(), py::arg("func"), "Create an instance of the ODE class")
        .def("__call__", static_cast<std::vector<double> (ODE::*)(double, std::vector<double>)>(&ODE::operator()),
        py::arg("t"), py::arg("y"),
        "Call the function defining the ODE");

    // Base FixedStepsizeSolver class
    py::class_<FixedStepsizeSolver>(m, "FixedStepsizeSolver")
    .def("setInitialConditions", &FixedStepsizeSolver::setInitialConditions, py::arg("initial"), py::arg("t0") = 0.0, "Set the initial conditions.")
    .def("getCurrentSolution", &FixedStepsizeSolver::getCurrentSolution, "Get the result of the previous step.")
    .def("__repr__", [](const FixedStepsizeSolver &self) {
        std::ostringstream oss;
        oss << self;
        return oss.str();
    });

    // EulerSolver
    py::class_<EulerSolver, FixedStepsizeSolver>(m, "EulerSolver")
    .def(py::init<ODE>(), py::arg("ode"), "Create an instace of the EulerSolver class")
    .def("step", &EulerSolver::step, py::arg("stepsize"), "Perform an Euler step.");

    // BackwardEulerSolver
    py::class_<BackwardEulerSolver, FixedStepsizeSolver>(m, "BackwardEulerSolver")
    .def(py::init<ODE>(), py::arg("ode"), "Create an instace of the BackwardEulerSolver class")
    .def("step", &BackwardEulerSolver::step, py::arg("stepsize"), "Perform an backwards Euler step.");

    // RK4Solver
    py::class_<RK4Solver, FixedStepsizeSolver>(m, "RK4Solver")
    .def(py::init<ODE>(), py::arg("ode"), "Create an instace of the RK4Solver class")
    .def("step", &RK4Solver::step, py::arg("stepsize"), "Perform a RK4 step.");

    // AdamsBashforthSolver
    py::class_<AdamsBashforthSolver, FixedStepsizeSolver>(m, "AdamsBashforthSolver")
    .def(py::init<ODE, unsigned int>(), py::arg("ode"), py::arg("s") = 2, "Create an instace of the AdamsBashforthSolver class")
    .def("step", &AdamsBashforthSolver::step, py::arg("stepsize"), "Perform a Adams-Bashforth step.");

    // Base AdaptiveStepsizeSolver class
    py::class_<AdaptiveStepsizeSolver>(m, "AdaptiveStepsizeSolver")
    .def("setInitialConditions", &AdaptiveStepsizeSolver::setInitialConditions, py::arg("initial"), py::arg("t0") = 0.0, "Set the initial conditions.")
    .def("getCurrentSolution", &AdaptiveStepsizeSolver::getCurrentSolution, "Get the result of the previous step.")
    .def("setInitialStepsize", &AdaptiveStepsizeSolver::setInitialStepsize, py::arg("initial_stepsize") = 0.001, "Set the initial stepsize.")
    .def("getCurrentTime", &AdaptiveStepsizeSolver::getCurrentTime, "Get the current time after the previous step.")
    .def("__repr__", [](const AdaptiveStepsizeSolver &self) {
        std::ostringstream oss;
        oss << self;
        return oss.str();
    });

    // RK45Solver
    py::class_<RK45Solver, AdaptiveStepsizeSolver>(m, "RK45Solver")
    .def(py::init<ODE, double>(), "Create an instace of the RK45Solver class")
    .def("step", &RK45Solver::step, "Perform a RK4(5) step.");
};  