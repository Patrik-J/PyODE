#ifndef SOLVER_EXCEPTIONS_HPP
#define SOLVER_EXCEPTIONS_HPP

#include <exception>

class SolverException : public std::exception {
    public:
        SolverException(const char* msg);
        virtual const char* what() const throw();

    private:
        const char* msg;
};

#endif 