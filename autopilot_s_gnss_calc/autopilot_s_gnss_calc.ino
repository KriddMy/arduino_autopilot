#include <Wire.h>
#include <TroykaIMU.h>
#include "coordinates_helper.h"

#define I2C_ADDRESS 47

Madgwick      Filter;
Gyroscope     Gyroscope;
Accelerometer Accelerometer;

volatile float Yaw = 0, Pitch = 0, Roll = 0;

float LastYaw = 0, LastPitch = 0, LastRoll = 0;

//константы сообщений по I2C шине
const String SET_A("SEA");
const String NOTIFY_SENSOR_UPDATE("NSA");
const String SET_B("SEB");
const String UNSET_A("USA");
const String UNSET_B("USB");
const String NEW_FROM_PSN("NPN");
const String NEW_FROM_PSN_OPPOSITE("NPO");
const String UPDATE_POSITION("UPO");

RowSegment cRowSegment;

bool IsPointA = false;
bool IsPointB = false;

MapPosition cPointA;
MapPosition cPointB;
MapPosition cCurrentPos;

float Offset = 0;
float RawDirection = 0;
float RawLength = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial speed 9600");
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(recieveEvent);
  Wire.onRequest(requestEvent);
  
  Gyroscope.begin();
  Accelerometer.begin();
  Filter.begin();
}

void loop() {
  unsigned long startMillis = millis();
  static float updateRate = 100;
  float gx, gy, gz, ax, ay, az;
  
  Accelerometer.readAccelerationGXYZ(ax, ay, az);
  Gyroscope.readRotationRadXYZ(gx, gy, gz);
  Filter.setFrequency(updateRate);
  Filter.update(gx, gy, gz, ax, ay, az);
  
  Yaw = Filter.getYawDeg();
  Pitch = Filter.getPitchDeg();
  Roll = Filter.getRollDeg();
  
  //Serial.print("Yaw: ");
  //Serial.println(Yaw);
  //Serial.print("Pitch: ");
  //Serial.println(Pitch);
  //Serial.print("Roll: ");
  //Serial.println(Roll);
  
  unsigned long deltaMillis = millis() - startMillis;
  updateRate = 1000 / deltaMillis;
}

void requestEvent()
{
  byte msg[12];
  
  msg[0] = ((uint8_t*)&Offset)[0];
  msg[1] = ((uint8_t*)&Offset)[1];
  msg[2] = ((uint8_t*)&Offset)[2];
  msg[3] = ((uint8_t*)&Offset)[3];

  msg[4] = ((uint8_t*)&RawDirection)[0];
  msg[5] = ((uint8_t*)&RawDirection)[1];  
  msg[6] = ((uint8_t*)&RawDirection)[2];
  msg[7] = ((uint8_t*)&RawDirection)[3];

  msg[8] = ((uint8_t*)&RawLength)[0];
  msg[9] = ((uint8_t*)&RawLength)[1];  
  msg[10] = ((uint8_t*)&RawLength)[2];
  msg[11] = ((uint8_t*)&RawLength)[3];

  Wire.write(msg, 12);
}

void recieveEvent(int num) {
  String sCode;
  String latitude;
  String longitude;
  latitude.reserve(32);
  longitude.reserve(32);
  unsigned int errorCheck = 0;

  for(int i = 0; i < 3; i++)
  {
    char c = Wire.read();
    sCode += c;
    errorCheck++;
  }
  
  while(errorCheck < num)
  {
    char t = Wire.read();
    if(t == ' ' || t == '\0')
      break;
      
    latitude += t;
    errorCheck++;
  }

  while(errorCheck < num)
  {
    char t = Wire.read();
    if(t == ' ' || t == '\0')
      break;
      
    longitude += t;
    errorCheck++;
  }

  char lat[latitude.length() + 1];
  char lon[longitude.length() + 1];
 
  latitude.toCharArray(lat, latitude.length() + 1);
  longitude.toCharArray(lon, longitude.length() + 1);

  Serial.print(sCode);
  Serial.print(" ");
  Serial.print(latitude);
  Serial.print(" ");
  Serial.println(longitude);

  if(SET_A.equals(sCode))
  {
    cPointA = MapPosition(lat, lon);
    IsPointA = true;
    if(IsPointB)
    {
      RawDirection = cRowSegment.SetSegment(cPointA, cPointB);
      RawLength = cRowSegment.GetRowLength();
    }
  }
  else if(SET_B.equals(sCode))
  {     
    cPointB = MapPosition(lat, lon);
    IsPointB = true;
    if(IsPointA)
    {
      RawDirection = cRowSegment.SetSegment(cPointA, cPointB);
      RawLength = cRowSegment.GetRowLength();
    }
  }
  else if(NEW_FROM_PSN.equals(sCode))
  {
    MapPosition temp = MapPosition(lat, lon);
    cPointA = temp;
    RawDirection = cRowSegment.UpdateOriginPosition(temp);
  }
  else if(NEW_FROM_PSN_OPPOSITE.equals(sCode))
  {    
    MapPosition temp = MapPosition(lat, lon);
    cPointB = temp;
    RawDirection = cRowSegment.UpdateOriginPosition(temp, true);
  }
  else if(UNSET_A.equals(sCode))
  {
    IsPointA = false;
  }
  else if(UNSET_B.equals(sCode))
  {
    IsPointB = false;
  }
  else if(UPDATE_POSITION.equals(sCode))
  {
    if(IsPointA && IsPointB)
    {
      cCurrentPos = MapPosition(lat, lon);
      Serial.print("Roll: ");
      Serial.println(LastRoll);
      Offset = cRowSegment.UpdateCurrentPosition(cCurrentPos, LastRoll);
    }
    else
    {
      Offset = 0;
      RawDirection = 0;
      RawLength = 0;
    }
  }
  else if(NOTIFY_SENSOR_UPDATE.equals(sCode))
  {
    LastYaw = Yaw;
    LastPitch = Pitch;
    LastRoll = Roll;
  }
}
