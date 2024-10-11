#include <AFMotor.h>

AF_DCMotor motorE(3, MOTOR12_64KHZ);
AF_DCMotor motorD(2, MOTOR12_64KHZ);

const int motorSpeed = 110, 
const int turningMotorSpeed = 170;
const int lineThresh = 200;
const int noLineThresh = 20;

void setup() {
  motorD.setSpeed(motorSpeed);
  motorE.setSpeed(motorSpeed);
  stopMotors(); 
  delay(500);
}
 
void loop() {
  int s1v = analogRead(A0); //Left most sensor
  int s2v = analogRead(A1); //Left sensor
  int s3v = analogRead(A2); //Middle sensor
  int s4v = analogRead(A3); //Right sensor
  int s5v = analogRead(A4); //Right most sensor

  //If only middle sensor detects black line 1-1-0-1-1
  if((s1v > lineThresh) && (s2v > lineThresh) && (s3v < noLineThresh) && (s4v > lineThresh) && (s5v > lineThresh)){
    toForward();
  }

  //If only left sensor detects black line 1-0-1-1-1
  if((s1v > lineThresh) && (s2v < noLineThresh)  && (s3v > lineThresh) && (s4v > lineThresh) && (s5v > lineThresh)){
    toLeft();
  }

  //If only left most sensor detects black line 0-1-1-1-1
  if((s1v < noLineThresh)  && (s2v > lineThresh) && (s3v > lineThresh) && (s4v > lineThresh) && (s5v > lineThresh)){  
    performTurn(FORWARD, BACKWARD);
  }

  //If only right sensor detects black line 1-1-1-0-1
  if((s1v > lineThresh) && (s2v > lineThresh)  && (s3v > lineThresh) && (s4v < noLineThresh) && (s5v > lineThresh)){ 
    toRight();
  }

  //If only right most sensor detects black line 1-1-1-1-0
  if((s1v > lineThresh) && (s2v > lineThresh)  && (s3v > lineThresh) && (s4v > lineThresh) && (s5v < noLineThresh)){ 
    performTurn(BACKWARD, FORWARD);
  } 

  //If middle and right sensor detects black line 1-1-0-0-1
  if((s1v > lineThresh) && (s2v > lineThresh)  && (s3v < noLineThresh) && (s4v < noLineThresh) && (s5v > lineThresh)){ //
    toRight();
  } 

  //If middle and left sensor detects black line 1-0-0-1-1
  if((s1v > lineThresh) && (s2v < noLineThresh)  && (s3v < noLineThresh) && (s4v > lineThresh) && (s5v > lineThresh)){
    toLeft();
  }

  //If middle, left and left most sensor detects black line 0-0-0-1-1
  if((s1v < noLineThresh) && (s2v < noLineThresh)  && (s3v < noLineThresh) && (s4v > lineThresh) && (s5v > lineThresh)){
    toLeft();
  }

  //If middle, right and right most sensor detects black line 1-1-0-0-0
  if((s1v > lineThresh) && (s2v > lineThresh)  && (s3v < noLineThresh) && (s4v < noLineThresh) && (s5v < noLineThresh)){
    toRight();
  } 

  //If all sensors are off black line 1-1-1-1-1
  if((s1v > lineThresh) && (s2v > lineThresh) && (s3v > lineThresh) && (s4v > lineThresh) && (s5v > lineThresh)){
    toForward();
  }
  
  //If all sensors are on black line 0-0-0-0-0
  if((s1v < lineThresh) && (s2v < lineThresh) && (s3v < lineThresh) && (s4v < lineThresh) && (s5v < lineThresh)){ 
    stopMotors();
  }
}

void toForward(){
  motorD.run(FORWARD);
  motorE.run(FORWARD);
  motorD.setSpeed(motorSpeed);
  motorE.setSpeed(motorSpeed);
}

void toRight(){
  motorD.run(RELEASE);
  motorE.run(FORWARD);
  motorE.setSpeed(motorSpeed);
}

void toLeft(){
  motorD.run(FORWARD);
  motorE.run(RELEASE);
  motorD.setSpeed(motorSpeed);
}

void stopMotors(){
  motorD.run(RELEASE);
  motorE.run(RELEASE);
}

void performTurn(uint8_t x, uint8_t y) {
    motorD.run(x);
    motorE.run(y);
    motorD.setSpeed(turningMotorSpeed);
    motorE.setSpeed(turningMotorSpeed);
}