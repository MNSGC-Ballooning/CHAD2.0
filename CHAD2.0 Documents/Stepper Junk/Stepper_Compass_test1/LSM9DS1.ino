
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
  //this funciton will calculate the attitude based on the Ixyz values and it will find the E values, then print the heading calculations
  updateAttitude(Ax, Ay, Az, Ix, Iy, Iz); 
}
