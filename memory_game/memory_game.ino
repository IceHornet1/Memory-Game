


void setup() {
  swipe(80);
}


void loop() {
  
}

void swipe(int del) {
  DDRB = 0xff;
  
  PORTB = 0b00001111;
  delay(del);
  PORTB = 0b00000111;
  delay(del);
  PORTB = 0b00000011;
  delay(del);
  PORTB = 0b00001011;
  delay(del);
  PORTB = 0b00001001;
  delay(del);
  PORTB = 0b00001101;
  delay(del);
  PORTB = 0b00001100;
  delay(del);
  PORTB = 0b00001110;
  delay(del);
  PORTB = 0b00001111;
}