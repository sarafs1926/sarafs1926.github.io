/*
Lab 2.6

Convert the main part of your sketch into a function
(Read about Arduino functions if you need review).
Use this function declaration as a prototype:
void setDac( word v)
The function argument v is declared as a word because 
it is specified to hold a 16-bit value, rather than an int 
whose size is not specified.

Test your function by writing a sketch which outputs various 
values to the DAC in succession, and viewing the output on the oscilloscope.

How long does it take to output a new value?  (Hint:  measure this by 
programming alternating large and small values and measuring on the oscilloscope).
*/

/*
NOTE: at 57600 baud, arduino takes ~10us to ramp up and ramp down.
 */


// DECLARE PINS //
const int dac_nCSPin = 10;     
const int dac_SCKPin = 13;       
const int dac_SDIPin = 11;

// INITIALIZE VARIABLES //
int config_bit = 0x7;
int n = 0x0;
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
  if (count & 1 ){
    n = 4095;
  }
  else{
    n = 0;
  }
  //Serial.println(config_bit);
  int num = config_bit << 12;
  int num1 = num + n;
  //Serial.println(num1);
  
  setDac(num1);

  count = count + 1;
}

void setDac(word v){
  // set nCS to 0 (LOW)
  digitalWrite( dac_nCSPin, 0);  
  
  //debug to serial monitor
  //write to serial and deal with SCK
  for (int i = 16; i --> 0;) {    
    int val = (v & (1 << i )) >> i;
    digitalWrite(dac_SDIPin,val); // seq(i) = 0 ==> LOW & seq(i) = 1 ==> HIGH
    //Serial.print(val);
    digitalWrite( dac_SCKPin, 1);  // set SCK high
    digitalWrite( dac_SCKPin, 0);  // set SCK low
  }
  //Serial.println();
  
  // set nCS to 1 (HIGH)
  digitalWrite( dac_nCSPin, 1); 
}
