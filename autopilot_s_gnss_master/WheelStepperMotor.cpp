#include "WheelStepperMotor.h"
#include "ErrorHandler.h"

extern ErrorHandler ErrHandler;

WheelStepperMotor::WheelStepperMotor() {
  Wire.begin();
}

WheelStepperMotor::~WheelStepperMotor() {
  Wire.end();
}

void WheelStepperMotor::RotateTo(int deg) 
{
  byte msg[5];
  msg[0] = 'A';
  msg[1] = 'N';
  msg[2] = 'G';
  msg[3] = deg >> 8;
  msg[4] = deg;
  
  Wire.beginTransmission(WHEEL_ADRESS   );
  Wire.write(msg, sizeof(msg));

  if(Wire.endTransmission() == 0)
    ErrHandler.UnsetError(ERR_NOWHEEL_CONNECTION);
  else
    ErrHandler.SetError(ERR_NOWHEEL_CONNECTION);
}

void WheelStepperMotor::UpdateAgression(int agress)
{
  byte msg[5];
  msg[0] = 'A';
  msg[1] = 'G';
  msg[2] = 'R';
  msg[3] = agress >> 8;
  msg[4] = agress;
  Wire.beginTransmission(WHEEL_ADRESS);
  Wire.write(msg, sizeof(msg));
  if(Wire.endTransmission() == 0)
    ErrHandler.UnsetError(ERR_NOWHEEL_CONNECTION);
  else
    ErrHandler.SetError(ERR_NOWHEEL_CONNECTION);
}

int WheelStepperMotor::GetWheelPosition()
{
  unsigned char rawValue[2];
  int value;
  
  Wire.requestFrom(WHEEL_ADRESS, 2);
  for(int i = 0; i < 2; i++)
  {
    rawValue[i] = Wire.read();
  }
  
  value = (rawValue[0] << 8) | (rawValue[1]);
  return value;
}

void WheelStepperMotor::PowerSwitch(bool powerOn)
{
  byte msg[5];
  
  //драйвер выключается при 1 (обратная логика)
  powerOn = !powerOn;
  
  msg[0] = 'P';
  msg[1] = 'W';
  msg[2] = 'R';
  msg[3] = powerOn >> 8;
  msg[4] = powerOn;
  Wire.beginTransmission(WHEEL_ADRESS);
  Wire.write(msg, sizeof(msg));
  if(Wire.endTransmission() == 0)
    ErrHandler.UnsetError(ERR_NOWHEEL_CONNECTION);
  else
    ErrHandler.SetError(ERR_NOWHEEL_CONNECTION);
}

int WheelStepperMotor::SetWheelCenter(int center = -1)
{
  byte msg[5];
  msg[0] = 'C';
  msg[1] = 'T';
  msg[2] = 'R';
  msg[3] = center >> 8;
  msg[4] = center;
  Wire.beginTransmission(WHEEL_ADRESS);
  Wire.write(msg, sizeof(msg));
  if(Wire.endTransmission() == 0)
    ErrHandler.UnsetError(ERR_NOWHEEL_CONNECTION);
  else
    ErrHandler.SetError(ERR_NOWHEEL_CONNECTION);
  
  if(center != -1) {
    return center;
  }

  unsigned char rawValue[4];
  int value;

  Wire.requestFrom(WHEEL_ADRESS, 4);

  for(int i = 0; i < 4; i++)
  {
    rawValue[i] = Wire.read();
  }
  
  value = (rawValue[2] << 8) | (rawValue[3]);
  return value;
}
