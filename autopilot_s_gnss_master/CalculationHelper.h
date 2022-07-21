#ifndef _CALCULATION_HELPER_CLASS
#define _CALCULATION_HELPER_CLASS

#include <Arduino.h>
#include <Wire.h>

#define CALC_ADRESS 47

class PreciseLatitude {
  private:
  short _degrees = 0;
  short _minutes = 0;
  float _decimals = 0;
  
  public:
  bool  IsValid = false;
  
  short Degrees()   { return _degrees; }
  short Minutes()   { return _minutes; }
  float Decimals()  { return _decimals; }

  PreciseLatitude();
  PreciseLatitude(short degrees, short minutes, float decimals);
  PreciseLatitude(const PreciseLatitude& copy);
  PreciseLatitude(char* input);
  
  PreciseLatitude  operator+ (const PreciseLatitude& other);
  PreciseLatitude  operator- (const PreciseLatitude& other);
  PreciseLatitude& operator+=( const PreciseLatitude& rhs);
  PreciseLatitude& operator-=(const PreciseLatitude& rhs);
  PreciseLatitude& operator= (const PreciseLatitude& copy);

  void print();
};

class PreciseLongitude {
  private:
  short _degrees = 0;
  short _minutes = 0;
  float _decimals = 0;
  
  public:
  bool  IsValid = false;
  
  short Degrees()   { return _degrees; }
  short Minutes()   { return _minutes; }
  float Decimals()  { return _decimals; }

  PreciseLongitude();
  PreciseLongitude(short degrees, short minutes, float decimals);
  PreciseLongitude(const PreciseLongitude& copy); 
  PreciseLongitude(char* input);

  PreciseLongitude  operator+ (const PreciseLongitude& other);
  PreciseLongitude  operator- (const PreciseLongitude& other);
  PreciseLongitude& operator+=( const PreciseLongitude& rhs);  
  PreciseLongitude& operator-=(const PreciseLongitude& rhs);
  PreciseLongitude& operator= (const PreciseLongitude& copy);

  void print();
  
};

class MapPosition {
  private:
  PreciseLatitude _latitude;
  PreciseLongitude _longitude;
  
  const float _fromMilesToMeters = 1852.107;
  const float _fromMilesToCantimeters = _fromMilesToMeters * 100;
  
  public:
  MapPosition();
  MapPosition(const MapPosition& copy); 
  MapPosition(PreciseLatitude& lat, PreciseLongitude& lon); 
  MapPosition(char* lat, char* lon);
  ~MapPosition();

  MapPosition  operator+ (const MapPosition& other); 
  MapPosition  operator- (const MapPosition& other);
  MapPosition& operator+=(const MapPosition& rhs);
  MapPosition& operator-=(const MapPosition& rhs);
  MapPosition& operator= (const MapPosition& copy);

  void  print();
  float DistanceInMeters(MapPosition& pos);
  float GetCoorinateX();
  float GetCoorinateY();
};

class CalcultionHelper
{
  private:
  float _rowLength = 0;
  float _rowDirection = 0;
  float _currentPosOffset = 0;
  
  float ReciveCalculatedValues();
  public:
  CalcultionHelper();
  ~CalcultionHelper();

  float SetSegmentA(char* lat, char* lon);
  float SetSegmentB(char* lat, char* lon);
  void UnsetSegmentA();
  void UnsetSegmentB();
  float UpdateCurrentPosition(char* lat, char* lon);
  float NewRowFromPosition(char* lat, char* lon);
  float NewRowFromPositionOpposite(char* lat, char* lon);
  void NotifySensorUpdate();

  float GetRowLength() { return _rowLength; }
  float GetRowDirection() { return _rowDirection; }
  float GetRowOffset() { return _currentPosOffset; }
};

#endif //_CALCULATION_HELPER_CLASS
