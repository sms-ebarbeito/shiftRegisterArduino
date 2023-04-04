/**
TESTER! CLOCK + DATA 1 + DATA 2

**/

//DEFINE PORTS

#define CLK   2 //PIN 2
#define DATA1 3 //PIN 3
#define DATA2 4 //PIN 4

#define LED  13

void setup() {
  pinMode(CLK,   OUTPUT);
  pinMode(DATA1, OUTPUT);
  pinMode(DATA2, OUTPUT);
  pinMode(LED,   OUTPUT);

  Serial.begin(115200);
  Serial.println("DEBUG MODE");
  Serial.println("SENDING SIGNALS D1 D2 CLK");
  digitalWrite(CLK, LOW);
  digitalWrite(DATA1, LOW);
  digitalWrite(DATA2, LOW);
  
}

void loop() {
  //111100000010 DATA 1 AZUL
  //111110011100 DATA 2 AMARILLO

  digitalWrite(LED, HIGH);
  setData(true,  true,  false);
  setData(true,  true,  false);
  setData(true,  true,  false);
  setData(true,  true,  false);
  setData(false, true,  false);
  setData(false, true, false);
  setData(false, false, false);
  setData(false, true,  false);
  setData(false, true,  false);
  setData(false, true,  false);
  setData(true,  false, false);
  setData(false, false, true);
  digitalWrite(LED, LOW);
  delay(1000);
  
}

void setData(bool d1, bool d2, bool finish) {
  if (d1) digitalWrite(DATA1, HIGH); else digitalWrite(DATA1, LOW);
  if (d2) digitalWrite(DATA2, HIGH); else digitalWrite(DATA2, LOW);
  //delay(1);
  digitalWrite(CLK, HIGH);
  //delay(1);
  if (finish) {
    digitalWrite(DATA1, HIGH);
    digitalWrite(DATA2, HIGH);
    //delay(1);
    digitalWrite(CLK, LOW);
    //delay(1);
    digitalWrite(DATA1, LOW);
    digitalWrite(DATA2, LOW);
    
  } else {
    digitalWrite(DATA1, LOW);
    digitalWrite(DATA2, LOW);
    //delay(1);
    digitalWrite(CLK, LOW);
  }
  //delay(1);

}
