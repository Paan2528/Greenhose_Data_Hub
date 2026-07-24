#include <Arduino.h>
#include "sensor.h"

DHT dhtIn(2, DHT11);
DHT dhtOut(3, DHT11);

// put function declarations here:
sensor mySensors(2, 2);

void setup()
{
  Serial.begin(9600);
  // dhtIn.begin();
  // dhtOut.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (mySensors.read())
  {
    Serial.println(mySensors.getTempInside());
    Serial.println(mySensors.getTempOutside());
    Serial.println(mySensors.getHumidity());
  }
  // Serial.println(dhtIn.readTemperature());
  // Serial.println(dhtOut.readTemperature());
  delay(2000);
}
