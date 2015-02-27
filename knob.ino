/* 
  Controlling a servo position using an LDR (Light Dependant Resistor) 
  Reads the analog input on pin 0, from the LDR.
  Uses the value red from the LDR to change the position of the servo, connected to pin 9.
  This example code is a variant from Knob, found in the public domain.
 
  version of March 4th 2015 
  by Airbus Team XX
 */

// We tell Arduino that we will use a library called Servo in this sketch
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int LDR_pin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() 
{ 
  val = analogRead(LDR_pin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180) 
  val = constrain(val, 0, 180);        // limits the values to the interval [0..180]
  myservo.write(val);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
} 
