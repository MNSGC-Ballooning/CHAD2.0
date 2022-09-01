//code to try and get the REQUIRED heading angle between two GPS points

//libraries for Ublox GPS
#include <UbloxGPS.h>
#include <TinyGPS++.h>
#include <Wire.h>

#define serialBAUD 9600
#define ubloxSerial Serial1 //defining which serial port the M8N is connected 

#define earthRadiusKm 6371.0

//initializing GPS object
UbloxGPS ublox(&ubloxSerial);

//declaring the helper funcitons
/*
  void ubloxSetup();
  void updateUblox();
  void displayUbloxCoordinates();

*/


//Lat long and altitude variables the the Ublox GPS gets
double ubloxLatitude = 44.9778;
double ubloxLongitude = -93.265;
double ubloxAltitude = 830;

double targetLat = 44.0121;
double targetLon = -92.4802;
double targetAlt = 1030;

bool useGPS = false; //variable that regulates whether the GPS will be used or user specified lat long will be used. true for GPS, false for user

//declaration of functions
double calcBearingAngle(double targetLat, double targetLon, double currLat = ubloxLatitude, double currLon = ubloxLongitude, double currHeading = 0);



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
  serialCommandCheck();

  //Every 1/4 second update the current GPS coordinates
  if ( (millis() % 250) == 0) {
    if (useGPS) {
      updateUblox();
    } //if useGPS is true then updateUbloxGPS otherwise dont
  }

  //every 1 second show the target and ublox coordinates
  if ( (millis() % 1000) == 0) {
    Serial.println(String(millis() / 1000));
    displayUbloxCoordinates();
    displayTargetCoordinates();
    //target lat long, then current lat long
    calcBearingAngle(targetLat, targetLon, ubloxLatitude, ubloxLongitude); //assuming the currHeading is north rn
    Serial.println("Distance to target: " + String(distanceEarth(targetLat, targetLon, ubloxLatitude, ubloxLongitude), 3));
    Serial.println();
    delay(100);
  }

}//end of loop
