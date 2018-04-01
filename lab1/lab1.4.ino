/*
Modify Lab 1.3 to count seconds, starting and stopping when the button
is pressed.  Display the seconds in binary on the LEDs.
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

//current state of the switch (LOW = switch on since using pullup resistors)
int counterstate = 0;

// milliseconds the switch was on
long millis_on = 0;    
// seconds the switch was on
long secs_on = 0;      
// how long the switch was on in the previous check
long prev_secs_on = 0;
// how long since switch turned on 
unsigned long millis_starttime = 0; 

int count = 0;
byte prev_counterstate = HIGH;

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
  
  digitalWrite(CountPin, HIGH);  // initialize the switch input

  }

void loop() {

  //first, write LOW to all the LEDs
  digitalWrite(X1Pin, LOW); 
  digitalWrite(X2Pin, LOW); 
  digitalWrite(X4Pin, LOW); 
  digitalWrite(X8Pin, LOW); 

  //read in the state of the counter switch
  counterstate = digitalRead(CountPin);
  
  // if the switch turns on, record the start time 
  if (counterstate == LOW && prev_counterstate == HIGH && (millis() - millis_starttime) > 200) {
    millis_starttime = millis();
  }

  millis_on = (millis() - millis_starttime);
  secs_on = millis_on / 1000;

  // If switch is truly on (debounced) 
  if (millis_on > 50) {

    if (counterstate == LOW && secs_on > prev_secs_on) {
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
  prev_counterstate = counterstate;
  prev_secs_on = secs_on;
}
