#ifndef __MY_LEADER_AGENT__H
#define __MY_LEADER_AGENT__H 

#include "enviro.h"
#include <string>
#include <math.h>
namespace {
    using namespace enviro;

    class MovingForward : public State, public AgentInterface {
        public:
        void entry(const Event& e) {}
        void during() { 
            track_velocity(-3,0);
            if (sensor_value(0) < 30 && sensor_value(1) > 25) {
                emit(Event("turn_left"));
            } else if (sensor_value(0) < 30 && sensor_value(2) > 25) {
                emit(Event("turn_right"));
            }
          
        }
        void exit(const Event& e) {}
    };

    class RotatingL : public State, public AgentInterface {
        public:
        void entry(const Event& e)  {}
        void during() { 
            track_velocity(0,-14); 
            if ( sensor_value(1) < 25 || sensor_value(2) < 25) {
                emit(Event("go"));
            }
        }
        void exit(const Event& e) {}      
    };

    class RotatingR : public State, public AgentInterface {
        public:
        void entry(const Event& e)  {}
        void during() { 
            track_velocity(0,14); 
            if ( sensor_value(1) < 25 || sensor_value(2) < 25) {
                emit(Event("go"));
            }
        }
        void exit(const Event& e) {}       
    };


    class MyLeaderController : public StateMachine, public AgentInterface {

        public:
        MyLeaderController() : StateMachine() {
            set_initial(moving_forward);
            add_transition("turn_left", moving_forward, rotatingL);
            add_transition("turn_right", moving_forward, rotatingR);
            add_transition("go", rotatingL, moving_forward);
            add_transition("go", rotatingR, moving_forward);
        }
        
        MovingForward moving_forward;
        RotatingL rotatingL;
        RotatingR rotatingR;
    };

    class MyLeader : public Agent {
        public:
        MyLeader(json spec, World& world) : Agent(spec, world) {
            add_process(c);
        }
        private:
        MyLeaderController c;
    };

    DECLARE_INTERFACE(MyLeader);
    
}


#endif