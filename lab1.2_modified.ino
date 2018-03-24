/*
Lab 1.2
Write a sketch which performs the following logic functions on the switch inputs 
and displays the result on the outputs.  You need two switches and one LED for each  (if you like you can display all four functions at once).
Show the results to your lab partner and double-check the truth tables.

  AND     hint:  C language  “&”
  OR      hint:  C language “|”
  NOR
  XOR     hint:  C language “^”

*/

/* NOTE:
 In lab, my design initially performed one logic function at a time.
 After watching the youtube tutorial https://www.youtube.com/watch?v=KaYsxzcTO_c after lab,
 I adopted his design so I could cycle through the logic functions.
 */

// DECLARE PINS //

//Toggle this switch to switch between logic functions
const int TogglePin = 11;

// 3 leds which indicate the function TogglePin has switched to
const int ledOrOutPin = 3;
const int ledAndOutPin = 4;
const int ledXorOutPin = 5;

// input switches
const int inputAPin = 13;
const int inputBPin = 12;

//LED which gives the result
const int ledOutputPin = 2;

// INITIALIZE VARIABLES //

//initialize which function we will execute
int func = 0;

// initialize inputs and outputs
int A = LOW;
int B = LOW;
int output = LOW;

void setup() {

  //our input pins are TogglePin, inputAPin and inputBPin
  pinMode(TogglePin,INPUT);
  pinMode(inputAPin,INPUT);
  pinMode(inputBPin,INPUT);

  //our output pins are the 'result LED' as well as the 3 LEDs which indicate which function TogglePin has switched to
  pinMode(ledOutputPin,OUTPUT);
  pinMode(ledOrOutPin, OUTPUT);
  pinMode(ledAndOutPin, OUTPUT);
  pinMode(ledXorOutPin, OUTPUT);
  
}

void loop() {
  // if TogglePin has been toggled, switch to the next logic function
  if (digitalRead(TogglePin)) {
    func = (func + 1 ) % 3;
  }

  //read in our input pins
  A = digitalRead(inputAPin);
  B = digitalRead(inputBPin);

  switch (func) {

    case 0: // XOR
      digitalWrite(ledXorOutPin,HIGH);
      digitalWrite(ledAndOutPin, LOW);
      digitalWrite(ledOrOutPin, LOW);
      output = (A != B );
      digitalWrite(ledOutputPin,output);
      break;
      
    case 1: // AND
      digitalWrite(ledXorOutPin,LOW);
      digitalWrite(ledAndOutPin, HIGH);
      digitalWrite(ledOrOutPin, LOW);
      output = (A || B );
      digitalWrite(ledOutputPin,output);
      break;
   
    case 2: // OR
      digitalWrite(ledXorOutPin,LOW);
      digitalWrite(ledAndOutPin, LOW);
      digitalWrite(ledOrOutPin, HIGH);
      output = (A && B );
      digitalWrite(ledOutputPin,output);
      break;   

    default: // No function
      digitalWrite(ledXorOutPin,LOW);
      digitalWrite(ledAndOutPin, LOW);
      digitalWrite(ledOrOutPin, LOW);
      digitalWrite(ledOutputPin, LOW);
  }
  delay(250);
}
