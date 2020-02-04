#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

bool operator==(const Complex& a, const Complex& b) {

    return a.real() == b.real() && a.imaginary() == b.imaginary();

}

Complex operator*(const Complex& a, const Complex& b) {
    Complex result = Complex ((a.real()*b.real() - a.imaginary()*b.imaginary()),(a.real()*b.imaginary() + a.imaginary()*b.real()));
    return result;
}

Complex operator+(const Complex& a, const Complex& b) {
    Complex result = Complex((a.real()+b.real()),(a.imaginary()+b.imaginary()));
    return result;
}

double Complex::real() const {
    return re;
}

double Complex::imaginary() const {
    return im;
}

Complex Complex::conjugate() {
    Complex conjugate = Complex(real(), -imaginary());
    return conjugate;
}

