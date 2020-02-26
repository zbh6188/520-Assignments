#ifndef _ROBOT_H
#define _ROBOT_H
#include <iostream>
#include "elma/elma.h"

using namespace elma;

class Mode : public State {
    public:
    Mode(std::string name) : State(name) {}
    void entry(const Event& e) {
        std::cout << "entering " + name() << "\n";
    }
    void during() {}
    void exit(const Event&) {}
};

class Robot : public StateMachine {

    public:

    Robot(std::string name) : StateMachine(name), wander("Wander"), findRs("Find Recharge Station"), recharge("Recharge"), mknoise("Make Noise"), evade("Evade") {
        set_initial(wander);
        add_transition("battery low", wander, findRs);
        add_transition("found recharge station", findRs, recharge);
        add_transition("battery full", recharge, wander);
        add_transition("reset", mknoise, wander);
        add_transition("intruder detected", wander, mknoise);
        add_transition("reset", evade, mknoise);
        add_transition("proximity warning", mknoise, evade);        
    }

    private:

    Mode recharge;
    Mode wander;
    Mode findRs;
    Mode evade;
    Mode mknoise;      

};

#endif