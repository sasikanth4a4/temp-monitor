#pragma once

#include "controller/State.hpp"

class StateController {
public:
    StateController();
    void process(float temperature);

private:
    State currentState;
};