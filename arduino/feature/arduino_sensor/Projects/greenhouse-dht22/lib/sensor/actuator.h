#ifndef sensorFanPump_H
#define sensorFanPump_H

#include <Arduino.h>

// ############# Fan ###########
class fan
{
public:
    fan(uint8_t pinFan);
    void turnOn();
    void turnOff();
    bool getIsOn();
    bool getIsOff();

private:
    uint8_t pin_Fan;
    bool is_On;
};

// ############# Pump ###########
class pump
{
public:
    pump(uint8_t pinPump);
    void turnOn();
    void turnOff();
    bool getIsOn();
    bool getIsOff();

private:
    uint8_t pin_Pump;
    bool is_On;
};
#endif // sensorFanPump_H