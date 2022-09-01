//This is code that is meant as practice coding the motor controler and stepper motor

#include <Stepper_Header_Test_1.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
//ublox libraries
#include <UbloxGPS.h>
#include <TinyGPS++.h>

#define PRINT_CALCULATED
#define PRINT_SPEED 200 // ms between prints
#define IMU_GPS_UPDATE_SPEED 100  //100 ms between IMU and GPS updates

#define DECLINATION 0.02 // Declination (degrees) Minneapolis MN
#define serialBAUD 115200
#define ubloxSerial Serial1 //defining which serial port the M8N is connected 
#define earthRadiusKm 6371.0

ROB_STEPPER_MOTOR stepper;
LSM9DS1 imu;
UbloxGPS ublox(&ubloxSerial);


//######################### Defining Variables #############################
static unsigned long lastPrint = 0; // Keep track of print time
int logicControlLastPrint = 5000; //wait a total of 5s before printing
//------------------GPS variables --------------------
bool useGPS = false; //variable that regulates whether the GPS will be used or user specified lat long will be used. true for GPS, false for user
//Lat long and altitude variables the the Ublox GPS gets
double currLatitude = 44.9778;
double currLongitude = -93.265;
double currAltitude = 830;
// LLA of target
double targetLat = 44.0121;
double targetLon = -93.265;
double targetAlt = 1030;
//variables for average heading
double m[3] = {0}; //array that will hold all calibrated mag values
int aveHeadingLength = 25;
double aveHeading[25] = {0};


//Function definitions
void printGyro();
void printAccel();
void printMag();
void updateAttitude(float ax, float ay, float az, float mx, float my, float mz);
double calcReqBearing(double targetLat, double targetLon, double currLat = currLatitude, double currLon = currLongitude, double currHeading = 0);


//variables for gyro (degrees), acc (g), mag (gauss)
float Ex, Ey, Ez; //the E values are the I values that are corrected for pitch
float Ix, Iy, Iz; //the I values are the calibrated magnetometer values in the frame of the IMU
float Ax, Ay, Az; //the A values are the acceleration values in the same frame as the magnetometer
double roll = 0;
double pitch = 0;

void setup() {
  Serial.begin(serialBAUD); //define baud rate in variable decleration above
  Serial.println("Serial online");
  //begin I2C
  Wire.begin();
  //setup for the IMU
  IMUsetup();
  //set up SD
  sdSetup();
  //setup GPS
  ubloxSetup();
}

void loop() {
  //checks if command has been entered every loop
  serialCommandCheck();

  //----------------GPS && heading loop part----------------

  if (millis() % IMU_GPS_UPDATE_SPEED == 0) {
    updateIMUdata(); //update IMU data every loop
    if (useGPS) //if useGPS is true then updateUbloxGPS otherwise dont
      updateUblox();
    delay(1);
  }

  if ((lastPrint + PRINT_SPEED) < millis())
  {
    Serial.println("Seconds: " + String(millis()));


    displayUbloxCoordinates();
    displayTargetCoordinates();
    printAttitude();
    //call calc req bearing to see the current bearings
    calcReqBearing(targetLat, targetLon, currLatitude, currLongitude, printAveHeading());
    //call the heading control, checks if it should try to update the current heading
    headingCorrection();

    //Serial.println("Distance to target: " + String(distanceEarth(targetLat, targetLon, currLatitude, currLongitude), 3));



    //   logData(); //this is the line that will save data to the SD if able to communicate with it
    Serial.println();
    delay(10);
    lastPrint = millis(); // Update lastPrint time

  }
  //------------------------------------------

}
