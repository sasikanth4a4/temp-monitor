#include "controller/Controller.hpp"
#include "utils/Logger.hpp"
#include "utils/Config.hpp"
#include <string>

void Controller::process(float temperature) {
    int threshold = Config::getThreshold();

    if (temperature > threshold) {
        Logger::log("Fan ON - High Temperature: " + std::to_string(temperature));
    } else {
        Logger::log("Fan OFF - Normal Temperature: " + std::to_string(temperature));
    }
}