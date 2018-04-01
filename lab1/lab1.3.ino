/*
Lab 1.3
Connect a push-button to a digital pin on your Arduino.
Write a sketch which counts inputs from the button in binary and displays the count on the LEDs.
*/

// DECLARE PINS //

// if this switch is on, we count in binary
const int CountPin = 13;

// 4 LEDs that display the binary bits
const int X1Pin = 2;
const int X2Pin = 3;
const int X4Pin = 4;
const int X8Pin = 5;

// INITIALIZE VARIABLES //

int counterstate = 0;
int count = 0;

void setup() { 
  //start serial connection
  Serial.begin(9600);

  //our input pin is the counter switch 
  pinMode(CountPin,INPUT);

  //our output pins are the 4 LEDs that display the binary bits
  pinMode(X1Pin,OUTPUT); 
  pinMode(X2Pin,OUTPUT);
  pinMode(X4Pin,OUTPUT); 
  pinMode(X8Pin,OUTPUT);
  }

void loop() { 

  //first, write LOW to all the LEDs
  digitalWrite(X1Pin, LOW); 
  digitalWrite(X2Pin, LOW); 
  digitalWrite(X4Pin, LOW); 
  digitalWrite(X8Pin, LOW); 

  //read in the state of the counter switch
  counterstate = digitalRead(CountPin);

  if(counterstate == LOW) { // In binary we display 0000
  } 
  
  else { // We count upwards in binary

    //increase counter by 1
    count++;
    
    delay(250); 

    //print count to serial monitor
    Serial.print(count);

    //use the remainders of count to determine whether the LEDs are low or high:
    
    if((count % 2) > 0) { 
      digitalWrite(X1Pin, HIGH); 
      } 
    else { 
      digitalWrite(X1Pin, LOW); 
      }

    if((count % 4) > 1) { 
      digitalWrite(X2Pin, HIGH); 
      } 
    else { 
      digitalWrite(X2Pin, LOW); 
      }

    if((count % 8) > 3) { 
      digitalWrite(X4Pin, HIGH); 
      } 
    else { 
      digitalWrite(X4Pin, LOW); 
      }

    if((count % 16) > 7) { 
      digitalWrite(X8Pin, HIGH); 
      } 
    else { 
      digitalWrite(X8Pin, LOW); 
      }
      
  delay(250); 
  } 
}

