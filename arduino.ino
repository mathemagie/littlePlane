#include <Process.h>
#include <Bridge.h>
#include <Servo.h>

const int ledPin = 13; 

String readString;

Servo monServo;
int is_on_water;
int flight_status;

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
  p.runShellCommand("/usr/bin/curl http://mathemagie.net/littleplane/get_flight_status.php?team_id=1");
  Serial.println("run curl");

  // do nothing until the process finishes, so you get the whole output:
  while(p.running());  

  // Read command output. runShellCommand() should have passed "Signal: xx&":
  while (p.available()) {
    char c  =  p.read();
    readString += c;
  }
  
  if (readString.length() >0) {
  
    //Serial.print(readString);
    flight_status = readString.substring(0,1).toInt();
    is_on_water = readString.substring(2,3).toInt();
    if (is_on_water) {
      Serial.println("flight on water");
      digitalWrite(ledPin, HIGH);
       monServo.write(90);
      delay(1000);      
    }else {
       digitalWrite(ledPin, LOW);
        monServo.write(180);
       delay(1000);      
    }
    if (flight_status == 2) {
      Serial.println("flight airborne");
        monServo.write(90);
      delay(1000);      
    }
    
    if (flight_status == 1) {
      Serial.println("flight landed");
        monServo.write(90);
      delay(1000);      
    }else {
        monServo.write(180);
       delay(1000);      
    }
   readString=""; 
   }
   
  delay(1000);  // wait 5 seconds before you do it again
}
