#ifndef ODE_HPP
#define ODE_HPP

#include <functional>
#include <vector>

#include "more_math.hpp"

class ODE {
    /*
        A basic class to hold one-dimensional ODEs.
    */
    public:
        ODE(std::function<double(double, std::vector<double>)> func);

        // this returns a vector of the same size as the input vector
        // the entries i = 0,...,n-1 are simply data y^(i+1)_n
        // the last entry of the vector is f(t_n, y_n)
        std::vector<double> operator() (double t, std::vector<double> y);
        std::vector<double> operator() (double t, std::vector<double> y) const;

    private:
        const std::function<double(double, std::vector<double>)> func;
};

#endif