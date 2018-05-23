/*
3.5
Write a sketch which will turn the A/B/C/D outputs on in sequence as shown in the table above. 
Add a delay of 10 ms after you update all four outputs.
What happens to the motor?
How many steps does it take to complete one rotation? (NOTE: 200, since each step is 1.8 degrees)
 */
 
// DECLARE PINS //
const int pin1 = 8;
const int pin2 = 9;
const int pin3 = 10;
const int pin4 = 11;

// INITIALIZE VARIABLES //
int delaytime = 100;

void setup() {
  Serial.begin(9600);     
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT); 
  pinMode(pin3, OUTPUT); 
  pinMode(pin4, OUTPUT);
}

void loop(){
  int numberOfSteps = 200;
  step_OFF();   
  while(numberOfSteps>0){
    fullstep_forward();   
    numberOfSteps -- ;
    //Serial.println(numberOfSteps);
  }
  delay(10000);
}

//FUNCTIONS

void fullstep_1(){
  digitalWrite(pin1, HIGH); 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, HIGH); 
  digitalWrite(pin4, LOW); 
  //Serial.println("fullstep1");
}
void fullstep_2(){
  digitalWrite(pin1, HIGH); 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, HIGH);
  //Serial.println("fullstep2");
 
}
void fullstep_3(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, HIGH); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, HIGH); 
  //Serial.println("fullstep3");

}
void fullstep_4(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, HIGH); 
  digitalWrite(pin3, HIGH); 
  digitalWrite(pin4, LOW);
  //Serial.println("fullstep4");
 
}
void step_OFF(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
}

void fullstep_forward(){
  fullstep_1();
  delay(delaytime);
  fullstep_2();
  delay(delaytime);
  fullstep_3();
  delay(delaytime);
  fullstep_4();
  delay(delaytime);
}