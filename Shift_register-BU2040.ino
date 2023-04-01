/**
SHIFT REGISTER 12 bits with latch
TRYING TO REPLACE A BU2040F CHIP

pulse has 20uS 

USING INTERRUPTS
**/

//#include <digitalWriteFast.h>

//DEFINE PORTS
#define DATA 2 //PIN 2
#define CLK  3 //PIN 3

#define O11 15 //PIN A1
#define O10 14 //PIN A0
#define O09 13 //PIN 13
#define O08 12 //PIN 12
#define O07 11 //PIN 11
#define O06 10 //PIN 10
#define O05 9 //PIN 9
#define O04 8 //PIN 8
#define O03 7 //PIN 7
#define O02 6 //PIN 6
#define O01 5 //PIN 5
#define O00 4 //PIN 4

int outputs[] = { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW };
int output = 0;
byte data = 0x0;

void setup() { 
  //Initialize pins as input output
  pinMode(CLK, INPUT);
  pinMode(DATA, INPUT);
  
  pinMode(O00, OUTPUT);
  pinMode(O01, OUTPUT);
  pinMode(O02, OUTPUT);
  pinMode(O03, OUTPUT);
  pinMode(O04, OUTPUT);
  pinMode(O05, OUTPUT);
  pinMode(O06, OUTPUT);
  pinMode(O07, OUTPUT);
  pinMode(O08, OUTPUT);
  pinMode(O09, OUTPUT);
  pinMode(O10, OUTPUT);
  pinMode(O11, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(CLK),  ISR_handleClk, CHANGE);
}

void loop() {
  //Maybe nothing??
}


void ISR_handleClk() {
  data = PIND & (1<<2); //DATA
  if ( PIND & (1<<3) ) {  
    // CLK RISING
    if (output < 12) {
      outputs[output] = data;
    }
    output++;  
  } else { 
    //CLOCK FALLING
    if (data) { //If data is still HIGH, latch!
      //latch all outputs and reset counter
      writeOut();
      output = 0;
    }
  }
  
}

void writeOut() {
  //UGLY, BUT FASTER!
  //PORTD
  if (outputs[0] == HIGH) { PORTD |= 1<<4; } else { PORTD &= ~1<<4;}
  if (outputs[1] == HIGH) { PORTD |= 1<<5; } else { PORTD &= ~1<<5;}
  if (outputs[2] == HIGH) { PORTD |= 1<<6; } else { PORTD &= ~1<<6;}
  if (outputs[3] == HIGH) { PORTD |= 1<<7; } else { PORTD &= ~1<<7;}
  //PORTB
  if (outputs[4] == HIGH) { PORTB |= 1<<0; } else { PORTB &= ~1<<0;}
  if (outputs[5] == HIGH) { PORTB |= 1<<1; } else { PORTB &= ~1<<1;}
  if (outputs[6] == HIGH) { PORTB |= 1<<2; } else { PORTB &= ~1<<2;}
  if (outputs[7] == HIGH) { PORTB |= 1<<3; } else { PORTB &= ~1<<3;}
  if (outputs[8] == HIGH) { PORTB |= 1<<4; } else { PORTB &= ~1<<4;}
  if (outputs[9] == HIGH) { PORTB |= 1<<5; } else { PORTB &= ~1<<5;}
  //PORTC --> PORTC is analog, maybe is slow, maybe is beter to use PORTD0, PORTD1
  if (outputs[11] == HIGH) { PORTC |= 1<<0; } else { PORTC &= ~1<<0;}
  if (outputs[12] == HIGH) { PORTC |= 1<<1; } else { PORTC &= ~1<<1;}
}
