#ifndef MORE_MATH_HPP
#define MORE_MATH_HPP

#include <vector>
#include <exception>

std::vector<double> operator+(std::vector<double> v1, std::vector<double> v2);
std::vector<double> operator-(std::vector<double> v1, std::vector<double> v2);
double operator*(std::vector<double> v1, std::vector<double> v2);


template <typename T>
void assertSameLength(std::vector<T> v1, std::vector<T> v2);

class VectorMathException : public std::exception {
    public:
        VectorMathException(const char* msg);
        virtual const char* what() const throw();

    private:
        const char* msg;
};

#endif 