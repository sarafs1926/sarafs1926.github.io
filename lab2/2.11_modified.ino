/*
Lab 2.11

Modify 2.10 to use the freq/ampl parameters to modify the output of your sketch.

*/

#include <SPI.h>
#include <TimerOne.h>

// DECLARE PINS //
const int dac_nCSPin = 10;     
const int dac_SCKPin = 13;       
const int dac_SDIPin = 11;

// INITIALIZE VARIABLES //
int config_bit = 0x7;
float freq = 100.0;        // output frequency in Hz
float amplitude = 5.0;     // output amplitude pk-pk in V

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

  
  //initialize TimerOne library
  Timer1.initialize(250); // timer interrupts every millisecond
  Timer1.attachInterrupt( timerFunc);  // call every interrupt

}
 
volatile int n = 0;
volatile int count = 0;
void timerFunc()
{
  const float pi2 = 3.1415927 * 2.0;
  static float a;      // sin angle in radians
  static float da = pi2/8;  // delta-a (increment value)
  unsigned int d;      // DAC value 0-4095 (12 bits)
  d = (amplitude/5.0)*(2048.0 + 2047.0 * sin((freq/500)*a));
  
  int num = config_bit << 12;
  int num1 = num + d;
  setDac(num1);
  a += da;
}

void loop(){
  
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
