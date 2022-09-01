//code to try and get the REQUIRED heading angle between two GPS points

//libraries for Ublox GPS
#include <UbloxGPS.h>
#include <TinyGPS.h>
#include <Wire.h>

#define serialBAUD 9600  
#define ubloxSerial Serial1 //defining which serial port the M8N is connected to 

//initializing GPS object
UbloxGPS ublox(&ubloxSerial);

//declaring the helper funcitons
void ubloxSetup();
void updateUblox();
void displayUbloxCoordinates();

//Lat long and altitude variables the the Ublox GPS gets
double ubloxLatitude = 0;
double ubloxLongitude = 0;
double ubloxAltitude = 0;

void setup() {
  // put your setup code here, to run once:

  //set up serial monitor:
  Serial.begin(serialBAUD); //define baud rate in variable decleration above
  Serial.println("Serial online");
  
  //set up the GPS
  ubloxSetup();
  
}

void loop() {
// need to constantly check for serial bytes/commands (as opposed to only every 1/4 s)
//  serialCommandCheck();
    
  //Every 1/4 second update the current GPS coordinates
  if( (millis() % 250) == 0){
    updateUblox();
  }

  if( (millis() % 1000) == 0){ //display values every 1 second
    displayUbloxCoordinates();
    delay(100);
  }
  
  
  
  
}
