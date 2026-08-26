#include "more_math.hpp"

DoubleVector operator+(DoubleVector v1, DoubleVector v2) {
    assertSameLength(v1, v2);
    unsigned int n = v1.size();
    DoubleVector out;
    for (unsigned int i = 0; i < n; i++) 
        out.push_back(v1[i] + v2[i]);
    return out;
};

DoubleVector& operator+=(DoubleVector& v1, DoubleVector& v2) {
    assertSameLength(v1, v2);
    for (unsigned int i = 0; i < v1.size(); i++)
        v1[i] += v2[i];
    return v1;
};

DoubleVector operator-(DoubleVector v1, DoubleVector v2) {
    assertSameLength(v1, v2);
    unsigned int n = v1.size();
    DoubleVector out;
    for (unsigned int i = 0; i < n; i++) 
        out.push_back(v1[i] - v2[i]);
    return out;
};

DoubleVector& operator-=(DoubleVector& v1, DoubleVector& v2) {
    assertSameLength(v1, v2);
    for (unsigned int i = 0; i < v1.size(); i++)
        v1[i] -= v2[i];
    return v1;
};

double operator*(DoubleVector v1, DoubleVector v2) {
    assertSameLength(v1, v2);
    unsigned int n = v1.size();
    double out = 0.0;
    for (unsigned int i = 0; i < n; i++) 
        out += v1[i] + v2[i];
    return out;
};

DoubleVector operator*(double d, DoubleVector v) {
    DoubleVector out;
    unsigned int n = v.size();
    for (unsigned int i = 0; i < n; i++) 
        out.push_back(v[i]*d);
    return out;
};

DoubleVector operator*(DoubleVector v, double d) {
    return d*v;
};

DoubleVector operator/(DoubleVector v, double d) {
    return (1/d)*v;
};

double abs(DoubleVector v) {
    unsigned int len = v.size();
    double sum = 0.0;
    for (unsigned int i = 0; i < len; i++)
        sum += pow(v[i], 2);
    return pow(sum, 0.5);
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

VectorContainer::VectorContainer(unsigned int size) : entries(size) {
    DoubleVector empty;
    for (unsigned int i = 0; i < size; i++) 
        this->storage.push_back(empty);
};

void VectorContainer::setItem(unsigned int index, DoubleVector& item) {
    if (this->entries == 0) 
        return;
    if (index > this->entries - 1)
        throw VectorContainerException("Index out of range!");
    this->storage[index] = item;
};

const DoubleVector& VectorContainer::getItem(unsigned int index) const {
    if (index > this->entries)
        throw VectorContainerException("Index out of range!");
    return this->storage[index];
};

DoubleVector& VectorContainer::getItem(unsigned int index) {
    if (index > this->entries)
        throw VectorContainerException("Index out of range!");
    return this->storage[index];
};

unsigned int VectorContainer::size() const {
    unsigned int len = this->entries;
    return len;
};

void VectorContainer::operator=(const VectorContainer& v) {
    this->entries = v.size();
    this->storage = v.storage;
};

VectorContainerException::VectorContainerException(const char* msg) : msg(msg) {};

const char* VectorContainerException::what() const throw() {
    return this->msg;
};