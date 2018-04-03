/*

3.6

Write a function in your sketch with the prototype:
  void run( int steps, int speed)
where steps is the number of steps to turn 
(negative numbers for reverse direction) and speed 
is the speed, expressed in steps per second (i.e. 200 
is one revolution per second).  What is the fastest speed 
the motor will run at reliably?  How does this compare with
what is in the datasheet?

 
NOTE: fastest speed reliably is: 500 steps/second at around 12 V CC
Datasheet says: torque gets halved at ~500 steps/second
http://edf.bu.edu/PY371/DataSheets/StepperMotor.pdf

 */
 
// DECLARE PINS //
const int pin1 = 8;
const int pin2 = 9;
const int pin3 = 10;
const int pin4 = 11;

// INITIALIZE VARIABLES //

//FUNCTIONS

void fullstep_1(){
  digitalWrite(pin1, HIGH); 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, HIGH); 
  digitalWrite(pin4, LOW); 
}
void fullstep_2(){
  digitalWrite(pin1, HIGH); 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, HIGH); 
}
void fullstep_3(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, HIGH); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, HIGH); 
}
void fullstep_4(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, HIGH); 
  digitalWrite(pin3, HIGH); 
  digitalWrite(pin4, LOW); 
}
void step_OFF(){
  digitalWrite(pin1, LOW); //power all coils down
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
}

void fullstep_forward(int delaytime){//one tooth forward
  fullstep_1();
  delay(delaytime);
  fullstep_2();
  delay(delaytime);
  fullstep_3();
  delay(delaytime);
  fullstep_4();
  delay(delaytime);
}

void run( int steps, int stepspersec){ //implement speed
  int delaytime = 1000/stepspersec;
  step_OFF();         
  while(steps>0){
    fullstep_forward(delaytime);      
    steps -- ;
  }
}

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT); 
  pinMode(pin3, OUTPUT); 
  pinMode(pin4, OUTPUT);
}

/*
If delay= 1 ms/step x 200 step, takes 200 ms for 1 rev, 1000 steps / second
If delay= 5 ms/step x 200 step, takes 1000 ms for 1 rev, 200 steps/second
If delay= 10 ms/step, x 200 step, takes 2000 ms for 1 rev, 100 steps/ second
 */
 
void loop(){
  int nsteps = 200; //one full rotation
  int stepspersec = 500;
  run(nsteps,stepspersec);
}
