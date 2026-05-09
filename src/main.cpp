#include "sensor/TemperatureSensor.hpp"
#include "controller/Controller.hpp"
#include "controller/StateController.hpp"

#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>
#include <vector>
#include <mutex>
#include <csignal>

const int NUM_SENSORS = 3;  // Number of temperature sensors
std::vector<std::atomic<float>> sharedTemps(NUM_SENSORS);
std::atomic<bool> running(true);
std::mutex tempMutex;

// Signal handler for graceful shutdown
void signalHandler(int signum) {
    std::cout << "\nShutting down system...\n";
    running = false;
}

// Sensor Thread - one per sensor
void sensorTask(int sensorId)
{
    TemperatureSensor sensor(sensorId);

    while (running)
    {
        float temp = sensor.readTemperature();
        sharedTemps[sensorId - 1] = temp;

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
        std::vector<float> currentTemps;
        {
            std::lock_guard<std::mutex> lock(tempMutex);
            for (const auto& temp : sharedTemps) {
                currentTemps.push_back(temp.load());
            }
        }

        simpleController.process(currentTemps);
        stateController.process(currentTemps);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    // Register signal handler for graceful shutdown
    std::signal(SIGINT, signalHandler);

    std::cout << "Multi-Sensor Temperature Monitor System\n";
    std::cout << "Number of sensors: " << NUM_SENSORS << "\n";
    std::cout << "System running... Press Ctrl+C to stop\n\n";

    // Create sensor threads
    std::vector<std::thread> sensorThreads;
    for (int i = 1; i <= NUM_SENSORS; ++i) {
        sensorThreads.emplace_back(sensorTask, i);
    }

    // Create control thread
    std::thread controlThread(controlTask);

    // Wait for threads (they run until Ctrl+C)
    for (auto& t : sensorThreads) {
        t.join();
    }
    controlThread.join();

    std::cout << "System shutdown complete.\n";
    return 0;
}