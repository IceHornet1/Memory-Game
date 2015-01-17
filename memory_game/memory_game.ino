



byte randomArray[100];
byte inputArray[100];

void setup() {
  randomSeed(analogRead(2));
  
  swipe(80);
  
  for(int x = 0; x<20; x++) {
  
    show(x);
    delay(500);
  }
  
  blink(200);
  delay(100);
  blink(200);
  
  DDRB = 0xf0;
  PORTB = 0xff;
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
  delay(del);
}

void blink(int del) {
  DDRB = 0xff;
  
  PORTB = 0b00000000;
  delay(del);
  PORTB = 0b00001111;
}

void show(byte num) {
  DDRB = 0xff;
  if(num < 16) {
    byte outputNum;
    byte j=3;
    //flip the first four bits
    for (byte i=0; i<4; i++ ) {
      bitWrite(outputNum, i, bitRead(num, j));
      j--;
    }
    
    PORTB = outputNum^0x0f;
  }else {
    PORTB = 0x0f;
  }
}