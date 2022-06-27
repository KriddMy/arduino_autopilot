#include <Arduino.h>

#define ANTENNA_HIGHT 2.2f

struct ScenePosition {
  float X;
  float Y;
};

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

class RowSegment
{
  private:
  bool        _isOriginSet = false;
  MapPosition _origin;

  const ScenePosition _zeroPosition = { 0, 0 };
  ScenePosition       _endPoint;
  ScenePosition       _currentPosition;
  float               _length2;
  
  float DirectionAB(const ScenePosition A, const ScenePosition B);
  float CrossProduct(const ScenePosition& A, const ScenePosition& B, const ScenePosition& C);
  float DotProductBA_BC(const ScenePosition& A, const ScenePosition& B, const ScenePosition& C);
  float DistanceFromPathToPoint(const ScenePosition A, const ScenePosition B, const ScenePosition pos);
  float SquaredDistance(ScenePosition A, ScenePosition B);
  
  public:
  RowSegment();
  RowSegment(MapPosition& first, MapPosition& second);
  ~RowSegment();

  float SetSegment(const MapPosition& first, const MapPosition& second);
  float UpdateCurrentPosition(const MapPosition& pos, float pitch);
  float UpdateOriginPosition(const MapPosition& pos, bool oppoiteDirection = false);

  float GetRowLength() { return sqrtf(_length2) / 100; }
};
