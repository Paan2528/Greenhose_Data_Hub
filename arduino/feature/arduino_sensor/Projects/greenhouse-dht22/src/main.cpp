#include <Arduino.h>
#include "sensor.h"
#include "actuator.h"
#include "soilsensor.h"

// ###### Pins Setting ###########
fan myFan(7);
pump myPump(8);

DHT dhtIn(2, DHT11);
DHT dhtOut(3, DHT11);

sensor mySensors(2, 2);

soilsensor soilPinSensor(1, 2, 3);

void setup()
{
  Serial.begin(9600);
  dhtIn.begin();
  dhtOut.begin();
}

void loop()
{
  unsigned long lastCheck = 0;
  const unsigned long interval = 5UL * 60UL * 1000UL;
  unsigned long currentMills = millis();

  if (currentMills - lastCheck >= interval)
  {
    // ####### read sensor ########
    if (mySensors.read())
    {
      Serial.println(mySensors.getTempInside());
      Serial.println(mySensors.getTempOutside());
      Serial.println(mySensors.getHumidity());
    }
    else
    {
      Serial.println(NAN);
    }
    // ####### check fan status ########
    if (myFan.getIsOn())
    {
      Serial.println(myFan.getIsOn());
    }
    else if (myFan.getIsOff())
    {
      Serial.println(myFan.getIsOff());
    }
    else
    {
      Serial.println(NAN);
    }

    // ########## check pump status #######
    if (myPump.getIsOn())
    {
      Serial.println(myPump.getIsOn());
    }
    else if (myPump.getIsOff())
    {
      Serial.println(myPump.getIsOff());
    }
    else
    {
      Serial.println(NAN);
    }

    // ######### read siol sensors ########
    if (soilPinSensor.getSoilHumidPin1() || soilPinSensor.getSoilHumidPin2() || soilPinSensor.getSoilHumidPin3())
    {
      Serial.println(soilPinSensor.getSoilHumidPin1());
      Serial.println(soilPinSensor.getSoilHumidPin2());
      Serial.println(soilPinSensor.getSoilHumidPin3());
    }
    else
    {
      Serial.println(NAN);
    }
  }

  // ######## Pump control by Humdimity sensors ##################
  if (soilPinSensor.read())
  {
    if (soilPinSensor.getSoilHumidPin1() || soilPinSensor.getSoilHumidPin2() || soilPinSensor.getSoilHumidPin3() <= 60)
    {
      myPump.turnOn();
      delay(5000);
    }
    else
    {
      myPump.turnOff();
    }
  }
  // ######## Fans control by temperture sensor in Greenhouse ##################
  if (mySensors.read())
  {
    if (mySensors.getTempInside() > 27)
    {
      myFan.turnOn();
    }
    else
    {
      myFan.turnOff();
    }
  }
}
