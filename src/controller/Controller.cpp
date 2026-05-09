#include "controller/Controller.hpp"
#include "utils/Logger.hpp"
#include "utils/Config.hpp"
#include "hardware/GPIO.hpp"
#include <string>
#include <numeric>

void Controller::process(const std::vector<float>& temperatures) {
    if (temperatures.empty()) return;

    float avgTemp = calculateAverage(temperatures);
    int threshold = Config::getThreshold();

    if (avgTemp > threshold) {
        Logger::log("Fan ON - High Average Temperature: " + std::to_string(avgTemp));
        GPIO::setHigh(1);  // simulate fan ON
    } else {
        Logger::log("Fan OFF - Normal Average Temperature: " + std::to_string(avgTemp));
        GPIO::setLow(1);   // simulate fan OFF
    }

    // Log individual sensor readings
    for (size_t i = 0; i < temperatures.size(); ++i) {
        Logger::log("Sensor " + std::to_string(i + 1) + ": " + std::to_string(temperatures[i]) + "°C");
    }
}

float Controller::calculateAverage(const std::vector<float>& temperatures) const {
    if (temperatures.empty()) return 0.0f;
    return std::accumulate(temperatures.begin(), temperatures.end(), 0.0f) / temperatures.size();
}