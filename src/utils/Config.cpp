#include "utils/Config.hpp"
#include <fstream>
#include <iostream>
#include <string>

int Config::getThreshold() {
    std::ifstream file("config/config.json");

    if (!file) {
        std::cerr << "Failed to open config file\n";
        return 50; // default
    }

    std::string line;
    int threshold = 30;

    while (getline(file, line)) {
        if (line.find("threshold") != std::string::npos) {
            threshold = std::stoi(line.substr(line.find(":") + 1));
        }
    }

    return threshold;
}