#include "sensor/TemperatureSensor.hpp"
#include <cstdlib>

float TemperatureSensor::readTemperature() {
    return rand() % 100; // simulate 0–99°C
}