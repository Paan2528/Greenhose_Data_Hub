#include <Arduino.h>
#include "actuator.h"

fan myFan(5);   // Pin4
pump myPump(6); // pin5

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  myFan.turnOn();
  Serial.println(myFan.getIsOn());
  delay(5000);
  myFan.turnOff();
  delay(5000);

  myPump.turnOn();
  Serial.println(myFan.getIsOn());
  delay(5000);
  myPump.turnOff();
  delay(5000);
}
