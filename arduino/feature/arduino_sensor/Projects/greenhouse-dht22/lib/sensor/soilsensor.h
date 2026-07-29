#ifndef SOIL_SENSOR_H
#define SOIL_SENSOR_H

#include <Arduino.h>
class soilsensor
{
public:
    soilsensor(uint8_t soilSensorPin1, uint8_t soilSensorPin2, uint8_t soilSensorPin3);
    bool read();
    float getSoilHumidPin1();
    float getSoilHumidPin2();
    float getSoilHumidPin3();
    unsigned long getTimestamp();

private:
    uint8_t sensorPin1;
    uint8_t sensorPin2;
    uint8_t sensorPin3;

    float sensor_pin1;
    float sensor_pin2;
    float sensor_pin3;
    unsigned long time_stamp;
};

#endif // SOIL_SENSOR_H