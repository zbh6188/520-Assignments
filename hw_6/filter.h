#ifndef _FILTER_H
#define _FILTER_H
#include <random>
#include <deque>
#include "elma/elma.h"

using namespace elma;
using namespace std;

class Filter : public Process {
    public:
    
    Filter(std::string name) : Process(name) {}

    void init() {}
    void start() {
        sum = 0; 
        average = 0;
    }
    void update() {
        if ( channel("link").nonempty() ) {
            d.push_back(channel("link").latest());
            sum += d.back();
            if (d.size() > 10) {
                d.pop_front();
                sum = sum - d.front();
            }
            average = sum / d.size();
        }
    }
    void stop() {}
    double value() {
        return average;
    }
    
    private:
    double average = 0;
    double sum = 0;
    std::deque<double> d;
};

#endif