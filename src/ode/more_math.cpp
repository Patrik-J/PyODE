#include "more_math.hpp"

std::vector<double> operator+(std::vector<double> v1, std::vector<double> v2) {
    assertSameLength(v1, v2);
    unsigned int n = v1.size();
    std::vector<double> out;
    for (unsigned int i = 0; i < n; i++) 
        out.push_back(v1[i] + v2[i]);
    return out;
};

void operator+=(std::vector<double> v1, std::vector<double> v2) {
    assertSameLength(v1, v2);
    v1 = v1 + v2;
};

std::vector<double> operator-(std::vector<double> v1, std::vector<double> v2) {
    assertSameLength(v1, v2);
    unsigned int n = v1.size();
    std::vector<double> out;
    for (unsigned int i = 0; i < n; i++) 
        out.push_back(v1[i] - v2[i]);
    return out;
};

void operator-=(std::vector<double> v1, std::vector<double> v2) {
    assertSameLength(v1, v2);
    v1 = v1 - v2;
};

double operator*(std::vector<double> v1, std::vector<double> v2) {
    assertSameLength(v1, v2);
    unsigned int n = v1.size();
    double out = 0.0;
    for (unsigned int i = 0; i < n; i++) 
        out += v1[i] + v2[i];
    return out;
};

std::vector<double> operator*(double d, std::vector<double> v) {
    std::vector<double> out;
    unsigned int n = v.size();
    for (unsigned int i = 0; i < n; i++) 
        out.push_back(v[i]*d);
    return out;
};

std::vector<double> operator*(std::vector<double> v, double d) {
    return d*v;
};

std::vector<double> operator/(std::vector<double> v, double d) {
    return (1/d)*v;
};

template <typename T>
void assertSameLength(std::vector<T> v1, std::vector<T> v2) {
    if (v1.size() != v2.size()) 
        throw VectorMathException("Vectors have unequal length!");
};

VectorMathException::VectorMathException(const char* msg) : msg(msg) {};

const char* VectorMathException::what() const throw() {
    return this->msg;
};