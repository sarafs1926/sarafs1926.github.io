/*
Lab 3.7

Modify the sketch to accelerate the motor gradually 
(over, say, 25 steps) instead of starting at full speed. 
Can you run reliably at higher speed now?

NOTE: yes, slightly higher. Maybe at 520 steps/second.
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
  for (int i=100; i<520; i+=30){
  int nsteps = 30; //one full rotation
  int stepspersec = i;
  run(nsteps,stepspersec);
  }
}