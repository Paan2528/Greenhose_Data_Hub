#include "actuator.h"
// ############# Fan #################
//  setter
fan::fan(uint8_t pinFan)
{
    pin_Fan = pinFan;
    pinMode(pin_Fan, OUTPUT);
    is_On = false;
}
void fan::turnOn()
{
    digitalWrite(pin_Fan, HIGH);
    is_On = true;
}
void fan::turnOff()
{
    digitalWrite(pin_Fan, LOW);
    is_On = false;
}

// getter

bool fan::getIsOn()
{
    return is_On;
}
bool fan::getIsOff()
{
    return !is_On;
}

// ############## Pump ###############

pump::pump(uint8_t pinPummp)
{
    pin_Pump = pinPummp;
    pinMode(pin_Pump, OUTPUT);
    is_On = false;
}
void pump::turnOn()
{
    digitalWrite(pin_Pump, HIGH);
    is_On = true;
}
void pump::turnOff()
{
    digitalWrite(pin_Pump, LOW);
    is_On = false;
}

// getter

bool pump::getIsOn()
{
    return is_On;
}
bool pump::getIsOff()
{
    return !is_On;
}