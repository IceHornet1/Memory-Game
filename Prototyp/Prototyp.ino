
const int inputPin = 2;
const int inputEnablePin = 3;

void setup() {
  pinMode(inputEnablePin, OUTPUT);
  pinMode(inputPin, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(inputEnablePin, LOW);
  digitalWrite(inputPin, LOW);
}

void loop() {
  //digitalWrite(13, digitalRead(inputPin));
}