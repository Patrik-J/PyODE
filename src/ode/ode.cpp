#include "ode.hpp"

ODE::ODE(std::function<double(double, std::vector<double>)> func) : func(func) {};

std::vector<double> ODE::operator() (double t, std::vector<double> y) {
    std::vector<double> f;

    unsigned int n = y.size();

    for (unsigned int i = 0; i < n-1; i++) {
        f.push_back(y[i+1]);
    };

    f.push_back(this->func(t, y));

    return f;
};
