#include <Arduino.h>
#include "sensor.h"
#include "actuator.h"

fan myFan(7);
pump myPump(8);

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

  myFan.turnOn();
  Serial.println(myFan.getIsOn());
  delay(5000);
  myFan.turnOff();
  Serial.println(myFan.getIsOff());
  delay(5000);

  myPump.turnOn();
  Serial.println(myFan.getIsOn());
  delay(2000);
  myPump.turnOff();
  Serial.println(myFan.getIsOff());
  delay(5000);
}
