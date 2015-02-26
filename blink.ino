/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
  This example code has been copied from the public domain.

  version of March 4th 2015 
  by Airbus Team XX

 */

// First of all we declare any variables used by the sketch
// We create a variable called "Led" that contains a number
// This number is the one of the pin to which we will connect our LED:
int led = 13;

// the setup routine runs once when you press reset or upload a new sketch:
void setup() {
  // we tell arduino to initialize the digital pin number 13 as an output.
  // note that OUTPUT is in blue, this is called a "constant" it has a value
  // that is pre-defined in arduino so the IDE recognises it
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over when the arduino is powered:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
