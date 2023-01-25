#include <Arduino.h>
#include <pin.h>

struct PidLoop
{
  float Kp = 1.0;
  float Kd = 1.0;
  float Ki = 1.0;
  float Setpoint = 1.0;
};

struct Sensor
{
  float Setpoint = 0; // desired position in Engineering units
  float EngVal = 0; // actual position in Eng units
  float SensorVal = 0; // actual input from sensor
  float SensorMax = 1; // maximum raw output of actuator
  float SensorMin = -1;
  float MaxEngVal = 1; // maximum engineering value we want to detect
  float MinEngVal = 1;
  float Perr = 0; // difference between actual position and desired position
  float Vel = 0;  // speed of actuator correlates to Verr
  float SumErr = 0; // integral error
  float Vff = 0; // Velocity feedforward term
};

struct Actuator
{
  bool isPositive = true; // whether desired command is pos or neg
  float CmdPct = 0; // percentage of max command to give
  float Cmd = 0; // actual command to be sent to actuator in raw units
  float CmdMax = 100; // max actual command actuator can receive
  float CmdMin = 0; 
  float ActMinEng = -100; // min position of Actuator in Engineering units
  float ActMaxEng = 100; // max position of Actuator in Engineering units
  float ActMinRaw = -100; // min position of Actuator in raw units
  float ActMaxRaw = -100; // max position of Actuator in raw units
  
};

// inputs - time start, time end, value start, value end
float getDx(int time_start, int time_end, float val_start, float val_end) {
    float time_delta = time_end - time_start;
    float val_delta = val_end - val_start;
    float Dx = val_delta/time_delta;
    // Serial.print("time start: ");
    // Serial.println(time_start, 1);
    // Serial.print("time end: ");
    // Serial.println(time_end, 1);
    // Serial.print("val start: ");
    // Serial.println(val_start, 1);
    // Serial.print("val end: ");
    // Serial.println(val_end, 1);
    return Dx;
}


// convert desired freq to number of ms per second to activate
float getMs(int freq)
{
    int ms = (1000/freq);
    return ms;
}

int getAnalogInt(int pin)
{
    int sensorValue = analogRead(pin);
    return sensorValue;
}

int SensorInputToUnitsInt(int sensorValue, int minSensorVal, int maxSensorVal, int minUnit, int maxUnit)
{
    sensorValue = max(sensorValue, minSensorVal);
    sensorValue = min(sensorValue, maxSensorVal);

    int val = map(sensorValue, minSensorVal, maxSensorVal, minUnit, maxUnit);
    return val;
}

int SensorInputToUnitsFloat(float sensorValue, float minSensorVal, float maxSensorVal, float minUnit, float maxUnit)
{
    float Value = max(sensorValue, minSensorVal);
    Value = min(sensorValue, maxSensorVal);

    float val = (Value-minSensorVal)/(maxSensorVal-minSensorVal)*(maxUnit-minUnit)+minUnit;
    return val;

}

float SensorInputToUnitsFloatPtr(Sensor *sens)
{
    float Value = max(sens->SensorVal, sens->SensorMin);
    Value = min(sens->SensorVal, sens->SensorMax);

    float val = (Value - sens->SensorMin)/(sens->SensorMax - sens->SensorMin)*(sens->MaxEngVal - sens->MinEngVal)+sens->MinEngVal;
    return val;

}

int UnitConversion(float before_val, float conversion_factor)
{
    float val = before_val*conversion_factor;
    return val;
}

void err(Sensor *sens)
{
    sens->Perr = sens->EngVal - sens->Setpoint;
}

void CtrlLoop(PidLoop *loop, Sensor *sens, Actuator *act)
{
    err(sens);
    act->CmdPct = loop->Kp * (-1.0) * sens->Perr - loop->Kd * sens->Vel + loop->Ki * sens->SumErr + sens->Vff;
    act->Cmd = (act->CmdPct/100) * act->CmdMax;
}


