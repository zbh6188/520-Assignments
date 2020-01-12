#include <math.h>
#include "complex.h"

Complex add ( Complex a, Complex b ){
    return (Complex){a.real + b.real, a.im + b.im};
}

Complex negate ( Complex a ) {
    return (Complex){a.real * -1, a.im * -1};
}

Complex multiply ( Complex a, Complex b ){
    return (Complex){a.real * b.real - a.im * b.im, a.real * b.im + a.im * b.real};
}

double magnitude ( Complex a ){
    double mag = sqrt(a.real * a.real + a.im * a.im);
    return mag;
}