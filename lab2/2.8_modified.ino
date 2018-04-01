/*
Lab 2.8

Load your 2.7 sketch.
Modify your main loop to output a square wave.

Trigger the oscilloscope on rising edge and look at the output.  
You should see a square wave with a frequency of about 30kHz.  
Adjust the oscilloscope so that 10-20 cycles fit on the screen. 
Notice how the wave “jumps” sometimes and the period seems to change?  
This is because periodically the AVR microcontroller is interrupted and
goes off to do something else, causing a delay in your sketch.  
This is troublesome if you want to create periodic waveforms.
There is a way around this...
 */

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
