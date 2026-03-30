#ifndef STATE_CONTROLLER_HPP
#define STATE_CONTROLLER_HPP

#include "controller/State.hpp"

class StateController {
public:
    StateController();
    void process(float temperature);

private:
    State currentState;
};

#endif