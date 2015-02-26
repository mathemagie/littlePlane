/*
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the signal electrode of an LDR sensor circuit to pin A0.

  This example code is a variant from AnalogReadSerial, found in the public domain.
 
  version of March 4th 2015 
  by Airbus Team XX
 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // both the arduino and the computer's serial port are connected through the usb cable 
  // they need to both read at the same speed so that the info they will get (essentially 
  // 0's and 1's) is the rigth one and there are no parasite values that appear
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
}
