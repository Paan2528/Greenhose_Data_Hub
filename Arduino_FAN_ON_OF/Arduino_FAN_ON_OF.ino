// Lüftersteuerung an aus mit stufen von 0 - 255
int fanPin = /; // pin hinzufügen
int buttonPin = /; //pin hinzufügen

int stufen[] = {0, 100, 150, 200, 255};
int anzahlStufen = 5;
int aktuelleStufe = 0;

int letzterZustand = HIGH;

void setup() {
  // put your setup code here, to run once:
  pinMode(fanPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  int zustand = digitalRead(buttonPin);

  if (zustand == LOW && letzterZustand == HIGH) {
    aktuelleStufe = (aktuelleStufe + 1) % anzahlStufen;
    analogWrite(fanPin, stufen[aktuelleStufe]);
    delay(50);
  }

  letzterZustand = zustand;

}
