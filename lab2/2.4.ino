/*
Lab 2.4: Use a serial DAC (Microchip MCP4921)

This is an 8-pin chip which should be in the kit of accessory parts.  
The MCP4921 is a 12-bit serial converter with an SPI bus interface.  
It accepts a 12-bit binary number (decimal values 0-4095) and converts it to a 
voltage from 0-5V (with normal gain settings).  

To communicate with the DAC you must use a specific protocol called SPI.  
To quote page 23 of the data sheet:  

“The write command is initiated by driving the CS* pin low, followed by clocking
the four Configuration bits and the 12 data bits into the SDI pin on the rising edge 
of SCK.  The CS* pin is then raised, causing the data to be latched into the DAC’s
input register.”

  SDI - pin 4   Arduino pin 11
  SCK - pin 3   Arduino pin 13
  CS* - pin 2   Arduino pin 10
  
  VDD - pin 1   +5V
  VSS - pin 7   0V (GND)

  LDAC* - pin 5   GND
  VREF - pin 6    +5V

  Vout - pin 8 --> Voltmeter

 ----

 In step 3 we provide 16 different bit values.
 The first 4 bits are configuration bits: 
 
 bit 15 = 0
 bit 14 = 1  (this is unimportant)
 bit 13 = 1  (set output scale to 0-5V)
 bit 12 = 1  (enable the output)

At first, output the fixed binary value 1000 0000 0000 to the DAC.
This should result in a voltage of 2.5V on the output (pin 8).

To load a value into the DAC: 
1. Initialize (in setup()) by setting nCS to HIGH and SCK to LOW.
We don’t have to worry about LDAC as we have tied it to GND
2. Set nCS to LOW
3. For bits 0 to 15 (loop):
  a. Output data (0 or 1) on SDI
  b. Set SCK to HIGH
  c. Set SCK to LOW
4. Set nCS to HIGH

 */

// DECLARE PINS //
const int dac_nCSPin = 10;     
const int dac_SCKPin = 13;       
const int dac_SDIPin = 11;

void setup() {   
  
  //start serial connection
  Serial.begin(9600);     
  pinMode( dac_nCSPin, OUTPUT);  // define nCS as an output
  pinMode( dac_SCKPin, OUTPUT);  // define SCK as an output
  pinMode( dac_SDIPin, OUTPUT);  // define SDI as an output
  digitalWrite( dac_nCSPin, 1);  // set nCS to 1 (HIGH)
  digitalWrite( dac_SCKPin, 0);  // set SCK to 0 (LOW)

}
 
void loop() {
  digitalWrite( dac_nCSPin, 0);  // set nCS to 0 (LOW)
  int seq[] = {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0};
  int lenseq = (int)( sizeof(seq) / sizeof(seq[0]) );
  Serial.println(lenseq);
  for (int i = 0; i < lenseq; i++){
    Serial.print(seq[i]);
    digitalWrite(dac_SDIPin,seq[i]); // seq(i) = 0 ==> LOW & seq(i) = 1 ==> HIGH
    digitalWrite( dac_SCKPin, 1);  // set SCK high
    digitalWrite( dac_SCKPin, 0);  // set SCK low
  }
  Serial.println();
  Serial.println("Now printing in reverse order");
  for (int i = lenseq; i --> 0; )
  { 
    Serial.print(seq[i]);
  }
  digitalWrite( dac_nCSPin, 1);  // set nCS to 1 (HIGH)
  Serial.println();
  delay(50000);
}


