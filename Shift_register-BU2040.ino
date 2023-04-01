/**
SHIFT REGISTER 12 bits with latch
TRYING TO REPLACE A BU2040F CHIP

pulse has 20uS 

USING INTERRUPTS
**/

//DEFINE PORTS
#define DATA 2 //PIN 2
#define CLK  3 //PIN 3

#define O11 1<<4 //PIN A1
#define O10 1<<5 //PIN A0
#define O09 1<<6 //PIN 13
#define O08 1<<7 //PIN 12
#define O07 1<<0 //PIN 11
#define O06 1<<1 //PIN 10
#define O05 1<<2 //PIN 9
#define O04 1<<3 //PIN 8
#define O03 1<<4 //PIN 7
#define O02 1<<5 //PIN 6
#define O01 1<<0 //PIN 5
#define O00 1<<1 //PIN 4

byte outputs[] = { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW };
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
  if (outputs[0] == HIGH) { PORTD |= O11; } else { PORTD &= ~O11;}
  if (outputs[1] == HIGH) { PORTD |= O10; } else { PORTD &= ~O10;}
  if (outputs[2] == HIGH) { PORTD |= O09; } else { PORTD &= ~O09;}
  if (outputs[3] == HIGH) { PORTD |= O08; } else { PORTD &= ~O08;}
  //PORTB
  if (outputs[4] == HIGH) { PORTB |= O07; } else { PORTB &= ~O07;}
  if (outputs[5] == HIGH) { PORTB |= O06; } else { PORTB &= ~O06;}
  if (outputs[6] == HIGH) { PORTB |= O05; } else { PORTB &= ~O05;}
  if (outputs[7] == HIGH) { PORTB |= O04; } else { PORTB &= ~O04;}
  if (outputs[8] == HIGH) { PORTB |= O03; } else { PORTB &= ~O03;}
  if (outputs[9] == HIGH) { PORTB |= O02; } else { PORTB &= ~O02;}
  //PORTC --> PORTC is analog, maybe is slow, maybe is beter to use PORTD0, PORTD1
  if (outputs[11] == HIGH) { PORTC |= O01; } else { PORTC &= ~O01;}
  if (outputs[12] == HIGH) { PORTC |= O00; } else { PORTC &= ~O00;}
}
