#ifndef _INTEGRATOR_H
#define _INTEGRATOR_H
#include "elma/elma.h"

using namespace elma;
using namespace std;

class Integrator : public Process {
    public:
    
    Integrator(std::string name) : Process(name) {}

    void init() {}
    void start() {
        inteVal = 0;
        v = 0;
    }
    void update() {
        if ( channel("link").nonempty() ) {
            v = channel("link").latest();
            inteVal += delta() * v;
        }
    }
    void stop() {}
    double value() {
        return inteVal;
    }
    
    private:
    double v;
    double inteVal;
};

#endif