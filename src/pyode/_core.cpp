#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include "ode.hpp"
#include "solver.hpp"

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

    // RK4Solver
    py::class_<RK4Solver, FixedStepsizeSolver>(m, "RK4Solver")
    .def(py::init<ODE>(), py::arg("ode"), "Create an instace of the RK4Solver class")
    .def("step", &RK4Solver::step, py::arg("stepsize"), "Perform a RK4 step.");
};  