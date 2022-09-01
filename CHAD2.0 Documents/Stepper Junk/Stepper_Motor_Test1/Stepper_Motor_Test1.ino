//This is code that is meant as practice coding the motor controler and stepper motor

//should make a struct with all of the states and whatnot in it

//declairing pins for the motor controller.
#define stp 2 //define stp as pin 2 (this controls if step is taking place, transition from LOW -> HIGH makes motor move one (1) step
#define dir 3 //defines direction pin as pin 3. This pin controls motor direction 
#define MS1 4 //This pin in tandem with MS2 controls the step size, 
#define MS2 5 //(MS1,MS2): (L,L) = 200stp/Rev   (H,L) = 400stp/Rev    (L,H) = 800Stp/Rev    (H,H) = 1600Stp/Rev
#define EN 6 //Enable pin defined as 6, this pin allows motor movement. LOW -> movement allowed, HIGH -> prevents movement

#define FORWARD LOW     //define the forward/backward direction
#define REVERSE HIGH

uint8_t defaultMS1State = HIGH;   //set the default MS1 and MS2 variables, default to 1600stp/Rev
uint8_t defaultMS2State = HIGH;
uint8_t currMS1State = defaultMS1State;  //the 'set' MS# variables will be changed as user requests
uint8_t currMS2State = defaultMS2State;
int currResolution = 1600;
uint8_t defaultDIRState = FORWARD;    //set default direction to 'forward'
uint8_t currDIRState = defaultDIRState;

#include <Stepper_Header_Test_1.h>
ROB_STEPPER_MOTOR stepper;

void setup() {
  //setup pins as output pins
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  //reset the Easy Driver pins to default conditions (should do this after each command)
  resetEDPins();

  

  //setup Serial monitor
  Serial.begin(9600);
  Serial.println("Begin Serial");

  
}

void loop() {
  //checks if command has been entered every loop
  serialCommandCheck();
  if(millis() % 1000 == 0){
   // Serial.println(stepper.stpPin);
    delay(1);
  }
  
  

}
