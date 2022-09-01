//IMU testing for chad document

// The SFE_LSM9DS1 library requires both Wire and SPI be
// included BEFORE including the 9DS1 library.
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>


LSM9DS1 imu;


#define PRINT_CALCULATED
//#define PRINT_RAW
#define PRINT_SPEED 100 // 100 ms between prints

static unsigned long lastPrint = 0; // Keep track of print time

// Earth's magnetic field varies by location. Add or subtract
// a declination to get a more accurate heading. Calculate
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION 0.02 // Declination (degrees) Minneapolis MN

//Function definitions
void printGyro();
void printAccel();
void printMag();
void printAttitude(float ax, float ay, float az, float mx, float my, float mz);

double m[3] = {0}; //array that will hold all calibrated mag values
int aveHeadingLength = 50;
double aveHeading[50] = {0};

//variables for gyro (degrees), acc (g), mag (gauss)
float Ex, Ey, Ez; //the E values are the I values that are corrected for pitch
float Ix, Iy, Iz; //the I values are the calibrated magnetometer values in the frame of the IMU
float Ax, Ay, Az; //the A values are the acceleration values in the same frame as the magnetometer

void setup()
{
  Serial.begin(115200);
  //begin I2C
  Wire.begin();
  //setup for the IMU
  IMUsetup();
  //set up SD
  sdSetup();
}

void loop()
{
  updateIMUdata(); //update IMU data every loop

  if ((lastPrint + PRINT_SPEED) < millis())
  {
   // printGyro();  // Print "G: gx, gy, gz"
   // printAccel(); // Print "A: ax, ay, az"
    printMag();   // Print "M: mx, my, mz"
    
    logData(); //this is the line that will save data to the SD if able to communicate with it

    printAttitude(Ax, Ay, Az, Ix, Iy, Iz); //this funciton will calculate the attitude based on the Ixyz values and it will find the E values, then print the heading calculations
    

    lastPrint = millis(); // Update lastPrint time
  }
}//end of 'loop()'
