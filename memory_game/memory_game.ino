/********************************************************************
*
*   Memory-Game V1.4
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

byte gamemode;

void setup() {
  Entropy.initialize();
  
  power_adc_disable();
  power_usi_disable();
  
  //determine gamemode
  enableInputs();
  for(int i = 0; i <= 100; i++) {
    input = PINB & 0x0f;
  
    if(input == 0b00001110) {
      gamemode = 1;
      break;
    }else if(input == 0b00001101) {
      gamemode = 2;
      break;
    }else if(input == 0b00001011) {
      gamemode = 3;
      break;
    }else if(input == 0b00000111) {
      gamemode = 4;
      break;
    }else {
      gamemode = 0;
    }
    
    delay(5);
  }
  disableInputs();
  
  delay(200);
  
  if(gamemode == 2 ||gamemode == 3) {
    swipe(50, 1);
  }else {
    swipe(50, 0);
  }
  
  if(gamemode == 4) {
    enableInputs();
    randomArray[turn] = buttonPressed();
    disableInputs();
    delay(200);
    swipe(50, 1);
  }
  
  delay(500);
  
  while(1) {
    
    if(gamemode == 0 || gamemode == 2) {
      //add a random number
      randomArray[turn] = Entropy.random(4);
    }
    else if(gamemode == 1 || gamemode == 3) {
      //create new random numbers
      for(int i = 0; i <= turn; i++) {
        randomArray[i] = Entropy.random(4);
      }
    }
    if(gamemode != 4) {
      //generate, display and store a random sequence
      for(int i = 0; i <= turn; i++) {
        digitalWrite(randomArray[i],0);
        delay(500);
        digitalWrite(randomArray[i],1);
        delay(200);
      }
    }
    
    //look for buttonpresses and compare them to the required ones
    enableInputs();
    int j = turn;
    for(int i = 0; i <= turn; i++) {
      if(gamemode == 0 || gamemode == 1 || gamemode == 4) {
        if(buttonPressed() != randomArray[i]) {
          goto gameover;
        }
      }else if(gamemode == 2 || gamemode == 3) {
        if(buttonPressed() != randomArray[j]) {
          goto gameover;
        }
      }
      delay(10);
      j--;
    }
    
    turn++;
    
    if(gamemode == 4) {
      randomArray[turn] = buttonPressed();
    }
    disableInputs();
    
    delay(200);
    
    if(gamemode == 2 || gamemode == 3 || (gamemode == 4 && turn % 2 == 0)) {
      swipe(50, 1);
    }else {
      swipe(50, 0);
    }
    
    delay(500);
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

void swipe(int del, boolean dir) {
  
  PORTB = 0b00001111;
  delay(del);
  
  for(byte i = 0; i < 5; i++) {
    if(dir == 0) {
      //left
      PORTB = (0b00001000 >> i)^0x0f;
    }else {
      //right
      PORTB = (0b00000001 << i)^0x0f;
    }
    delay(del);
  }
}

void blink(int del) {

  //blinks all leds
  
  PORTB = 0x00;
  delay(del);
  PORTB = 0x0f;
}

void enableInputs() {

  //enables the inputs and pullups
  
  DDRB = 0x10;
  PORTB = 0x1f;
}

void disableInputs() {

  //enables the outputs
  
  DDRB = 0x1f;
  PORTB = 0x0f;
}

byte buttonPressed() {

  //returns the pressed button
  
  while(1) {
    //set the last 4 bits 0
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