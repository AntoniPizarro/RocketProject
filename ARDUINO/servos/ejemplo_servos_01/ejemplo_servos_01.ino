#include <Servo.h>

Servo servoMotor_1;
Servo servoMotor_2;
Servo servoMotor_3;
Servo servoMotor_4;

void setup() {
  Serial.begin(115200);

  servoMotor_1.attach(7);
  //servoMotor_2.attach(8);
  //servoMotor_3.attach(9);
  //servoMotor_4.attach(10);
}

void loop() {
  for (int i = 0; i <= 180; i++) {
    Serial.println("=============");
    servoMotor_1.write(i);
    Serial.print("motor_1 = ");
    Serial.println(servoMotor_1.read());

    //servoMotor_2.write(i);
    //Serial.print("motor_2 = ");
    //Serial.println(servoMotor_2.read());

    //servoMotor_3.write(i);
    //Serial.print("motor_3 = ");
    //Serial.println(servoMotor_3.read());

    //servoMotor_4.write(i);
    //Serial.print("motor_4  = ");
    //Serial.println(servoMotor_4.read());
    delay(50);
  }
  
  for (int i = 180; i >= 0; i--) {
    Serial.println("=============");
    servoMotor_1.write(i);
    Serial.print("motor_1 = ");
    Serial.println(servoMotor_1.read());

    //servoMotor_2.write(i);
    //Serial.print("motor_2 = ");
    //Serial.println(servoMotor_2.read());

    //servoMotor_3.write(i);
    //Serial.print("motor_3 = ");
    //Serial.println(servoMotor_3.read());

    //servoMotor_4.write(i);
    //Serial.print("motor_4  = ");
    //Serial.println(servoMotor_4.read());
    delay(10);
  }
}