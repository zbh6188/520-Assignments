#include "gtest/gtest.h"
#include "elma/elma.h"
#include "robot.h"
#include "BetterStateMachine.h"
using namespace std::chrono;
using namespace elma;

class Trigger : public Process {
    public:
    Trigger() : Process("trigger") {}
    void init() {}
    void start() {}
    void update() { 
        std::cout << "switch at " << milli_time() << "\n";
        emit(Event("switch"));
    }
    void stop() {}
};

class Mode2 : public State {
    public:
    Mode2(std::string name) : State(name) {}
    void entry(const Event& e) {
        std::cout << "entering " + name() << "\n";
    }
    void during() {}
    void exit(const Event&) {}
};


namespace {
   
    TEST(Robot, Question) {

        Robot robot = Robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 10_ms)
        .init()
        .start();

        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("intruder detected"));
        EXPECT_EQ(robot.current().name(), "Make Noise");
        m.emit(Event("proximity warning"));
        EXPECT_EQ(robot.current().name(), "Evade");
        m.emit(Event("battery full"));
        EXPECT_EQ(robot.current().name(), "Evade");      

        /// ETC

    }

    TEST(Toggle,ItWorks) {
        Manager m;
        Trigger trigger;
        Mode2 off("off"), on("on");
        BetterStateMachine fsm("toggle switch");
        fsm.set_initial(off)
        .set_propagate(false)
        .add_transition("switch", off, on)
        .add_transition("switch", on, off);
        
        auto k = fsm.to_json().dump();
        std::cout << k << "\n";

        json j = fsm.to_json();
        ASSERT_EQ(j["name"], "toggle switch");
        ASSERT_EQ(j["states"].size(), 2);
    }
}
