#include <Process.h>
#include <Bridge.h>

String readString;
Servo monServo;


void setup() {
   Bridge.begin();   // Initialize the Bridge
   monServo.attach(9); 
}

void loop() {
  
   
  Process p;
  //a HTTP GET with curl 
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
  
    Serial.print(readString);
    readString=""; 
   }
   
  delay(1000);  // wait 5 seconds before you do it again
}
