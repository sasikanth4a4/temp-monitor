#pragma once

#include <string>

class TemperatureSensor {
public:
    TemperatureSensor(int id);
    float readTemperature();
    int getId() const;
    std::string getName() const;

private:
    int sensorId;
};