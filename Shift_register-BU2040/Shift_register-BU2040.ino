/**
SHIFT REGISTER 12 bits with latch
TRYING TO REPLACE A BU2040F CHIP

pulse has 20uS 

USING INTERRUPTS

BU2040F  ARDUINO
DATA     PIN 2
CLOCK    PIN 3
Q0       PIN 4
Q1       PIN 5
Q2       PIN 6
Q3       PIN 7
Q4       PIN 8
Q5       PIN 9
Q6       PIN 10
Q7       PIN 11
Q8       PIN 12
Q9       PIN 13
Q10      PIN A0
Q11      PIN A1
**/

//DEFINE PORTS
#define DATA 2 //PIN 2
#define CLK  3 //PIN 3
#define C_DATA 1<<2 //PIN 2
#define C_CLK  1<<3 //PIN 3

//PORTD
#define C11 1<<4 //PIN A1
#define C10 1<<5 //PIN A0
#define C09 1<<6 //PIN 13
#define C08 1<<7 //PIN 12
//PORTB
#define C07 1<<0 //PIN 11
#define C06 1<<1 //PIN 10
#define C05 1<<2 //PIN 9
#define C04 1<<3 //PIN 8
#define C03 1<<4 //PIN 7
#define C02 1<<5 //PIN 6
//PORTC
#define C01 1<<0 //PIN 5
#define C00 1<<1 //PIN 4

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


byte outputs[] = { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW };
int output = 0;
byte data = 0x0;
byte lastClk = 0x0;

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

  attachInterrupt(INT1, handleClk, CHANGE);
}

void loop() {
  //Nothing to do! waiting for interrupt
}

void handleClk() {
  byte clk =  PIND & (C_CLK);
  byte data = PIND & (C_DATA);
  if (clk) {
    //rise clk
    if (output < 12) {
      if (data) outputs[output] = HIGH; else outputs[output] = LOW;
    }
    output++;
  } else {
    //fall clk
    if (data) {
      writeOutFast();
      output = 0;
    }
  }
}

void writeOutSlow() {
  if (outputs[0] == HIGH) { digitalWrite(O00, HIGH); } else { digitalWrite(O00, LOW); }
  if (outputs[1] == HIGH) { digitalWrite(O01, HIGH); } else { digitalWrite(O01, LOW); }
  if (outputs[2] == HIGH) { digitalWrite(O02, HIGH); } else { digitalWrite(O02, LOW); }
  if (outputs[3] == HIGH) { digitalWrite(O03, HIGH); } else { digitalWrite(O03, LOW); }
  //PORTB
  if (outputs[4] == HIGH) { digitalWrite(O04, HIGH); } else { digitalWrite(O04, LOW); }
  if (outputs[5] == HIGH) { digitalWrite(O05, HIGH); } else { digitalWrite(O05, LOW); }
  if (outputs[6] == HIGH) { digitalWrite(O06, HIGH); } else { digitalWrite(O06, LOW); }
  if (outputs[7] == HIGH) { digitalWrite(O07, HIGH); } else { digitalWrite(O07, LOW); }
  if (outputs[8] == HIGH) { digitalWrite(O08, HIGH); } else { digitalWrite(O08, LOW); }
  if (outputs[9] == HIGH) { digitalWrite(O09, HIGH); } else { digitalWrite(O09, LOW); }
  //PORTC --> PORTC is analog, maybe is slow, maybe is beter to use PORTD0, PORTD1
  if (outputs[10] == HIGH) { digitalWrite(O10, HIGH); } else { digitalWrite(O10, LOW); }
  if (outputs[11] == HIGH) { digitalWrite(O11, HIGH); } else { digitalWrite(O11, LOW); }
}

void writeOutFast() {
  //UGLY, BUT FASTER!
  //PORTD
  if (outputs[0] == HIGH) { PORTD |= C11; } else { PORTD &= ~C11;}
  if (outputs[1] == HIGH) { PORTD |= C10; } else { PORTD &= ~C10;}
  if (outputs[2] == HIGH) { PORTD |= C09; } else { PORTD &= ~C09;}
  if (outputs[3] == HIGH) { PORTD |= C08; } else { PORTD &= ~C08;}
  //PORTB
  if (outputs[4] == HIGH) { PORTB |= C07; } else { PORTB &= ~C07;}
  if (outputs[5] == HIGH) { PORTB |= C06; } else { PORTB &= ~C06;}
  if (outputs[6] == HIGH) { PORTB |= C05; } else { PORTB &= ~C05;}
  if (outputs[7] == HIGH) { PORTB |= C04; } else { PORTB &= ~C04;}
  if (outputs[8] == HIGH) { PORTB |= C03; } else { PORTB &= ~C03;}
  if (outputs[9] == HIGH) { PORTB |= C02; } else { PORTB &= ~C02;}
  //PORTC --> PORTC is analog, maybe is slow, maybe is beter to use PORTD0, PORTD1
  if (outputs[10] == HIGH) { PORTC |= C01; } else { PORTC &= ~C01;}
  if (outputs[11] == HIGH) { PORTC |= C00; } else { PORTC &= ~C00;}
}
