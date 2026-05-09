#include "sensor/TemperatureSensor.hpp"
#include <cstdlib>
#include <ctime>

TemperatureSensor::TemperatureSensor(int id) : sensorId(id) {
    // Seed random number generator differently for each sensor
    srand(time(nullptr) + sensorId);
}

float TemperatureSensor::readTemperature() {
    // Generate temperature with some variation based on sensor ID
    // Sensor 1: 0-99°C, Sensor 2: 5-104°C, etc.
    int baseTemp = rand() % 100;
    float variation = (sensorId - 1) * 5.0f; // 5°C offset per sensor
    return baseTemp + variation;
}

int TemperatureSensor::getId() const {
    return sensorId;
}

std::string TemperatureSensor::getName() const {
    return "Sensor_" + std::to_string(sensorId);
}