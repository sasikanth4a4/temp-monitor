#include "controller/StateController.hpp"
#include "utils/Logger.hpp"
#include "utils/Config.hpp"
#include <string>
#include <numeric>

StateController::StateController() {
    currentState = State::IDLE;
}

void StateController::process(const std::vector<float>& temperatures) {
    if (temperatures.empty()) return;

    float avgTemp = calculateAverage(temperatures);
    int threshold = Config::getThreshold();

    switch (currentState) {

        case State::IDLE:
            Logger::log("[STATE] IDLE -> RUNNING");
            currentState = State::RUNNING;
            break;

        case State::RUNNING:
            if (avgTemp > threshold) {
                Logger::log("[STATE] RUNNING -> COOLING (Avg Temp: " + std::to_string(avgTemp) + ")");
                currentState = State::COOLING;
            } else {
                Logger::log("[STATE] RUNNING (Avg Temp: " + std::to_string(avgTemp) + ")");
            }
            break;

        case State::COOLING:
            if (avgTemp <= threshold) {
                Logger::log("[STATE] COOLING -> RUNNING (Avg Temp: " + std::to_string(avgTemp) + ")");
                currentState = State::RUNNING;
            } else {
                Logger::log("[STATE] COOLING (Avg Temp high: " + std::to_string(avgTemp) + ")");
            }
            break;
    }
}

float StateController::calculateAverage(const std::vector<float>& temperatures) const {
    if (temperatures.empty()) return 0.0f;
    return std::accumulate(temperatures.begin(), temperatures.end(), 0.0f) / temperatures.size();
}