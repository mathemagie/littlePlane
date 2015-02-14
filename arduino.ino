#include <Process.h>
#include <Bridge.h>
#include <Servo.h>

const int ledPin = 13; 

Servo monServo;

void setup() {
  Bridge.begin();   // Initialize the Bridge
   pinMode(ledPin, OUTPUT);
   monServo.attach(9); 
}

void loop() {
  
   
  Process p;
  // This command line runs the WifiStatus script, (/usr/bin/pretty-wifi-info.lua), then 
  // sends the result to the grep command to look for a line containing the word
  // "Signal:"  the result is passed to this sketch:
  p.runShellCommand("/usr/bin/curl http://mathemagie.net/projects/flight/index.php");
  Serial.println("run curl");

  // do nothing until the process finishes, so you get the whole output:
  while(p.running());  

  // Read command output. runShellCommand() should have passed "Signal: xx&":
  while (p.available()) {
    int result = p.parseInt();  
    Serial.println(result);
    if (result) {
      digitalWrite(ledPin, HIGH);
       monServo.write(90);
      delay(1000);      
    }else {
       digitalWrite(ledPin, LOW);
        monServo.write(180);
       delay(1000);      
    }
 

    // look for an integer
   
  
  } 
  delay(1000);  // wait 5 seconds before you do it again
}
