/********************************************************************
*
*   Memory-Game V1.2
*   Florian Ulmschneider
*   18.01.2015
*
********************************************************************/


#include <Entropy.h>
#include <avr/power.h>

int turn = 0;

byte randomArray[100]; // stores the random sequence that is generated each turn

byte prevInput;
byte input;

void setup() {
  Entropy.initialize();
  
  power_adc_disable();
  power_usi_disable();
 
  disableInputs();
  
  swipe(60);
  
  delay(200);
  
  while(1) {
    
    //generate, display and store a random sequence
    for(int i = 0; i <= turn; i++) {
      randomArray[i] = Entropy.random(4);
      digitalWrite(randomArray[i],0);
      delay(500);
      digitalWrite(randomArray[i],1);
      delay(200);
    }
    
    delay(300);
    
    //blink to indicate players turn
    blink(200);
    
    //look for buttonpresses and compare them to the required ones
    enableInputs();
    for(int i = 0; i <= turn; i++) {
      if(buttonPressed() != randomArray[i]) {
        goto gameover;
      }
      delay(100);
    }
    disableInputs();
    
    turn++;
    swipe(60);
    delay(200);
  }
  
  gameover:
  
  //display the score in binary 
  disableInputs();
  blink(200);
  delay(100);
  blink(200);
  show(turn);
}


void loop() {
  
}

void swipe(int del) {

  //lights up the leds from left to right
  
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

  //blinks all leds
  
  PORTB = 0x00;
  delay(del);
  PORTB = 0x0f;
}

void enableInputs() {

  //enables the inputs and pullups
  
  DDRB = 0xf0;
  PORTB = 0xff;
}

void disableInputs() {

  //enables the outputs
  
  DDRB = 0xff;
  PORTB = 0x0f;
}

byte buttonPressed() {

  //returns the pressed button
  
  while(1) {
    prevInput = PINB & 0x0f;
    delay(5);
    
    //checks whether there was a transition from high to low
    if(prevInput==0x0f) {
      switch(PINB & 0x0f) {
        case 0b00001110:
          return 0;
        case 0b00001101:
          return 1;
        case 0b00001011:
          return 2;
        case 0b00000111:
          return 3;
      }
    }
  }
}

void show(byte num) {
  
  //displays a number up to 15
  
  if(num < 16) {
    byte outputNum;
    byte j=3;
    //flip the first four bits
    for (byte i=0; i<4; i++) {
      bitWrite(outputNum, i, bitRead(num, j));
      j--;
    }
    //invert the first four bits
    PORTB = outputNum^0x0f;
  }else {
    //turn off all leds
    PORTB = 0x0f;
  }
}