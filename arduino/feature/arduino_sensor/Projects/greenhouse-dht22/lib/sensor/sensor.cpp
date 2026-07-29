#include "sensor.h"

sensor::sensor(uint8_t pinInside, uint8_t pinOutside)
    : dhtInsideSensor(pinInside, DHT11),
      dhtOutsideSensor(pinOutside, DHT11)

{
    pin_Inside = pinInside;
    pin_Outside = pinOutside;

    dhtInsideSensor.begin();
    dhtOutsideSensor.begin();
}
bool sensor::read()
{
    float tempIn = dhtInsideSensor.readTemperature();
    float humidity = dhtInsideSensor.readHumidity();
    float tempOut = dhtOutsideSensor.readTemperature();

    if (isnan(tempIn) || isnan(humidity) || isnan(tempOut))
    {
        Serial.println("Something wrong with sensor!");
        return false;
    }
    else
    {
        dht_Inside = tempIn;
        dht_Humidity = humidity;
        dht_Outside = tempOut;
        sensor_Timestamp = millis();
        return true;
    }
}
// Getter

float sensor::getTempInside()
{
    return dht_Inside;
}
float sensor::getTempOutside()
{
    return dht_Outside;
}
float sensor::getHumidity()
{
    return dht_Humidity;
}
unsigned long sensor::getTimestamp()
{
    return sensor_Timestamp;
}