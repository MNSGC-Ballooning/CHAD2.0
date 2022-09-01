void serialCommandCheck() {

  //checks is any commands have been entered
  if (Serial.available()) {
    String serialcommand = Serial.readStringUntil('\n');
    Serial.print("You typed: " );
    Serial.println(serialcommand);
    readCommand(serialcommand);
  }
}

void readCommand(String commandInput) {
  //Took out the secion to use '<' '>' surrounding commands
  /* Command List w/ format: <Command>
   *  -----------Stepper commands-----------------
      DIR_F         <- sets direction to 'forward'
      DIR_R         <- sets direction to 'reverse'
      SET_RES####   <- Sets the resolution of steps/Revolution. possible: 200,400,800,1600
      STP####       <- Steps in current direction X steps
      STP_DEG####   <- Steps in current direction X degrees
      STP_REV####   <- Steps in current direction X revolutions
      -----------GPS commands ---------------------
      TARGETLAT####   <-- sets the user defined target's latitude (latitude to point at)in decimal degrees
      TARGETLON####  <-- sets a user defined target's longitude (longitude to point at) in decimal degrees
      TARGETALT#### <-- sets a user defined target's Altitude (altitude to point at) in feet
      LAT###        <--- sets the current Lat if not using the GPS to get current Lat
      LON###        <--- sets the current LON if not using the GPS to get current LON
      ALT###        <--- sets the current ALT if not using the GPS to get current alt
  */
  if ( commandInput.startsWith("DIR_F") ) {
    stepper.setDirF();   //pass in the current DIR state and change its state to Forward
    Serial.println("DIR set to F:  " + String(stepper.currDIRState));
  }
  else if (commandInput.startsWith("DIR_R")) {
    stepper.setDirR();
    Serial.println("DIR set to R:  " + String(stepper.currDIRState));
  }
  else if (commandInput.startsWith("SET_RES")) {
    commandInput.remove(0, 7); //remove preceding command
    //set the stepper resolution to what the command input was
    stepper.setStepperResolution( commandInput.toFloat() );
  }
  else if (commandInput.startsWith("STP_DEG")) {
    commandInput.remove(0, 7);
    stepper.moveStepperDeg( commandInput.toFloat() ); //move the stepper the number of degrees
  }
  else if (commandInput.startsWith("STP_REV")) {
    commandInput.remove(0, 7);
    stepper.moveStepperRev( commandInput.toFloat() ); //move the stepper the number of steps specified
  }
  else if (commandInput.startsWith("STP")) {      //need to check for just the STP command last because it overwrited the STP_DEG and STP_REV commands
    commandInput.remove(0, 3);
    stepper.moveStepperStp( commandInput.toFloat() ); //move the stepper the number of steps
  }
  else if (commandInput.startsWith("RESET")) {
    stepper.resetEDPins();
  }
  else if ( commandInput.startsWith("TARGETLAT") ) {          //command is to set the latitiude
    commandInput.remove(0, 9); //remove the preceing command
    targetLat = commandInput.toFloat(); //set the remaining numbers trailing the command to latitude
    Serial.println("New Target Latitude Set Due to Command");
  }
  else if (commandInput.startsWith("TARGETLON")) {          //command is to set the longitude
    commandInput.remove(0, 9); //remove the preceing command
    targetLon = commandInput.toFloat(); //set the remaining numbers trailing the command to latitude
    Serial.println("New Target longitude Set Due to Command");
  }
  else if (commandInput.startsWith("TARGETALT")) {          //command is to set the longitude
    commandInput.remove(0, 9); //remove the preceing command
    targetAlt = commandInput.toFloat(); //set the remaining numbers trailing the command to latitude
    Serial.println("New Target Altitude Set Due to Command");
  }
  else if ( commandInput.startsWith("GPSOFF") ) {           //command to stop using the GPS to update LLA data
    useGPS = false;
    Serial.println("Not using GPS");
  }
  else if (commandInput.startsWith("GPSON")) {          //command is to set the longitude
    useGPS = true;
    Serial.println("Using GPS");
  }
  else if (commandInput.startsWith("LAT")) {          //command is to set the longitude
    commandInput.remove(0, 3); //remove the preceing command
    currLatitude = commandInput.toFloat(); //set the remaining numbers trailing the command to latitude
    Serial.println("New user specified Lat Set Due to Command");
  }
  else if (commandInput.startsWith("LON")) {          //command is to set the longitude
    commandInput.remove(0, 3); //remove the preceing command
    currLongitude = commandInput.toFloat(); //set the remaining numbers trailing the command to latitude
    Serial.println("New user specified Lon Set Due to Command");
  }
  else if (commandInput.startsWith("ALT")) {          //command is to set the longitude
    commandInput.remove(0, 3); //remove the preceing command
    currAltitude = commandInput.toFloat(); //set the remaining numbers trailing the command to latitude
    Serial.println("New user specified Alt Set Due to Command");
  }
  else {
    Serial.println("Invalid Command");
  }


}//end of readCommand()
