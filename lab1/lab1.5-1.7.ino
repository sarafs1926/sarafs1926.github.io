/*
First we need to figure out how to display information in a more convenient way than in binary on the LEDs. 
You are going to wire up a four-digit display like the one shown below.  
See page 348 in your lab manual or the HP5082-7340 data sheet for wiring details.

Lab 1.5
Wire up one digit of the display.  Connect four digital Arduino pins
to pins 8, 1, 2, 3 of the display.  Connect GND to pin 6 and 5V (from the breadboard) to pin 7.  
Tie pin 4 and 5 to GND.
Write a sketch which outputs various values to the four digital outputs.
Figure out how to display the values “0” through “9”.  
This can be done cleverly in about 3 lines of C code.

Lab 1.6
Disconnect pin 5 of your display from GND and wire to an Arduino digital pin.
This is the LE* (latch enable, active low) input.  When it is at logic ‘0’, 
the display track the inputs.  When it is at logic ‘1’, the display is latched (frozen).
Modify your sketch so that it updates the display as follows:
  Output desired binary value on pins 8, 1, 2, 3
  Output a logic ‘0’ to pin 5
  Output a logic ‘1’ to pin 5
Now the value is latched by the display.

Lab 1.7
Add three more digits to your display.  Wire them just like the first one, except
that the connections to pins 8, 1, 2, 3 should be shared by all the digits (parallel).  
Each digit should have a separate connection from a digital pin to the LE* input.
Write a sketch which displays a four-digit number.  This is a bit of tricky coding,
and you may need to ask for some help.  That’s fine.  Here are some hints:
Update one digit at a time
Use the “/” (division) and “%” (modulo) operators to get each digit’s value
*/

 /* NOTE: I'm only showing Lab 1.7 since it contains the concepts of Lab 1.5 and 1.6 
 In this script I count to 100 on the first 2 digits */

// DECLARE PINS //

// the four binary bits displayed by the four hex digits
const int X1Pin = 2;
const int X2Pin = 3;
const int X4Pin = 4;
const int X8Pin = 5;

// the four enable pins which enable me to write to each of the four digits
const int EnablePin1 = 6;
const int EnablePin2 = 7;
const int EnablePin3 = 8;
const int EnablePin4 = 9;

void setup() {
    //start serial connection
    Serial.begin(9600);

    //all pins are output here
    pinMode(EnablePin1, OUTPUT);
    pinMode(EnablePin2, OUTPUT);
    pinMode(EnablePin3, OUTPUT);
    pinMode(EnablePin4, OUTPUT);
    pinMode(X1Pin, OUTPUT);
    pinMode(X2Pin, OUTPUT);
    pinMode(X4Pin, OUTPUT);
    pinMode(X8Pin, OUTPUT);
}
 
void loop() {
  for(int i=0; i<100; i++){ 
    displayLogic(i);
    delay(500); 
  }
}
 
bool displayLogic(long numeric)
{
  if(numeric >=0 && numeric < 100){
    Serial.println(numeric);
    int onesplace = numeric % 10;
    int tensplace = numeric / 10 % 10;

    //latch the upper two digits
    digitalWrite(EnablePin3, HIGH);  
    digitalWrite(EnablePin4, HIGH);  

    //track the lower two digits
    digitalWrite(EnablePin1, LOW);           
    digitalWrite(EnablePin2, LOW);      

    //write the 'ones-place' value to the lowest digit
    // first set data pins, then latch the digit 
    digitalWrite(X1Pin, (onesplace >> 0) & 1); //test if the LSB is a 1 or a 0.
    digitalWrite(X2Pin, (onesplace >> 1) & 1); //shift 1 place and test if bit is a 1 or a 0
    digitalWrite(X4Pin, (onesplace >> 2) & 1); //shift 2 places and test if bit is a 1 or a 0
    digitalWrite(X8Pin, (onesplace >> 3) & 1); //shift 3 places and test if bit is a 1 or a 0 
    digitalWrite(EnablePin1, HIGH);           

    //write the 'tens-place' value to the second-lowest digit
    // first set data pins, then latch the digit 
    digitalWrite(X1Pin, (tensplace >> 0) & 1); 
    digitalWrite(X2Pin, (tensplace >> 1) & 1); 
    digitalWrite(X4Pin, (tensplace >> 2) & 1); 
    digitalWrite(X8Pin, (tensplace >> 3) & 1); 
    digitalWrite(EnablePin2, HIGH);          
    
    return 1;
  }
  else{
  }
}
