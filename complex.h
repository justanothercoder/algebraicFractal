#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

class Complex
{
    friend Complex operator +(const Complex& u, const Complex& v);
    friend Complex operator -(const Complex& u, const Complex& v);
    friend Complex operator *(const Complex& u, const Complex& v);
    friend Complex operator /(const Complex& u, const Complex& v);

public:
    Complex();
    Complex(double x);
    Complex(double x, double y);

    double abs() const;
    Complex conjugate() const;

    double x, y;
};

Complex operator +(const Complex& u, const Complex& v);
Complex operator -(const Complex& u, const Complex& v);
Complex operator *(const Complex& u, const Complex& v);
Complex operator /(const Complex& u, const Complex& v);

#endif // COMPLEX_H
