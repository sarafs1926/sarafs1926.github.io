/*
Lab 2.5
Write and debug a sketch to output a ramp from 0-5V on the DAC.

Use your oscilloscope as needed to debug it if it doesn’t work.
You’ll need both channels.  Use one to trigger on the falling edge
of nCS and look at the other signals to be sure they look like the 
timing diagram.

 */

// DECLARE PINS //
const int dac_nCSPin = 10;     
const int dac_SCKPin = 13;       
const int dac_SDIPin = 11;

// INITIALIZE VARIABLES //
int count = 0;

void setup() {   
  
  //start serial connection
  Serial.begin(57600);     
  pinMode( dac_nCSPin, OUTPUT);  // define nCS as an output
  pinMode( dac_SCKPin, OUTPUT);  // define nCS as an output
  pinMode( dac_SDIPin, OUTPUT);  // define nCS as an output
  digitalWrite( dac_nCSPin, 1);  // set nCS to 1 (HIGH)
  digitalWrite( dac_SCKPin, 0);  // set SCK to 0 (LOW)

}
 
void loop() {
  Serial.println(count);

  //update our binary sequence
  int seq[16] = {0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}; 
  for (int b = 0; b < 12; b++ ){
    if (count & (1<<b)){ //rewrite binary digits 1-12
      seq[15-b] = 1;
    }
    else{
      seq[15-b] = 0;
    }
  }

  // set nCS to 0 (LOW)
  digitalWrite( dac_nCSPin, 0);  
  
  //debug to serial monitor
  //write to serial and deal with SCK
  for (int i=0;i < 16;i++) {    
    digitalWrite(dac_SDIPin,seq[i]); // seq(i) = 0 ==> LOW & seq(i) = 1 ==> HIGH
    Serial.print(seq[i]);
    digitalWrite( dac_SCKPin, 1);  // set SCK high
    digitalWrite( dac_SCKPin, 0);  // set SCK low
  }
  Serial.println();
  // set nCS to 1 (HIGH)
  digitalWrite( dac_nCSPin, 1); 

  //increment count
  count = count + 1;

  //wraparound
  if (count > 4095){
    count = 0;
  }
}

