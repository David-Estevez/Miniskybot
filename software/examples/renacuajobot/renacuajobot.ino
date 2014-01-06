#include <Servo.h>
#include <Configuration.h>
#include <Miniskybot.h>
#include <Miniskybot_motors.h>
#include <Miniskybot_sensors.h>
Miniskybot renacuajo;
void setup(){

 renacuajo.addServo(6,IZQUIERDA);
 renacuajo.addServo(9,DERECHA);
 pinMode(8,INPUT);
}

void loop(){

    renacuajo.servoControl(0,0);
    renacuajo.servoControl(0,1);

}
