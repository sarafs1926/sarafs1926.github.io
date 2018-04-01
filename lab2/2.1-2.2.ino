/*
 Lab 2.1
Build a pulse width modulation DAC
Wire an LED between Arduino pin 3 and GND.
Write a sketch which calls analogWrite() to pin 3 with various values from 0 to 255. 
What happens to the brightness of the LED?  Connect an oscilloscope to pin 3.  
You should see a train of pulses.  What is the frequency?

Make a table in your notebook with 3 columns as follows:

PWM Value: 0/64/128/192/255
Pulse Width
Voltage

Set the PWM to each of the values suggested and measure the pulse width.
Often it is useful to get a programmable DC voltage from a PWM signal.
You can use a low-pass filter to convert the pulse train to a DC value.

Lab 2.2
Design a low-pass RC filter with a cutoff frequency which you think is appropriate
to get a DC value from the pulse train.  Test it.  If you still see pulses, the 
frequency is too high.  Experiment with different R, C until the output is smooth 
(less than maybe 100mV of ripple)  What component values did you end up with?  
What is the cutoff frequency?

Fill in the third column of the table from 2.1 with your filter connected (use a volt meter).

The filter you have designed is a common feature of systems which generate waveforms
from digital data (like mp3 players).

Limitations of PWM -- PWM works well for applications where speed is not important (such as 
dimming LEDs or controlling motor speed).  It is not so good for generating waveforms.

*/

// DECLARE PINS //

const int PWMOutPin=3;

// INITIALIZE VARIABLES //
byte pwmValue = 128;

void setup() {

}

void loop() {
  analogWrite(PWMOutPin,pwmValue);
  //pwmValue++;
  delay(20);
}
