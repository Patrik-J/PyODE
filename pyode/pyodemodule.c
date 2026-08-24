#define PY_SSIZE_T_CLEAN
#include <Python.h>

// ODE(std::function<double(double, std::vector<double>)> func)
static PyObject* pyode_ode(PyObject* self, PyObject* args) {
    Py_RETURN_NONE;
};

// EulerSolver(ODE ode)
static PyObject* pyode_euler(PyObject* self, PyObject* args) {
    Py_RETURN_NONE;
};

// void EulerSolver::step(double stepsize)
static PyObject* pyode_euler_step(PyObject* self, PyObject* args) {
    Py_RETURN_NONE;
};

// RK4Solver(ODE ode)
static PyObject* pyode_rk4(PyObject* self, PyObject* args) {
    Py_RETURN_NONE;
};

// void RK4Solver::step(double stepsize)
static PyObject* pyode_rk4_step(PyObject* self, PyObject* args) {
    Py_RETURN_NONE;
};

static PyMethodDef pyode_methods[] = {
    {"ode", pyode_ode, METH_VARARGS, "Create a new instance of the ODE class."},
    {"euler", pyode_euler, METH_VARARGS, "Create a new instance of an Euler solver."},
    {"euler_step", pyode_euler_step, METH_VARARGS, "Perform one Euler step."},
    {"rk4", pyode_rk4, METH_VARARGS, "Create a new instance of an RK4 solver."},
    {"rk4_step", pyode_rk4_step, METH_VARARGS, "Perform one RK4 step."},
    {NULL, NULL, 0, NULL}
};

static PyObject* PyOdeError = NULL;

static int pyode_module_exec(PyObject* m) {
    if (PyOdeError != NULL) {
        PyErr_SetString(PyExc_ImportError, "Cannot initialized PyODE module more than once!");      // set the error type and error message
        return -1;
    }
    PyOdeError = PyErr_NewException("PyODE.error", NULL, NULL);     // initialize new exception 
    if (PyModule_AddObjectRef(m, "PyOdeError", PyOdeError) < 0) {
        return -1;
    }
    return 0;
};

static PyModuleDef_Slot pyode_module_slots[] = {
    {Py_mod_exec, pyode_module_exec},
    {0, NULL}
};

static struct PyModuleDef pyode_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "PyODE",
    .m_size = 0,
    .m_slots = pyode_module_slots,
    .m_methods = pyode_methods
};

PyMODINIT_FUNC PyInit_pyode(void) {
    return PyModuleDef_Init(&pyode_module);
};