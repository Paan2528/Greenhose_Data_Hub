#include "soilsensor.h"

soilsensor::soilsensor(uint8_t soilSensorPin1, uint8_t soilSensorPin2, uint8_t soilSensorPin3)
    : sensorPin1(soilSensorPin1), sensorPin2(soilSensorPin2), sensorPin3(soilSensorPin3)
{
}
bool soilsensor::read()
{

    sensor_pin1 = analogRead(sensorPin1);
    sensor_pin2 = analogRead(sensorPin2);
    sensor_pin3 = analogRead(sensorPin3);
    time_stamp = millis();
    return true;

    if (isnan(sensor_pin1) || isnan(sensor_pin2) || isnan(sensor_pin3))
    {
        Serial.println("Something wrong with sensor!");
        return false;
    }
    else
    {
        sensor_pin1 = sensorPin1;
        sensor_pin2 = sensorPin2;
        sensor_pin3 = sensorPin3;
    }
}
float soilsensor::getSoilHumidPin1()
{
    return sensor_pin1;
}
float soilsensor::getSoilHumidPin2()
{
    return sensor_pin2;
}
float soilsensor::getSoilHumidPin3()
{
    return sensor_pin3;
}
unsigned long soilsensor::getTimestamp()
{
    return time_stamp;
}