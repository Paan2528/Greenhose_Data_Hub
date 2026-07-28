/*
Temp. sensor (in/out)
Humdity sensor (in)
*/

const int tempsensorIn_Pin = A0; // check pin again
const int tempsensorOut_Pin = A0; // check pin again
const int humdisensorPin = A0; // check pin again
 setup() {
  serial:begin(9600);
}

void loop() {
  float sensor_temp_in = analogRead(tempsensorIn_Pin);
  float sensor_temp_out = analogRead(tempsensorOut_Pin);
  float sensor_humdity = analogRead(humdisensorPin);

  Serial.print("Temperature in greenhouse: ");
  Serial.print(sensor_temp_in);
  Serial.print("Temperature outside of greenhouse: ");
  Serial.print(sensor_temp_out);
  Serial.print("Humidity: ");
  Serial.print(sensor_humdity);

  delay(1000);
  
}
