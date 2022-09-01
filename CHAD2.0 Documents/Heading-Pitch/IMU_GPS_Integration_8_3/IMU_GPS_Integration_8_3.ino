//IMU testing for chad document

// The SFE_LSM9DS1 library requires both Wire and SPI be
// included BEFORE including the 9DS1 library.
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
//ublox libraries
#include <UbloxGPS.h>
#include <TinyGPS++.h>

#define PRINT_CALCULATED
#define PRINT_SPEED 100 // 100 ms between prints
#define DECLINATION 0.02 // Declination (degrees) Minneapolis MN
#define serialBAUD 115200
#define ubloxSerial Serial1 //defining which serial port the M8N is connected 
#define earthRadiusKm 6371.0

LSM9DS1 imu;
UbloxGPS ublox(&ubloxSerial);

//######################### Defining Variables #############################
static unsigned long lastPrint = 0; // Keep track of print time
       //------------------GPS variables --------------------
bool useGPS = false; //variable that regulates whether the GPS will be used or user specified lat long will be used. true for GPS, false for user
//Lat long and altitude variables the the Ublox GPS gets
double currLatitude = 44.9778;
double currLongitude = -93.265;
double currAltitude = 830;
// LLA of target
double targetLat = 44.0121;
double targetLon = -92.4802;
double targetAlt = 1030;
//variables for average heading
double m[3] = {0}; //array that will hold all calibrated mag values
int aveHeadingLength = 50;
double aveHeading[50] = {0};


//Function definitions
void printGyro();
void printAccel();
void printMag();
void printAttitude(float ax, float ay, float az, float mx, float my, float mz);
double calcBearingAngle(double targetLat, double targetLon, double currLat = currLatitude, double currLon = currLongitude, double currHeading = 0);


//variables for gyro (degrees), acc (g), mag (gauss)
float Ex, Ey, Ez; //the E values are the I values that are corrected for pitch
float Ix, Iy, Iz; //the I values are the calibrated magnetometer values in the frame of the IMU
float Ax, Ay, Az; //the A values are the acceleration values in the same frame as the magnetometer

void setup()
{
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

void loop()
{
  serialCommandCheck(); //constantly check for Serial commands

  
  if (millis() % 250 == 0) {
    updateIMUdata(); //update IMU data every loop
    if (useGPS) //if useGPS is true then updateUbloxGPS otherwise dont
      updateUblox();
    delay(10);
  }

  if ((lastPrint + PRINT_SPEED) < millis())
  {
    Serial.println("Seconds: " + String(millis()));

    printAttitude(Ax, Ay, Az, Ix, Iy, Iz); //this funciton will calculate the attitude based on the Ixyz values and it will find the E values, then print the heading calculations
    displayUbloxCoordinates();
    displayTargetCoordinates();
    
    //target lat long, then current lat long
    Serial.println("Passing this for ave heading: " + String(printAveHeading()) );
    calcBearingAngle(targetLat, targetLon, currLatitude, currLongitude, printAveHeading()); //assuming the currHeading is the average heading (ave across 5 sec)
    Serial.println("Distance to target: " + String(distanceEarth(targetLat, targetLon, currLatitude, currLongitude), 3));
    Serial.println();
 //   logData(); //this is the line that will save data to the SD if able to communicate with it
    delay(10);
    lastPrint = millis(); // Update lastPrint time
  }
}//end of 'loop()'
