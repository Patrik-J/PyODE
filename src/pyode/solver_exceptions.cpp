#include "solver_exceptions.hpp"

SolverException::SolverException(const char* msg) : msg(msg) {};

const char* SolverException::what() const throw() {
    return this->msg;
};