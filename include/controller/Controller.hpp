#pragma once

#include <vector>

class Controller {
public:
    void process(const std::vector<float>& temperatures);
private:
    float calculateAverage(const std::vector<float>& temperatures) const;
};