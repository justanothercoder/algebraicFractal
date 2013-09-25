#include "complex.h"

Complex::Complex() : x(0), y(0) { }
Complex::Complex(double x) : x(x), y(0) { }
Complex::Complex(double x, double y) : x(x), y(y) { }

double Complex::abs() const { return sqrt(x * x + y * y); }
Complex Complex::conjugate() const { return Complex(x, -y); }

Complex operator +(const Complex& u, const Complex& v) { return Complex(u.x + v.x, u.y + v.y); }
Complex operator -(const Complex& u, const Complex& v) { return Complex(u.x - v.x, u.y - v.y); }
Complex operator *(const Complex& u, const Complex& v) { return Complex(u.x * v.x - u.y * v.y, u.x * v.y + u.y * v.x); }
Complex operator /(const Complex& u, const Complex& v) { return Complex((u.x * v.x + u.y * v.y) / (v.abs() * v.abs()),
                                                                        (u.y * v.x - u.x * v.y) / (v.abs() * v.abs()));
                                                       }
