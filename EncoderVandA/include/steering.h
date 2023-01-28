#include <pin.h>
//#include <utilities.h>
//#include <vars.h>

void setupSteeringControl()
{
  // steering
    // Sensor *SteeringPot = new Sensor();
    // PidLoop *SteeringPID = new PidLoop();
    // Actuator *SteeringMotor = new Actuator();
  
    SteeringPID->Kp = 4;
    SteeringPID->Kd = 1;
    SteeringPID->Ki = 0;
    SteeringPot->SensorMin = 350;
    SteeringPot->SensorMax = 850;
    SteeringPot->MinEngVal = -45;
    SteeringPot->MaxEngVal = 45;
    SteeringPot->InputPin = STEERING_ANGLE_POT;
    SteeringPot->InputVarAdd = 30;

}