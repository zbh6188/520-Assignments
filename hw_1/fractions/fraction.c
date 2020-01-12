#include "fraction.h"

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}

Fraction reduce ( Fraction a ) {
  int gcd;
  int temp;
  int c = a.num;
  int d = a.den;
  while (d != 0){
    temp = c % d;
    c = d;
    d = temp;
  }
  gcd = c;
  if (a.num == 0 || a.den == 0) {
    return (Fraction){a.num, a.den};
  } else {
    return (Fraction) {a.num / gcd, a.den / gcd};
  }
}