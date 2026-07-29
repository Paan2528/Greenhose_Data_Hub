// Wasserpumpe an und aus 
const int buttonPin = /; // Pin Hinzufügen
const int pumpPin = /; // Pin Hinzufügen

bool pumpState = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    pumpState = !pumpState;
    digitalWrite(pumpPin, pumpState);
    delay(50);
  }

  lastButtonState = buttonState;
}
