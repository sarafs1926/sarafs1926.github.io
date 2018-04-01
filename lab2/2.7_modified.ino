/*
Lab 2.7
Make a new version of 2.5 using the Arduino SPI library (reading link).
This requires several changes to your code.  First you must add:
  #include <SPI.h>
at the top of the sketch to include the function declarations for the library.
Next, you must add:
SPI.begin();
SPI.setBitOrder( MSBFIRST);
to your setup() function.  The first line initializes the library.  
The second tells the library to output the MSB (most-significant bit) 
first as shown in the timing diagram from the datasheet. 
Finally, you have to call the function:
  SPI.transfer( data);
for each byte (8 bits) to be sent.  Note that the DAC requires two bytes 
(16 bits) to be sent so you have to call the function twice for each update 
of the DAC.  Also note that the library does not take care of the nCS signal, 
so you need to handle that in your own code.

If you have trouble getting the code using the library to work, don’t forget 
that you need to take care of the BUF, GA* and SHDN* bits.  Ask for help if you need it.

Finally, make a function called setDac() which works like the one you wrote before.
Output a ramp from 0-5V as you did in Lab 2.5.
Compare the speed.  Is it faster?
 */

 /* NOTE: the rate is around 20 Hz for this design, over 10* faster than 2.5 */
 
#include <SPI.h>

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
  //pinMode( dac_SCKPin, OUTPUT);  // define nCS as an output
  //pinMode( dac_SDIPin, OUTPUT);  // define nCS as an output
  digitalWrite( dac_nCSPin, 1);  // set nCS to 1 (HIGH)
  digitalWrite( dac_SCKPin, 0);  // set SCK to 0 (LOW)
  
  //initialize SPI library
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);

}
 
void loop() {
  
  //Serial.println(config_bit);
  int num = config_bit << 12;
  int num1 = num + count;
  //Serial.println(num1);
  
  setDac(num1);

  count = count + 1;
  
  //wraparound
  if (count > 4095){
    count = 0;
  }
  
}

void setDac(word v){
  // set nCS to 0 (LOW)

  byte high_byte = highByte(v);
  byte low_byte = lowByte(v);
  //use SPI library to send
  digitalWrite( dac_nCSPin, 0);
  SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(high_byte);

  SPI.transfer(low_byte);
  SPI.endTransaction();
  digitalWrite( dac_nCSPin, 1);

  }
