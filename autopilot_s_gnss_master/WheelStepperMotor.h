#ifndef _WHEEL_STEPPER_MOTOR_CLASS
#define _WHEEL_STEPPER_MOTOR_CLASS

#include <Arduino.h>
#include <Wire.h>

#define WHEEL_ADRESS 23

class WheelStepperMotor
{
  //string m_strError = L"";
  public:
  WheelStepperMotor();
  ~WheelStepperMotor();
  
  void RotateTo(int deg);
  void UpdateAgression(int agress);
  int GetWheelPosition();
  void PowerSwitch(bool powerOn);
  int SetWheelCenter(int center = -1);
  
};

#endif //_WHEEL_STEPPER_MOTOR_CLASS
