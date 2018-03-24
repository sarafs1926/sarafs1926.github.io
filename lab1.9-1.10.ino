/*
Lab 1.9
Connect a potentiometer to provide an adjustable DC voltage from 0 to 5V
and wire it to the A0 (analog input 0) pin of your Arduino.
Use the analogRead function to measure the voltage on the potentiometer, and
use the code you wrote above to display the value on the digital display.

Lab 1.10
Modify your sketch to calibrate the display so it reads in volts, 
i.e. from 0.000 to 5.000.  Compare the results with a VOM.  Is it accurate?  If not, how could you improve it?
 */

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

const int AnalogInPin = A1;


// INITIALIZE VARIABLES //

//current state of the switch (LOW = switch on since using pullup resistors)
int counterstate = 0;

int trycount = 0;

void setup() {
    //start serial connection
    Serial.begin(9600);
    
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
  int sensorValue = analogRead(AnalogInPin);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  voltage = voltage*1000;
  voltage = int(voltage);
  // print out the read value to serial monitor
  Serial.println(voltage);
  // display that value on the 4 hex digits
  displayLogic(voltage);
}
        
bool displayLogic(long numeric)
{
        int onesplace = numeric % 10;
        int tensplace = numeric / 10 % 10;
        int hundplace = numeric / 100 % 10;
        int thouplace = numeric / 1000 % 10;
        
        digitalWrite(EnablePin1, LOW);           
        digitalWrite(EnablePin2, LOW); 
        digitalWrite(EnablePin3, LOW);           
        digitalWrite(EnablePin4, LOW);      

        digitalWrite(X1Pin, (onesplace >> 0) & 1); 
        digitalWrite(X2Pin, (onesplace >> 1) & 1); 
        digitalWrite(X4Pin, (onesplace >> 2) & 1); 
        digitalWrite(X8Pin, (onesplace >> 3) & 1);
        digitalWrite(EnablePin1, HIGH);           

        digitalWrite(X1Pin, (tensplace >> 0) & 1);
        digitalWrite(X2Pin, (tensplace >> 1) & 1);
        digitalWrite(X4Pin, (tensplace >> 2) & 1); 
        digitalWrite(X8Pin, (tensplace >> 3) & 1); 
        digitalWrite(EnablePin2, HIGH);      
        
        digitalWrite(X1Pin, (hundplace >> 0) & 1); 
        digitalWrite(X2Pin, (hundplace >> 1) & 1); 
        digitalWrite(X4Pin, (hundplace >> 2) & 1); 
        digitalWrite(X8Pin, (hundplace >> 3) & 1);
        digitalWrite(EnablePin3, HIGH);           

        digitalWrite(X1Pin, (thouplace >> 0) & 1);
        digitalWrite(X2Pin, (thouplace >> 1) & 1);
        digitalWrite(X4Pin, (thouplace >> 2) & 1); 
        digitalWrite(X8Pin, (thouplace >> 3) & 1); 
        digitalWrite(EnablePin4, HIGH);          
        
        return 1;

}

