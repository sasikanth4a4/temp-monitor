#ifndef GPIO_HPP
#define GPIO_HPP

class GPIO {
public:
    static void setHigh(int pin);
    static void setLow(int pin);
};

#endif