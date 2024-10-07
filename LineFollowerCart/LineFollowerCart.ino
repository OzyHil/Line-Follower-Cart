#include <AFMotor.h>
AF_DCMotor motorE(1, MOTOR12_64KHZ);
AF_DCMotor motorD(4, MOTOR12_64KHZ);

const int NUM_SENSORS = 5;
const int IR_LED_PIN = 2;
//const int IR_RECEIVER_PINS[NUM_SENSORS] = {A4, A3, A2, A1, A0};

void setup() {
  Serial.begin(9600);
  pinMode(IR_LED_PIN, OUTPUT);
  digitalWrite(IR_LED_PIN, HIGH);

  motorD.setSpeed(200);
  motorD.run(RELEASE);
  motorE.setSpeed(200);
  motorE.run(RELEASE);
  delay(500);
}
 
void loop() {
  int S1_VALUE = analogRead(A0);
  int S2_VALUE = analogRead(A1);
  int S3_VALUE = analogRead(A2);
  int S4_VALUE = analogRead(A3);
  int S5_VALUE = analogRead(A4);
 // delay(500);
  
  if(S1_VALUE && S2_VALUE && S4_VALUE && S5_VALUE > 200 && S3_VALUE < 100 ){
    toForward();
  }

  if(S1_VALUE && S2_VALUE && S5_VALUE > 200 && S3_VALUE && S4_VALUE < 100 ){
    toRight();
  }

  if(S1_VALUE && S4_VALUE && S5_VALUE > 200 && S3_VALUE && S2_VALUE < 100 ){
    toLeft();
  }

  if(S1_VALUE && S2_VALUE && S3_VALUE && S4_VALUE && S5_VALUE < 200 ){
    stopMotors();
  }
}


void toForward(){
  motorE.run(FORWARD);
  motorE.setSpeed(200);
  motorD.run(FORWARD);
  motorD.setSpeed(200);
}

void toRight(){
 //motorD.run(RELEASE);
 motorD.setSpeed(80);
}

void toLeft(){
  //motorE.run(RELEASE);
  motorE.setSpeed(80);
}

void stopMotors(){
  motorE.run(RELEASE);
  motorD.run(RELEASE);
}
 