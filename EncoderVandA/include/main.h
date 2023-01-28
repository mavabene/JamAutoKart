#include <Arduino.h>
#include <blink_led.h>
#include <pin.h>
#include <vars.h>
#include <utilities.h>
#include <steering.h>


Sensor *SteeringPot = new Sensor();
PidLoop *SteeringPID = new PidLoop();
Actuator *SteeringMotor = new Actuator();

void setup();

void loop();



