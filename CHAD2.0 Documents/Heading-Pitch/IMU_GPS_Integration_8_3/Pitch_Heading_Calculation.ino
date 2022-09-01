
// Calculate roll pitch and heading, as described in that order, the variables being passed are in the same frame and should always be maped using the calcAcc() (etc. function)
void printAttitude(float aX, float aY, float aZ, float mX, float mY, float mZ)
{
  // 1-2-3 rotation
  float roll = atan2(aY, aZ);
  float pitch = atan2(-aX, sqrt(aY * aY + aZ * aZ)); //needs a neg x to get correct orientation
  float heading = calcHeading(mX, mY, mZ);

  // Below taking the Ixyz variables and trying to convert them into Exyz to compensate for tilt
  float  rollrad = -roll; //roll and pitch are already in radians, negate because we are going from I frame to the E frame
  float  pitchrad = -pitch;
  
  Ex = (cos(pitchrad) * Ix) + (-1 * sin(pitchrad) * Iz);
  Ey = (sin(pitchrad) * sin(rollrad) * Ix) + (cos(rollrad) * Iy) + (sin(rollrad) * cos(pitchrad) * Iz);
  Ez = cos(rollrad) * sin(pitchrad) * Ix + (-1 * sin(rollrad) * Iy) + (cos(rollrad) * cos(pitchrad) * Iz);

  //Section to print everything:
  Serial.print("Corrected M (Exyz): ");
  Serial.print(Ex, 5);
  Serial.print(", ");
  Serial.print(Ey, 5);
  Serial.print(", ");
  Serial.print(Ez, 5);
  Serial.println("");
  // Convert everything from radians to degrees:
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;

  Serial.print("Pitch, Roll: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
  Serial.print("Heading based on Ixyz: "); Serial.println(heading, 2);


  Serial.print("Heading based on Exyz variables: ");   
  Serial.print(calcHeading(Ex, Ey, Ez));
  Serial.println("\t\tAverage Heading: " + String(saveAveHeading(calcHeading(Ex, Ey, Ez))));
  Serial.println();
}

//^^^^^^^^^^^^^^^^^^Function to calculate heading wrt magnetic north, based off of passes x,y,z magnetometer variables ^^^^^^^^^^
//returns heading in degrees
float calcHeading(float mX, float mY, float mZ) {
  float heading;

  if (mY == 0)
    heading = (mX < 0) ? PI : 0;  //check
  else
    heading = atan2(mY, mX);  //the y value here is negative to get into common compass rose frame so where x is north and y is east

  heading -= DECLINATION * PI / 180;

  //convert heading back into rad
  heading *= float(180) / PI;

  return heading;
}

//^^^^^^^^^^^^^^^^^^^function that will save the average heading when one is passed in^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
double saveAveHeading(float newHeading) { // there is a ~5s delay in the calculation of Ave heading because it takes last 50 heading with new data every 10th of a second

  for (int i = (aveHeadingLength - 1); i > 0; i--) { //aveHeadingLength -1 is last spot bc nth spot is array[n-1]
    aveHeading[i] = aveHeading[i - 1];
  }
  aveHeading[0] = newHeading;
 

  return printAveHeading();
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^function that prints the average heading across the last 5 seconds ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
double printAveHeading(){
  double out = 0;
  
  for (int i = 0; i < aveHeadingLength; i++) {
    out += aveHeading[i];
  }
  out /= double(aveHeadingLength);
  return out;
}
