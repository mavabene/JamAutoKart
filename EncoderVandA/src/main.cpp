
#include <main.h>

/*
blink an led at different rates to compare what freq appears solid to different people
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  setupLED();
  init1=true;
  SteeringPID->Kp = 4;
  SteeringPID->Kd = 1;
  SteeringPID->Ki = 0;
  SteeringPot->SensorMin = 350;
  SteeringPot->SensorMax = 850;
  SteeringPot->MinEngVal = -45;
  SteeringPot->MaxEngVal = 45;
  // SteeringMotor->ActMaxEng = xx;
  // SteeringMotor->ActMinEng = xx;
  // SteeringMotor->ActMaxRaw = xx;
  // SteeringMotor->ActMinRaw = xx;
  // SteeringMotor->CmdMax = xx;
  // SteeringMotor->CmdMin = xx;
}

// the loop function runs over and over again forever
void loop() {
  
  if (init1==true)
    {
      
      init1=false;
    }
  
  currentMillis = millis();
  SteeringPot->SensorVal = getAnalogInt(STEERING_ANGLE_POT);
  SteeringPot->Setpoint = 30;
  CtrlLoop(SteeringPID,SteeringPot,SteeringMotor);
  current_angle = SensorInputToUnitsFloatPtr(SteeringPot);
  SteeringPot->EngVal = current_angle;

  //sens->EngVal - sens->Setpoint;
  
  // float min_sensor_value = 350;
  // float max_sensor_value = 850;
  //  Steering_pot_inputVal = getAnalogInt(STEERING_ANGLE_POT);
  // current_angle = SensorInputToUnitsFloat(Steering_pot_inputVal, min_sensor_value, max_sensor_value, min_detectable_angle, max_detectable_angle);
 

  if ((currentMillis-startMillis) >= 1) // && (current_angle != start_angle))
    { 
        Serial.print("Current angle: ");
        Serial.print(current_angle, 1);
        Serial.print("\t");
        Serial.print("Angular Velocity: ");
        Serial.print(SteeringPot->Vel, 1);
        Serial.print("\t");

        Serial.print("\t");
        Serial.print("Perr: ");
        Serial.print(SteeringPot->Perr, 1);

        Serial.print("\t");
        Serial.print("Cmd: ");
        Serial.println(SteeringMotor->CmdPct, 1);

        // Serial.print("Current raw pot value: ");
        // Serial.println(Steering_pot_inputVal, 1);
        startMillis = currentMillis;
    }

  if (((currentMillis-angle_detect_start_time) >= 20)) // set up time interval for getting dx
    { 
      steering_angular_vel = getDx(angle_detect_start_time, currentMillis, start_angle, current_angle);
      SteeringPot->Vel = UnitConversion(steering_angular_vel,deg_per_ms_TO_deg_per_sec);
      start_angle = current_angle;
      angle_detect_start_time = currentMillis;
    }

}

