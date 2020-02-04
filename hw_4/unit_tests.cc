#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
// #include "point.h"
#include "gtest/gtest.h"
#include "complex.h"

namespace {

    // TEST(TypedArray, Construction) {
    //     TypedArray<Point> b;
    //     b.set(0, Point(1,2,3));
    //     b.set(1, Point(2,3,4));
    //     b.set(20, Point(3,4,5));
    //     EXPECT_EQ(b.get(0).x, 1);
    //     EXPECT_EQ(b.get(1).y, 3);
    //     EXPECT_EQ(b.get(20).z, 5);
    // }

    // TEST(TypedArray, Defaults) {
    //     TypedArray<Point> x;
    //     Point& y = x.get(3);
    //     std::cout << x << "\n";
    //     EXPECT_DOUBLE_EQ(y.magnitude(), 0.0);
    // }

    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    // TEST(TypedArray,CopyElementsInSet1) {
    //     TypedArray<Point> b;
    //     Point p(1,2,3);
    //     b.set(0, p);
    //     p.x = 4;
    //     EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    // }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }

    TEST(TypedArray,Push) {
        TypedArray<double> x;
        double t = 0;
        while (t < 10) {
            x.push(t);
            t = t + 1;
        }
        ASSERT_EQ(x.size(),10);
        std::cout << x << "\n";
        while (x.size() > 0) {
            x.pop();
        }
        ASSERT_EQ(x.size(),0);
        std::cout << x << "\n";
        TypedArray<double> y;
        y.set(0,0);
        y.set(1,1);
        int r = y.pop();
        std::cout << r << "\n";
        std::cout << y << "\n";
    }

    TEST(TypedArray,PushFront) {
        TypedArray<double> x;
        double t = 0;
        while (t < 10) {
            x.push_front(t);
            t += 1;
        }
        ASSERT_EQ(x.size(),10);
        std::cout << x << "\n";
        while (x.size() > 0) {
            x.pop_front();
        }
        ASSERT_EQ(x.size(),0);
        std::cout << x << "\n";
        TypedArray<double> y;
        y.set(0,0);
        y.set(1,1);
        int r = y.pop_front();
        std::cout << r << "\n";
        std::cout << y << "\n";
    }

    TEST(TypedArray,Concat) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> c;
        c.set(0,8);
        c.set(1,9);
        TypedArray<int> b = a.concat(c).concat(c).concat(a).concat(c);
        std::cout << b << "\n";
    }

    TEST(TypedArray,Reverse) {
        TypedArray<int> a;
        int t = 0;
        while (t < 11) {
            a.push(t);
            t = t + 1;
        }
        TypedArray<int> &r = a.reverse();
        std::cout << r << "\n";
        TypedArray<int> b;
        b.set(0,0);
        b.set(1,1);
        TypedArray<int> &r2 = b.reverse();
        std::cout << r2 << "\n";
    }

    TEST(TypedArray, Add) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b = a + a + a;
        TypedArray<int> c;
        c.set(0,2);
        c.set(1,3);
        c.set(2,4);
        TypedArray<int> d = c + a + c + a + c;
        std::cout << b << "\n";
        std::cout << d << "\n";
    }

    TEST(Complex, Conjugate) {
        Complex a = Complex(1,2);
        Complex b = a.conjugate();
        Complex c = Complex(1,-2);
        ASSERT_EQ(b.real(),1);
        ASSERT_EQ(b.imaginary(),-2);
        ASSERT_EQ(b,c);
        Complex d = Complex(0,1);
        Complex e = Complex(1);
        ASSERT_EQ(d.conjugate(),Complex(0,-1));
        ASSERT_EQ(e.conjugate(),Complex(1));
    }

    TEST(Complex, Multiply) {
        Complex a = Complex(1,2);
        Complex b = Complex(3,-4);
        Complex c = Complex(1);
        Complex d = Complex(0,2);
        ASSERT_EQ(a*b,Complex(11,2));
        ASSERT_EQ(c*d,Complex(0,2));
    }

    TEST(Complex, Addition) {
        Complex a = Complex(1,2);
        Complex b = Complex(3,-4);
        Complex c = Complex(1);
        Complex d = Complex(0,2);
        ASSERT_EQ(a+b,Complex(4,-2));
        ASSERT_EQ(c+d,Complex(1,2));
    }

    

    
}