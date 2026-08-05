#include <Arduino.h>
#include "sensor.h"
#include "actuator.h"
#include "soilsensor.h"

// ###### Pins Setting ###########

fan actuatorFan(7);
pump actuatorPump(2);

DHT dhtIn(12, DHT11);
DHT dhtOut(13, DHT11);

sensor tempAndHumdiSensor(12, 13);
soilsensor soilPinSensor(4, 5, 6);

void setup()
{
  Serial.begin(9600);
  dhtIn.begin();
  dhtOut.begin();
}

void loop()
{
  // unsigned long lastCheck = 0;
  // const unsigned long interval = 5UL * 60UL * 1000UL;
  // unsigned long currentMills = millis();

  // if (currentMills - lastCheck >= interval)
  //{
  //  ####### read sensor ########
  if (tempAndHumdiSensor.read())
  {
    Serial.print(tempAndHumdiSensor.getTempInside());
    Serial.print(",");
    Serial.print(tempAndHumdiSensor.getTempOutside());
    Serial.print(",");
    Serial.print(tempAndHumdiSensor.getHumidity());
    Serial.print(",");
  }
  else
  {
    Serial.println(NAN);
  }
  // ######### read siol sensors ########

  if (soilPinSensor.getSoilHumidPin1() || soilPinSensor.getSoilHumidPin2() || soilPinSensor.getSoilHumidPin3())
  {
    Serial.print(soilPinSensor.getSoilHumidPin1());
    Serial.print(",");
    Serial.print(soilPinSensor.getSoilHumidPin2());
    Serial.print(",");
    Serial.print(soilPinSensor.getSoilHumidPin3());
    Serial.print(",");
  }
  else
  {
    Serial.println(NAN);
    delay(2000);
  }

  // ####### check fan status ########

  if (actuatorFan.getIsOn())
  {
    Serial.print(actuatorFan.getIsOn());
    Serial.print(",");
  }
  else if (actuatorFan.getIsOff())
  {
    Serial.print(actuatorFan.getIsOff());
    Serial.print(",");
  }
  else
  {
    Serial.println(NAN);
    Serial.print(",");
  }

  // ########## check pump status #######

  if (actuatorPump.getIsOn())
  {
    Serial.println(actuatorPump.getIsOn());
  }
  else if (actuatorPump.getIsOff())
  {
    Serial.println(actuatorPump.getIsOff());
  }
  else
  {
    Serial.println(NAN);
  }

  // ######## Pump control by Humdimity sensors ##################
  if (soilPinSensor.read())
  {
    if ((soilPinSensor.getSoilHumidPin1() <= 60 || soilPinSensor.getSoilHumidPin2() <= 60 || soilPinSensor.getSoilHumidPin3()) <= 60)
    {
      actuatorPump.turnOn();
      delay(5000);
    }
    else
    {
      actuatorPump.turnOff();
    }
  }

  // ######## Fans control by temperture sensor in Greenhouse ##################
  if (tempAndHumdiSensor.read())
  {
    if (tempAndHumdiSensor.getTempInside() > 27)
    {
      actuatorFan.turnOn();
    }
    else
    {
      actuatorFan.turnOff();
    }
  }
  delay(2000);
}