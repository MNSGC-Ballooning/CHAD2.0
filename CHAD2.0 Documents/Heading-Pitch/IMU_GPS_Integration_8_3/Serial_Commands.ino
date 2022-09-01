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
  char startMarker = '<';
  char endMarker = '>';
  int indx = 0;
  int inputLength = commandInput.length();
  
  //checks if there is a valid command
  if (commandInput[indx] != startMarker && commandInput[inputLength - 1] != endMarker) {
    Serial.println("Invalid command");
    return; // end function if no command present
  }
  
  String commandWoMarkers = "";
  for (int i = 1; i < inputLength - 1; i++) {
    commandWoMarkers += commandInput[i];
  }

  //save commandInput as commandW/o markers thus removing the start and end markers from the command
  commandInput = String(commandWoMarkers);

  //switch that designates what command has been entered.
  /* Command List:
      TARGETLAT####   <-- sets the user defined target's latitude (latitude to point at)in decimal degrees
      TARGETLON####  <-- sets a user defined target's longitude (longitude to point at) in decimal degrees
      TARGETALT#### <-- sets a user defined target's Altitude (altitude to point at) in feet
      LAT###        <--- sets the current Lat if not using the GPS to get current Lat
      LON###        <--- sets the current LON if not using the GPS to get current LON
      ALT###        <--- sets the current ALT if not using the GPS to get current alt
  */
  if ( commandInput.startsWith("TARGETLAT") ) {           //command is to set the latitiude
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
    Serial.println("INVALID COMMAND");
  }
}
