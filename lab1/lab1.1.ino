/*
Lab 1.1
Write a sketch which reads a switch and displays its value on an LED.
You will need to enable the “pull-up” function as described in the reading.
Trouble?  Make sure you use pinMode to set the LED pins as outputs.  
Use digitalRead() on each switch and digitalWrite() on each LED.
Does a switch “on” result in a logic ‘1’ or logic ‘0’.  Why?
*/

void setup() {
  //start serial connection
  Serial.begin(9600);
  // the switch is an input pullup
  pinMode(13, INPUT_PULLUP);
  // The LED pin is output
  pinMode(2, OUTPUT);

}

void loop() {
  //read the switch value into a variable
  int sensorVal = digitalRead(13);
  //print the switch value to the serial monitor
  Serial.println(sensorVal);

  // The pull-up means the switch's logic is inverted. It goes
  // HIGH when it's low (off), and LOW when it's on (high). 
  // See diagram 1 here: https://playground.arduino.cc/CommonTopics/PullUpDownResistor
  
  //When the sensorVal is high, the switch is off, so write LOW to the LED.
  if (sensorVal == HIGH) {
    digitalWrite(2, LOW);
  } 
  //When the sensorVal is low, the switch is on, so write HIGH to the LED.
  else {
    digitalWrite(2, HIGH);
  }
}
