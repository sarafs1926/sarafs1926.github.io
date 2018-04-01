
/*
Lab 2.9

Make a sketch which uses the timer interrupt to output 
a square wave at exactly 500Hz using the suggestions above
 */
 
#include <SPI.h>
#include <TimerOne.h>

// DECLARE PINS //
const int dac_nCSPin = 10;     
const int dac_SCKPin = 13;       
const int dac_SDIPin = 11;

// INITIALIZE VARIABLES //
int config_bit = 0x7;

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
  Timer1.initialize(1000); // timer interrupts every millisecond
  Timer1.attachInterrupt( timerFunc);  // call every interrupt

}
 
volatile int n = 0;
volatile int count = 0;
void timerFunc()
{
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
