#include <Servo.h>
#include <Configuration.h>
#include <Miniskybot.h>
#include <Miniskybot_motors.h>
#include <Miniskybot_sensors.h>
Miniskybot renacuajo;
void setup(){

 renacuajo.addServo(6,LEFT);
 renacuajo.addServo(9,RIGHT);
 renacuajo.addSensor(FOLLOW,8,LEFT);
 renacuajo.addSensor(FOLLOW,7,RIGHT);
 pinMode(8,INPUT);
 Serial.begin(9600);
}

void loop(){
 //         renacuajo.servoControl(10,1);renacuajo.servoControl(10,0);
 renacuajo.followLine();
}
