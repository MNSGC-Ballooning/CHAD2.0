//this tab is for the logic that controls how the stepper moves to compensate for incorrect heading

/* go through every 2 seconds check your average heading from last 5 seconds,
    if current average heading differs from the required heading by more than 20 degrees, then move the required difference to correct for the error

      idea to break up the movement into smaller steps and move every iteration of the loop?
*/

#define HEADING_SENSITIVITY 45   //this is the variable that controls when to move the stepper morot to correct for drift
#define LOGIC_SPEED 6000         // rechecks logic every 5 seconds

void headingCorrection() {
   //if it has not been LOGIC_SPEED milliseconds since last logic check then dont preform logic check
  if( (logicControlLastPrint + LOGIC_SPEED) > millis() ){
    return;
  }
  //assuming the currHeading is the average heading (ave across 5 sec)
  double reqHeadingChange = calcReqBearing(targetLat, targetLon, currLatitude, currLongitude, printAveHeading()); 

  //checking if the required change in heading is more than HEADING_SENSITIVITY
  if( abs(reqHeadingChange) >= HEADING_SENSITIVITY ){

    if( reqHeadingChange < 0 ) {
      stepper.setDirR();
      Serial.println("Stepper dir set to R");
    } else {
      stepper.setDirF();
      Serial.println("Stepper dir set to F");
    }
    Serial.println("##### request to move stepper " + String(reqHeadingChange,4) + " degrees");
    stepper.moveStepperDeg(reqHeadingChange);
  }
  //reset the logic control timer
  logicControlLastPrint = millis();
}
