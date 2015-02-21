#include <Process.h>
#include <Bridge.h>
#include <Servo.h>

const int ledPinSea = 13; 
const int ledPinGround = 12; 

String readString;

Servo monServo;
int is_on_water;
int flight_status;

void setup() {
   Bridge.begin();   // Initialize the Bridge
   pinMode(ledPinSea, OUTPUT);
   pinMode(ledPinGround, OUTPUT);
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
  
    //Serial.print(readString);
    flight_status = readString.substring(0,1).toInt();
    is_on_water = readString.substring(2,3).toInt();
    
    if (is_on_water) {
      Serial.println("flight on water");
      digitalWrite(ledPinSea, HIGH);
       digitalWrite(ledPinGround, LOW);
      delay(1000);      
    }
    else {
       Serial.println("flight on land");
      digitalWrite(ledPinGround, HIGH);
      digitalWrite(ledPinSea, LOW);
      delay(1000);      
    }
    
    if (flight_status == 2) {
      Serial.println("flight airborne");
      monServo.write(10);//en haut
      delay(1000);      
    }
    
    if (flight_status == 1) {
      Serial.println("flight landed");
      monServo.write(180);//en bas
      delay(1000);      
    }
   readString=""; 
   }
   
  delay(1000);  // wait 5 seconds before you do it again
}
