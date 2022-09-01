
//Sets up the I2C for the IMU
void IMUsetup() {
  if (imu.begin() == false) // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    while (1);
  }
}

void updateIMUdata() {
  // Update the sensor values whenever new data is available
  if ( imu.gyroAvailable() )
    imu.readGyro();

  if ( imu.accelAvailable() )
  {
    imu.readAccel();
    //map the raw acceleration valuesonto proper units
    Ax = -1.0 * imu.calcAccel(imu.ax); //switch the x vaiable so the accelerometer is in the same frame as the magnetometer
    Ay = imu.calcAccel(imu.ay);
    Az = imu.calcAccel(imu.az);
  }
  if ( imu.magAvailable() )
  {
    imu.readMag();
    magCal();// this function calibrates the raw magnetometer values.
    //map magnetometer data onto proper units and save
    Ix = imu.calcMag(m[0]);
    Iy = imu.calcMag(m[1]);
    Iz = imu.calcMag(m[2]);
  }
}

//////////////////////////////////////////////Below are the Print functions for IMU (not required)/////////////////////////////////////////

void printAccel()
{
  // Now we can use the ax, ay, and az variables as we please.
  // Either print them as raw ADC values, or calculated in g's.
  Serial.print("A: ");
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcAccel helper function to convert a raw ADC value to
  // g's. Give the function the value that you want to convert.
  Serial.print(imu.calcAccel((-1 * imu.ax)), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.az), 2);
  Serial.println(" g");
#elif defined PRINT_RAW
  Serial.print(imu.ax);
  Serial.print(", ");
  Serial.print(imu.ay);
  Serial.print(", ");
  Serial.println(imu.az);
#endif

}

void printMag()
{
  Serial.print("Raw M (Voltage): ");
  Serial.print(imu.mx);
  Serial.print(", ");
  Serial.print(imu.my);
  Serial.print(", ");
  Serial.println(imu.mz);

  Serial.print(" M (After calcMag): ");
  Serial.print(imu.calcMag(imu.mx), 4);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 4);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 4);
  Serial.println(" gauss");

  Serial.print("Calibrated mapped M (Ixyz): ");
  Serial.print(imu.calcMag(m[0]));
  Serial.print(", ");
  Serial.print(imu.calcMag(m[1]));
  Serial.print(", ");
  Serial.println(imu.calcMag(m[2]));


}



void printGyro()
{
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.
  Serial.print("G: ");
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcGyro helper function to convert a raw ADC value to
  // DPS. Give the function the value that you want to convert.
  Serial.print(imu.calcGyro(imu.gx), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gy), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gz), 2);
  Serial.println(" deg/s");
#elif defined PRINT_RAW
  Serial.print(imu.gx);
  Serial.print(", ");
  Serial.print(imu.gy);
  Serial.print(", ");
  Serial.println(imu.gz);
#endif
}
