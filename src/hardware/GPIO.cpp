#include "hardware/GPIO.hpp"
#include "utils/Logger.hpp"

void GPIO::setHigh(int pin) {
    Logger::log("[GPIO] Pin " + std::to_string(pin) + " -> HIGH (ON)");
}

void GPIO::setLow(int pin) {
    Logger::log("[GPIO] Pin " + std::to_string(pin) + " -> LOW (OFF)");
}