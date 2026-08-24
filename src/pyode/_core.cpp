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

    // EulerSolver
    py::class_<EulerSolver>(m, "EulerSolver")
        .def(py::init<ODE>(), py::arg("ode"), "Create an instace of the EulerSolver class")
        .def("step", static_cast<void (EulerSolver::*)(double)>(&EulerSolver::step), py::arg("stepsize"),
    "Perform an Euler step");

    // RK4Solver
    py::class_<RK4Solver>(m, "RK4Solver")
        .def(py::init<ODE>(), py::arg("ode"), "Create an instace of the RK4Solver class")
        .def("step", static_cast<void (RK4Solver::*)(double)>(&RK4Solver::step), py::arg("stepsize"),
    "Perform an RK4 step");
};  