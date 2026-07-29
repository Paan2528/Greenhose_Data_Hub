#ifndef DHT11PAIR_H
#define DHT11PAIR_H

#include <Arduino.h>
#include <DHT.h>

class sensor
{

public:
    sensor(uint8_t pinInside, uint8_t pinOutside);

    bool read();

    float getTempInside();
    float getTempOutside();
    float getHumidity();
    unsigned long getTimestamp();

private:
    DHT dhtInsideSensor;
    DHT dhtOutsideSensor;
    uint8_t pin_Inside;
    uint8_t pin_Outside;
    float dht_Inside;
    float dht_Outside;
    float dht_Humidity;
    unsigned long sensor_Timestamp;
};
#endif // DHT22PAIR_H