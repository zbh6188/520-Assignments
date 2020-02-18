#ifndef _RANDOM_PROCESS_H
#define _RANDOM_PROCESS_H
#include <random>
#include "elma/elma.h"

using namespace elma;

class RandomProcess : public Process {
    public:
    
    RandomProcess(std::string name) : Process(name) {}

    void init() {}
    void start() {}
    void update() {
        channel("link").send(rand()/double(RAND_MAX));
        //channel("link").send(1);
    }
    void stop() {}

};

#endif