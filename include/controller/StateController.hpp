#pragma once

#include "controller/State.hpp"
#include <vector>

class StateController {
public:
    StateController();
    void process(const std::vector<float>& temperatures);

private:
    State currentState;
    float calculateAverage(const std::vector<float>& temperatures) const;
};