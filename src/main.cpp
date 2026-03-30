#include "controller/Controller.hpp"
#include "sensor/TemperatureSensor.hpp"
#include "utils/Logger.hpp"

int main() {
    TemperatureSensor sensor;
    Controller controller;

    float temp = sensor.readTemperature();
    controller.process(temp);

    return 0;
}