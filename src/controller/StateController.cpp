#include "controller/StateController.hpp"
#include "utils/Logger.hpp"
#include "utils/Config.hpp"
#include <string>

StateController::StateController() {
    currentState = State::IDLE;
}

void StateController::process(float temperature) {
    int threshold = Config::getThreshold();

    switch (currentState) {

        case State::IDLE:
            Logger::log("[STATE] IDLE -> RUNNING");
            currentState = State::RUNNING;
            break;

        case State::RUNNING:
            if (temperature > threshold) {
                Logger::log("[STATE] RUNNING -> COOLING (Temp: " + std::to_string(temperature) + ")");
                currentState = State::COOLING;
            } else {
                Logger::log("[STATE] RUNNING (Temp: " + std::to_string(temperature) + ")");
            }
            break;

        case State::COOLING:
            if (temperature <= threshold) {
                Logger::log("[STATE] COOLING -> RUNNING (Temp: " + std::to_string(temperature) + ")");
                currentState = State::RUNNING;
            } else {
                Logger::log("[STATE] COOLING (Temp high: " + std::to_string(temperature) + ")");
            }
            break;
    }
}