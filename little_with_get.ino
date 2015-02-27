/* 
  Little airplane
  This sketch uses the real-time information of an airplane, provided by the API FlightRadar.
  The API information is obtained and processed into a string from a distant server
  at http://mathemagie.net/littleplane
  The string provided by the server contains the flight status of the plane 
  This sketch translates de plane's status into movement of a servo motor that makes an airplane go up or down
  And also lights up an LED to indicate wether the ariplane flies over the sea or the ground
 
  version of March 4th 2015 
  modified by Airbus Team XX
 */

// Arduino provides libraries that allow him to reuse the code for advanced functions. 
// The libraries need to be declared at the begining of the sketch.

#include <Bridge.h>       // A library to connects the arduino and the linux processor
#include <Servo.h>        // A library to allows the operation of a servo motor
#include <HttpClient.h>   // A library to create a basic HTTP client that connects to the internet


// We then declare and initialise the variables that we will use in our sketch
// Variables are used to give a meaningful name to the constant values they contain
// they also avoid mistakes if we decide to change the value they contain

const int ledPinSea = 13;     // The positive leg of the Sea LED is connected to pin 13 
const int ledPinGround = 12;  // The positive leg of the Ground LED is connected to pin 12

int servoPin = 9;             // The signal cable of the servo motor will be connected to Pin 9

const int plane_flying = 2;   // Variable containing the reference value of a plane that is flying 
const int plane_landed = 1;   // Variable containint the reference value of a plane is on the ground

String readString;   // A variable that will contain the chain of characters (string) obtained 
                     // from of the HTTP request of API info

int is_on_water;     // A variable that will contain the API info downloaded from the server, 
                     // tells if the plane is flying over water (1) or ground (0)
int flight_status;   // A variable that will contain the API info downloaded from the server,
                     // tells if the plane is flying (2) or landed (1)

Servo monServo;      // An object that represents the servo we will connect to the Digital pin 9


//routine executed just once after first connexion or reseting the board

void setup() {
   pinMode(ledPinSea, OUTPUT);       // Pin 13 is set as an output
   pinMode(ledPinGround, OUTPUT);    // Pin 12 is set as an output
   pinMode (servoPin, OUTPUT);       // Pin 9 is set as an output
  
   // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
   digitalWrite(ledPinSea, LOW);    
   Bridge.begin();
   digitalWrite(ledPinSea, HIGH);    // Initialize the Bridge 
 
   monServo.attach(servoPin);        // A servo is connected to Pin 9
   Serial.begin(9600);               // Sets the data rate communication in bits per seconds for communicating
                                     // with the computer

  while (!Serial); // The program will be blocked here waiting until the serial connection is opened
                 
}

// This routine is executed continuously, over and over
void loop() {
  
  // This part of the code connects to the server online and obtains the processed information from the API
  
  // An http get is the equivalent of the action that you computer will execute once you enter a url 
  // on your navigator
  
  // Here the url in question is "http://mathemagie.net/littleplane/get_flight_status.php?team_id=1" 
  // Note that in the URL you have team_id=1 and you must substitute it with your team's ID Number
 
  // If you go to a navigator with "http://mathemagie.net/littleplane/get_flight_status.php?team_id=1"
  // you will see the string that is sent from the server, in this form A | B, where 
  // A is a cypher indicating one of the plane status (1 or 2) for landed or flying
  // B is a cypher indicationg is the sea status (0 or 1) for ground or sea
  
  HttpClient client;
  client.get("http://mathemagie.net/littleplane/get_flight_status.php?team_id=1");
  
  // Here println is used as a trick to inform you that the get has been requested
  // the words run httpget will be printed on your serial monitor
  // remember you can visualize the serial monitor by clicking ont he top right icon of the IDE
  Serial.println("run httpget");
  
  

  // while the information is being received by the HTTP client
  while (client.available()) {
    char c = client.read();      // read the next character of the info
    readString += c;             // and add it to the string of characters called "c"
  }
  Serial.println(readString);    // As a trick to find possible errors, 
                                 // prints the string on the serial monitor so I can see what is being read
     
  // if there is something left to be read on the string containint the plane info
  if (readString.length() >0) {
  
    flight_status = readString.substring(0,1).toInt();    // extract the first character in the string and 
                                                          // store it in the variable flight_status
    is_on_water = readString.substring(2,3).toInt();      // extract the third character in the string and 
                                                          // store it in the variable is_on_water  
    
    // if the plane is flying over the water
    if (is_on_water) {
      Serial.println("flight on water");     // Write a message on the serial monitor so I can check all is OK
      digitalWrite(ledPinSea, HIGH);         // Turn on the Sea LED
      digitalWrite(ledPinGround, LOW);       // Turn off the Ground LED
      delay(1000);                           // Wait for a second
    }
    // otherwise it means it's over ground
    else {
      Serial.println("flight on land");     // Write a message on the serial monitor so I can check all is OK
      digitalWrite(ledPinGround, HIGH);     // Turn off the Sea LED
      digitalWrite(ledPinSea, LOW);         // Wait for a second
      delay(1000);      
    }
    // if the plane is flying
    if (flight_status == plane_flying) {
      Serial.println("flight airborne");   // Write a message on the serial monitor so I can check all is OK
      monServo.write(10);                  // Turn the motor to bring the plane up. 
                                           //We make it turn to 10 instead of 180 to avoid motor noise.
      delay(1000);      
    }
     // otherwise if the plane is on the ground
    if (flight_status == plane_landed) {  
      Serial.println("flight landed");    // Write a message on the serial monitor so I can check all is going OK
      monServo.write(170);                // Turn the motor to bring the plane down.
                                          // We make it turn to 170 instead of 180 to avoid motor noise.
      delay(1000);      
    }
   readString="";   // empty the string with the API info
   }
    delay(1000);  // wait for 5 seconds before you verify the plane info again
}
