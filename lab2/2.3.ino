/*
Lab 2.3
Measure the maximum frequency you can output with your filtered PWM DAC
With the oscilloscope connected to the output of your filter, enter and run the following sketch:

This sketch will output a square wave (in principle) with a frequency of 1/2d 
where d is the delay for one half-cycle in ms.

If you set the delay very large, you should see a 5V square wave.  
Experiment to find the delay at which the amplitude drops by 3dB (1/sqrt(2)).
How does this compare with the cutoff frequency of your filter?

Would this circuit be good for generating sound?  Why or why not?
*/

int d = 120;                    // half-cycle delay in ms
void setup() { }
void loop() {
  analogWrite( 3, 0);      // set PWM to minimum
  delay( d);
  analogWrite( 3, 255);    // set PWM to maximum
  delay( d);
}

