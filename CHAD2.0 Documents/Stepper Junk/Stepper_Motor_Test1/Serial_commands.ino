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
 

  /* Command List w/ format: <Command>
      DIR_F         <- sets direction to 'forward'
      DIR_R         <- sets direction to 'reverse'
      SET_RES####   <- Sets the resolution of steps/Revolution. possible: 200,400,800,1600
      STP####       <- Steps in current direction X steps
      STP_DEG####   <- Steps in current direction X degrees
      STP_REV####   <- Steps in current direction X revolutions
  */
  if ( commandInput.startsWith("DIR_F") ) {
    setDirF(currDIRState);   //pass in the current DIR state and change its state to Forward
    Serial.println("DIR set to F:  " + String(currDIRState));
  }
  else if (commandInput.startsWith("DIR_R")) {
    setDirR(currDIRState);
    Serial.println("DIR set to R:  " + String(currDIRState));
  }
  else if (commandInput.startsWith("SET_RES")) {
    commandInput.remove(0, 7); //remove preceding command
    //set the stepper resolution to what the command input was
    setStepperResolution( commandInput.toFloat(), currMS1State, currMS2State);
  }
  else if (commandInput.startsWith("STP_DEG")) {
    commandInput.remove(0,7);
    moveStepperDeg(commandInput.toFloat(), currDIRState); //move the stepper the number of degrees 
  }
  else if (commandInput.startsWith("STP_REV")) {
    commandInput.remove(0,7);
    moveStepperRev(commandInput.toFloat(), currDIRState); //move the stepper the number of steps specified
  }
  else if (commandInput.startsWith("STP")) {      //need to check for just the STP command last because it overwrited the STP_DEG and STP_REV commands
    commandInput.remove(0,3);
    moveStepperStp(commandInput.toFloat(), currDIRState); //move the stepper the number of steps
  }
  else if(commandInput.startsWith("RESET")){
    resetEDPins();
  }
  else {
    Serial.println("Invalid Command");
  }
  



}//end of readCommand()
