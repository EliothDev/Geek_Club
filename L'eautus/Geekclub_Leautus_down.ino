#include <AFMotor.h>


AF_Stepper motor(200, 2);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");

  motor.setSpeed(30);  // 10 rpm   

  motor.step(1000, BACKWARD, SINGLE); 
  motor.release();

}

void loop() {

}
