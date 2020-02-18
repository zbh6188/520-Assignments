#ifndef _DERIVATIVE_H
#define _DERIVATIVE_H
#include <deque>
#include "elma/elma.h"

using namespace elma;
using namespace std;

class Derivative : public Process {
    public:
    
    Derivative(std::string name) : Process(name) {}

    void init() {}
    void start() {
        derivative = 0;
        x = 0;
    }
    void update() {
        if ( channel("link").nonempty() ) {
            x = channel("link").latest();
            d.push_back(x);
            if (d.size() == 2) {
                derivative = (d.back() - d.front()) / delta();
                d.pop_front();
            }
        }
    }
    void stop() {}
    double value() {
        return derivative;
    }
    
    private:
    double x;
    double derivative;
    std::deque<double> d;
};

#endif