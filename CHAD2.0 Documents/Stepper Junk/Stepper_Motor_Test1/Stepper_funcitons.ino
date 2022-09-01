//funcitons to control stepper motor

//funciton sets all of the Easy Driver pins to default
void resetEDPins()
{
  //need to reset all of these variables to default settings
  currMS1State = defaultMS1State;
  currMS2State = defaultMS2State;
  currDIRState = defaultDIRState;
  digitalWrite(stp, LOW); //reset step pin
  digitalWrite(dir, defaultDIRState); //set direction to 'forward'
  digitalWrite(MS1, defaultMS1State); //set to default step/revolution
  digitalWrite(MS2, defaultMS2State);
  digitalWrite(EN, HIGH); //disable stepper motor movement
}


//function to change direction state to forward
void setDirF(uint8_t &DIR) {
  DIR = FORWARD;
}

//function to change direction state to reverse
void setDirR(uint8_t &DIR) {
  DIR = REVERSE;
}

//funciton to change step resolution. Input requested resolution, MS1 state variable, MS2 state variable
void setStepperResolution(int userResolution, uint8_t &ms1, uint8_t &ms2) {
  switch (userResolution) {
    case 200:
      ms1 = LOW;
      ms2 = LOW;
      break;
    case 400:
      ms1 = HIGH;
      ms2 = LOW;
      break;
    case 800:
      ms1 = LOW;
      ms2 = HIGH;
      break;
    case 1600:
      ms1 = HIGH;
      ms2 = HIGH;
      break;
    default:
      Serial.println("Invalid resolution requested. Possible: 200, 400, 800, 1600");
      break;
  }
  Serial.println("Step/Rev: " + String(getRes(ms1, ms2)));
}

//function to return the current Resolution in steps/Resolution

int getRes(uint8_t &ms1, uint8_t &ms2) {
  int out = 200;
  if (ms1 == LOW) {
    if (ms2 == LOW) {
      out = 200;      // L,L
    } else {
      out = 800;      // L,H
    }
  } else {
    if (ms2 == LOW) {
      out = 400;      // H,L
    } else {
      out = 1600;      //H,H
    }
  }
  return out;
}

//function to step the motor forward X steps
void moveStepperStp(int numSteps, uint8_t dirState) {
  Serial.println("Stepping " + String(numSteps) + " steps...");
  //enable movement
  digitalWrite(EN, LOW);           //enable stepper movement
  digitalWrite(dir, dirState);     //determine direction of step
  digitalWrite(MS1, currMS1State); //writing the current resolution before moving
  digitalWrite(MS2, currMS2State);
  
  for (int stepCount = 0; stepCount < numSteps; stepCount++)
  {
    digitalWrite(stp, HIGH);
    delay(1);                 //total delay for 1 loop is 2 millis, so 500 steps/second
    digitalWrite(stp, LOW);
    delay(1);
  }
  digitalWrite(EN, HIGH);      //disable movement
}

//function to step the motor forward X degrees. Input the number of degrees to turn and 
void moveStepperDeg(float numDeg, const uint8_t dirState) {
  //convert degrees into number of steps by taking resolution 
  float stepsToMove = float(getRes(currMS1State, currMS2State)) / 360.0; //steps to move needs to be a float otherwise the precision is lost 
  Serial.println("Steps/Deg: " + String(stepsToMove));
  stepsToMove *= numDeg;
  Serial.println("Stepping " + String(stepsToMove) + " steps");
  moveStepperStp(stepsToMove, dirState);    //move the stepper motor the calculated number of steps (rounded down)
}

//funciton to step the motor forward X revolutions. Input num of Rev to move and direction
void moveStepperRev(float numRev, const uint8_t dirState){
  //convert number of revolutions to steps
  int stepsToMove = getRes(currMS1State, currMS2State) * numRev;    //<-- lines like this will be rewritted when we make a struct out of the stepper motor/ED
  
  moveStepperStp(stepsToMove, dirState);
}
