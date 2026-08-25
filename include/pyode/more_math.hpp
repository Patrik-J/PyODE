#ifndef MORE_MATH_HPP
#define MORE_MATH_HPP

#include <vector>
#include <exception>

using DoubleVector = std::vector<double>;

DoubleVector operator+(DoubleVector v1, DoubleVector v2);
DoubleVector& operator+=(DoubleVector& v1, DoubleVector& v2);

DoubleVector operator-(DoubleVector v1, DoubleVector v2);
DoubleVector& operator-=(DoubleVector& v1, DoubleVector& v2);

double operator*(DoubleVector v1, DoubleVector v2);
DoubleVector operator*(double d, DoubleVector v);
DoubleVector operator*(DoubleVector v, double d);
DoubleVector operator/(DoubleVector v, double d);

template <typename T>
void assertSameLength(std::vector<T> v1, std::vector<T> v2);

class VectorMathException : public std::exception {
    public:
        VectorMathException(const char* msg);
        virtual const char* what() const throw();

    private:
        const char* msg;
};

class VectorContainer {
    public:
        VectorContainer(unsigned int size = 0);
        
        void setItem(unsigned int index, DoubleVector item);
        DoubleVector getItem(unsigned int index);
        unsigned int size();

        void operator=(VectorContainer& v);

    private:
        unsigned int entries;

        std::vector<DoubleVector> storage;
};

class VectorContainerException : public std::exception {
    public:
        VectorContainerException(const char* msg);
        virtual const char* what() const throw();

    private:
        const char* msg;
};

#endif 