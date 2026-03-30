#include "sensor/TemperatureSensor.hpp"
#include "controller/Controller.hpp"
#include "controller/StateController.hpp"

#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>

std::atomic<float> sharedTemp(0.0);
std::atomic<bool> running(true);

// Sensor Thread
void sensorTask()
{
    TemperatureSensor sensor;

    while (running)
    {
        float temp = sensor.readTemperature();
        sharedTemp = temp;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Control Thread
void controlTask()
{
    Controller simpleController;
    StateController stateController;

    while (running)
    {
        float temp = sharedTemp.load();

        simpleController.process(temp);
        stateController.process(temp);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    std::thread t1(sensorTask);
    std::thread t2(controlTask);

    std::cout << "System running... Press Ctrl+C to stop\n";

    t1.join();
    t2.join();

    return 0;
}