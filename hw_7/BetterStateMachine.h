#ifndef _BETTER_STATE_MACHINE_H
#define _BETTER_STATE_MACHINE_H

#include "elma/elma.h"
#include <set>
#include <json/json.h>

using nlohmann::json; 
using namespace elma;

class BetterStateMachine : public StateMachine {
    
    public:

    BetterStateMachine(std::string name) : StateMachine(name), sname(name) {}
    
    json to_json() const {
        json j;
        j["name"] = sname;
        std::set<std::string> setOfStates;
        for (auto t : _transitions) {
            setOfStates.insert(t.to().name());
        }
        j["states"] = setOfStates;
	    
        j["transitions"] ={};
        for (auto trans : _transitions) {
            j["transitions"].push_back({{"from", trans.from().name()},
                                        {"to", trans.to().name()},
                                        {"when", trans.event_name()}});
        }
        return j;
    }

    private:
    std::string sname;
};

#endif