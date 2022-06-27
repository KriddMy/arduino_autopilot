#include "coordinates_helper.h"

////////////////////////////////////////////////////////////////////////
///////////////////////PreciseLatitude/////////////////////////////////
///////////////////////////////////////////////////////////////////////

PreciseLatitude::PreciseLatitude() {
  
}

PreciseLatitude::PreciseLatitude(short degrees, short minutes, float decimals) {
  _degrees = degrees;
  _minutes = minutes;
  _decimals = decimals;
  IsValid = true;
}

PreciseLatitude::PreciseLatitude(const PreciseLatitude& copy) {
  _degrees = copy._degrees;
  _minutes = copy._minutes;
  _decimals = copy._decimals;
  IsValid = copy.IsValid;
}

PreciseLatitude::PreciseLatitude(char* input) {
  int i = 0;
  int j = 0;
  char parsingLatitude[16];
  
  while( i != 2) {
    parsingLatitude[j++] = input[i++];
  } 
  parsingLatitude[j] = '\0';
  j = 0;
  _degrees = atoi(parsingLatitude);
  
  while(input[i] != '.') {
    parsingLatitude[j++] = input[i++];
  }
  parsingLatitude[j] = '\0';
  j = 0;
  _minutes = atoi(parsingLatitude);
  
  
  while (input[i] != '\0') {
      parsingLatitude[j++] = input[i++];
  }
  parsingLatitude[j] = '\0';
  _decimals = atof(parsingLatitude);


  if (input[strlen(input) - 1] == 'S') {
      _degrees *= -1;
      _minutes *= -1;
      _decimals *= -1;
  }
  else if(input[strlen(input) - 1] != 'N') {
    IsValid = false;
    _degrees = 0;
    _minutes = 0;
    _decimals = 0;
  }
  IsValid = true;
}

PreciseLatitude PreciseLatitude::operator+(const PreciseLatitude& other) {
  short m;
  short d;
  float dec;
  bool isNegative = false;

  if( (_degrees < -other._degrees) ||
      (_degrees == other._degrees && _minutes < -other._minutes) ||
      (_minutes == other._minutes && _decimals < -other._decimals) ) 
  {
    d = other._degrees;
    m = other._minutes;
    dec = other._decimals;

    d += _degrees;
    m += _minutes;
    dec += _decimals;
    
    isNegative = true;
  }
  else {
    m = _minutes;
    d = _degrees;
    dec = _decimals;

    d += other._degrees;
    m += other._minutes;
    dec += other._decimals;
  }
  
  if(dec >= 1.0) {
    dec -= 1.0;
    m++;
  }
  else if(dec < 0.0) {
    dec += 1.0;
    m--;
  }
  
  if(m >= 60) {
    m -=60;
    d++;
  }
  else if(m < 0) {
    m += 60;
    d--;
  }

  if(isNegative) {
    d *= -1;
    m *= -1;
    dec *= -1;
  }
 
  return PreciseLatitude(d, m, dec);
}

PreciseLatitude PreciseLatitude::operator-(const PreciseLatitude& other) {
  short m;
  short d;
  float dec;
  bool isNegative = false;

  if( (_degrees < other._degrees) ||
      (_degrees == other._degrees && _minutes < other._minutes) ||
      (_minutes == other._minutes && _decimals < other._decimals) ) 
  {
    m = other._minutes;
    d = other._degrees;
    dec = other._decimals;

    d -= _degrees;
    m -= _minutes;
    dec -= _decimals;
    
    isNegative = true;
  }
  else {
    m = _minutes;
    d = _degrees;
    dec = _decimals;

    d -= other._degrees;
    m -= other._minutes;
    dec -= other._decimals;
  }
  
  if(dec >= 1.0) {
    dec -= 1.0;
    m++;
  }
  else if(dec < 0.0) {
    dec += 1.0;
    m--;
  }
  
  if(m >= 60) {
    m -=60;
    d++;
  }
  else if(m < 0) {
    m += 60;
    d--;
  }

  if(isNegative) {
    d *= -1;
    m *= -1;
    dec *= -1;
  }
 
  return PreciseLatitude(d, m, dec);
}

PreciseLatitude& PreciseLatitude::operator+=( const PreciseLatitude& rhs) {
  short m;
  short d;
  float dec;
  bool isNegative = false;

  if( (_degrees < -rhs._degrees) ||
      (_degrees == rhs._degrees && _minutes < -rhs._minutes) ||
      (_minutes == rhs._minutes && _decimals < -rhs._decimals) ) 
  {
    m = rhs._minutes;
    d = rhs._degrees;
    dec = rhs._decimals;

    d -= _degrees;
    m -= _minutes;
    dec -= _decimals;
    
    isNegative = true;
  }
  else {
    m = _minutes;
    d = _degrees;
    dec = _decimals;

    d += rhs._degrees;
    m += rhs._minutes;
    dec += rhs._decimals;
  }
  
  if(dec >= 1.0) {
    dec -= 1.0;
    m++;
  }
  else if(dec < 0.0) {
    dec += 1.0;
    m--;
  }
  
  if(m >= 60) {
    m -=60;
    d++;
  } 
  else if(m < 0) {
    m += 60;
    d--;
  }

  if(isNegative) {
    d *= -1;
    m *= -1;
    dec *= -1;
  }

  _degrees = d;
  _minutes = m;
  _decimals = dec;

  return *this;
}

PreciseLatitude& PreciseLatitude::operator-=(const PreciseLatitude& rhs) {
  short m;
  short d;
  float dec;
  bool isNegative = false;

  if( (_degrees < rhs._degrees) ||
      (_degrees == rhs._degrees && _minutes < rhs._minutes) ||
      (_minutes == rhs._minutes && _decimals < rhs._decimals) ) 
  {
    m = rhs._minutes;
    d = rhs._degrees;
    dec = rhs._decimals;

    d -= _degrees;
    m -= _minutes;
    dec -= _decimals;
    
    isNegative = true;
  }
  else {
    m = _minutes;
    d = _degrees;
    dec = _decimals;

    d -= rhs._degrees;
    m -= rhs._minutes;
    dec -= rhs._decimals;
  }
  
  if(dec >= 1.0) {
    dec -= 1.0;
    m++;
  }
  else if(dec < 0.0) {
    dec += 1.0;
    m--;
  }
  
  if(m >= 60) {
    m -=60;
    d++;
  }
  else if(m < 0) {
    m += 60;
    d--;
  }

  if(isNegative) {
    d *= -1;
    m *= -1;
    dec *= -1;
  }

  _degrees = d;
  _minutes = m;
  _decimals = dec;
  
  return *this;
}

PreciseLatitude& PreciseLatitude::operator=(const PreciseLatitude& copy) {
  _degrees = copy._degrees;
  _minutes = copy._minutes;
  _decimals = copy._decimals;
  IsValid = copy.IsValid;
}

void PreciseLatitude::print() {
  Serial.print("degrees: ");
  Serial.println(_degrees);
  Serial.print("minutes: ");
  Serial.println(_minutes);
  Serial.print("decimals: ");
  Serial.println(_decimals, 7);
}

///////////////////////////////////////////////////////////////////////////////
////////////////////PreciseLongitude//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

PreciseLongitude::PreciseLongitude() {
  
}

PreciseLongitude::PreciseLongitude(short degrees, short minutes, float decimals) {
  _degrees = degrees;
  _minutes = minutes;
  _decimals = decimals;
  IsValid = true;
}

PreciseLongitude::PreciseLongitude(const PreciseLongitude& copy) {
  _degrees = copy._degrees;
  _minutes = copy._minutes;
  _decimals = copy._decimals;
  IsValid = copy.IsValid;
}

PreciseLongitude::PreciseLongitude(char* input) {
  int i = 0;
  int j = 0;
  char parsingLongitude[16];
  
  while( i != 3) {
    parsingLongitude[j++] = input[i++];
  }
  parsingLongitude[j] = '\0';
  j = 0;
  _degrees = atoi(parsingLongitude);
  
  while(input[i] != '.') {
    parsingLongitude[j++] = input[i++];
  }
  parsingLongitude[j] = '\0';
  j = 0;
  _minutes = atoi(parsingLongitude);
  
  
  while (input[i] != '\0') {
      parsingLongitude[j++] = input[i++];
  }
  parsingLongitude[j] = '\0';
  _decimals = atof(parsingLongitude);


  if (input[strlen(input) - 1] == 'E') {
      _degrees *= -1;
      _minutes *= -1;
      _decimals *= -1;
  }
  else if(input[strlen(input) - 1] != 'W') {
    IsValid = false;
    _degrees = 0;
    _minutes = 0;
    _decimals = 0;
  }
  IsValid = true;
}

PreciseLongitude PreciseLongitude::operator+(const PreciseLongitude& other) {
  short m;
  short d;
  float dec;
  bool isNegative = false;

  if( (_degrees < -other._degrees) ||
      (_degrees == other._degrees && _minutes < -other._minutes) ||
      (_minutes == other._minutes && _decimals < -other._decimals) ) 
  {
    m = other._minutes;
    d = other._degrees;
    dec = other._decimals;

    d += _degrees;
    m += _minutes;
    dec += _decimals;
    
    isNegative = true;
  }
  else {
    m = _minutes;
    d = _degrees;
    dec = _decimals;

    d += other._degrees;
    m += other._minutes;
    dec += other._decimals;
  }
  
  if(dec >= 1.0) {
    dec -= 1.0;
    m++;
  }
  else if(dec < 0.0) {
    dec += 1.0;
    m--;
  }
  
  if(m >= 60) {
    m -=60;
    d++;
  }
  else if(m < 0) {
    m += 60;
    d--;
  }

  if(isNegative) {
    d *= -1;
    m *= -1;
    dec *= -1;
  }
 
  return PreciseLongitude(d, m, dec);
}

PreciseLongitude PreciseLongitude::operator-(const PreciseLongitude& other) {
  short m;
  short d;
  float dec;
  bool isNegative = false;

  if( (_degrees < other._degrees) ||
      (_degrees == other._degrees && _minutes < other._minutes) ||
      (_minutes == other._minutes && _decimals < other._decimals) ) 
  {
    m = other._minutes;
    d = other._degrees;
    dec = other._decimals;

    d -= _degrees;
    m -= _minutes;
    dec -= _decimals;
    
    isNegative = true;
  }
  else {
    m = _minutes;
    d = _degrees;
    dec = _decimals;

    d -= other._degrees;
    m -= other._minutes;
    dec -= other._decimals;
  }
  
  if(dec >= 1.0) {
    dec -= 1.0;
    m++;
  }
  else if(dec < 0.0) {
    dec += 1.0;
    m--;
  }
  
  if(m >= 60) {
    m -=60;
    d++;
  }
  else if(m < 0) {
    m += 60;
    d--;
  }

  if(isNegative) {
    d *= -1;
    m *= -1;
    dec *= -1;
  }
 
  return PreciseLongitude(d, m, dec);
}

PreciseLongitude& PreciseLongitude::operator+=( const PreciseLongitude& rhs) {
  short m;
  short d;
  float dec;
  bool isNegative = false;

  if( (_degrees < -rhs._degrees) ||
      (_degrees == rhs._degrees && _minutes < -rhs._minutes) ||
      (_minutes == rhs._minutes && _decimals < -rhs._decimals) ) 
  {
    m = rhs._minutes;
    d = rhs._degrees;
    dec = rhs._decimals;

    d -= _degrees;
    m -= _minutes;
    dec -= _decimals;
    
    isNegative = true;
  }
  else {
    m = _minutes;
    d = _degrees;
    dec = _decimals;

    d += rhs._degrees;
    m += rhs._minutes;
    dec += rhs._decimals;
  }
  
  if(dec >= 1.0) {
    dec -= 1.0;
    m++;
  }
  else if(dec < 0.0) {
    dec += 1.0;
    m--;
  }
  
  if(m >= 60) {
    m -=60;
    d++;
  }
  else if(m < 0) {
    m += 60;
    d--;
  }

  if(isNegative) {
    d *= -1;
    m *= -1;
    dec *= -1;
  }

  _degrees = d;
  _minutes = m;
  _decimals = dec;

  return *this;
}

PreciseLongitude& PreciseLongitude::operator-=(const PreciseLongitude& rhs) {
  short m;
  short d;
  float dec;
  bool isNegative = false;

  if( (_degrees < rhs._degrees) ||
      (_degrees == rhs._degrees && _minutes < rhs._minutes) ||
      (_minutes == rhs._minutes && _decimals < rhs._decimals) ) 
  {
    m = rhs._minutes;
    d = rhs._degrees;
    dec = rhs._decimals;

    d -= _degrees;
    m -= _minutes;
    dec -= _decimals;
    
    isNegative = true;
  }
  else {
    m = _minutes;
    d = _degrees;
    dec = _decimals;

    d -= rhs._degrees;
    m -= rhs._minutes;
    dec -= rhs._decimals;
  }
  
  if(dec >= 1.0) {
    dec -= 1.0;
    m++;
  }
  else if(dec < 0.0) {
    dec += 1.0;
    m--;
  }
  
  if(m >= 60) {
    m -=60;
    d++;
  }
  else if(m < 0) {
    m += 60;
    d--;
  }

  if(isNegative) {
    d *= -1;
    m *= -1;
    dec *= -1;
  }

  _degrees = d;
  _minutes = m;
  _decimals = dec;

  return *this;
}

PreciseLongitude& PreciseLongitude::operator=(const PreciseLongitude& copy) {
  _degrees = copy._degrees;
  _minutes = copy._minutes;
  _decimals = copy._decimals;
  IsValid = copy.IsValid;
}

void PreciseLongitude::print() {
  Serial.print("degrees: ");
  Serial.println(_degrees);
  Serial.print("minutes: ");
  Serial.println(_minutes);
  Serial.print("decimals: ");
  Serial.println(_decimals, 7);
}

////////////////////////////////////////////////////
/////////////////MapPosition///////////////////////
///////////////////////////////////////////////////

MapPosition::MapPosition() {
}

MapPosition::MapPosition(const MapPosition& copy) {
  _latitude = PreciseLatitude(copy._latitude);
  _longitude = PreciseLongitude(copy._longitude);
}

MapPosition::MapPosition(PreciseLatitude& lat, PreciseLongitude& lon) {
  _latitude = PreciseLatitude(lat);
  _longitude = PreciseLongitude(lon);
}

MapPosition::MapPosition(char* lat, char* lon) {
  _latitude = PreciseLatitude(lat);
  _longitude = PreciseLongitude(lon);
}

MapPosition::~MapPosition() {
}

MapPosition MapPosition::operator+(const MapPosition& other) {
  PreciseLatitude lat(_latitude + other._latitude);
  PreciseLongitude lon(_longitude + other._longitude);
  return MapPosition(lat, lon);
}

MapPosition MapPosition::operator-(const MapPosition& other) {
  PreciseLatitude lat(_latitude - other._latitude);
  PreciseLongitude lon(_longitude - other._longitude);
  return MapPosition(lat, lon);
}

MapPosition& MapPosition::operator+=(const MapPosition& rhs) { 
  _latitude += rhs._latitude;
  _longitude += rhs._longitude;
  
  return *this;
}

MapPosition& MapPosition::operator-=(const MapPosition& rhs) {
  _latitude -= rhs._latitude;
  _longitude -= rhs._longitude;
  
  return *this;
}

MapPosition& MapPosition::operator=(const MapPosition& copy) {
  _latitude = PreciseLatitude(copy._latitude);
  _longitude = PreciseLongitude(copy._longitude);
}

void MapPosition::print() {
  Serial.println("Latitude: ");
  _latitude.print();

  Serial.println("Longitude: ");
  _longitude.print();
  Serial.println();
}

float MapPosition::DistanceInMeters(MapPosition& pos) {
  float result;
  const double lonCoeff = cos(radians(_latitude.Degrees() + _latitude.Minutes() / 60));

  MapPosition differance = *this - pos;
  
  float dLat = differance._latitude.Degrees() * 60 + differance._latitude.Minutes() + differance._latitude.Decimals();
  float dLon = differance._longitude.Degrees() * 60 + differance._longitude.Minutes() + differance._longitude.Decimals();
  
  dLat *= _fromMilesToMeters;
  dLon = dLon * _fromMilesToMeters * lonCoeff;

  result = dLat * dLat + dLon * dLon;
  result = sqrt(result);
  
  return result;
}

float MapPosition::GetCoorinateX() {
  float dLat = this->_latitude.Degrees() * 60 + this->_latitude.Minutes() + this->_latitude.Decimals();
  dLat *= _fromMilesToCantimeters;

  return dLat;
}

float MapPosition::GetCoorinateY() {
  const double coeff = cos(radians(_latitude.Degrees() + _longitude.Minutes() / 60));
  
  float dLon = this->_longitude.Degrees() * 60 + this->_longitude.Minutes() + this->_longitude.Decimals();
  dLon = dLon * _fromMilesToCantimeters * coeff;

  return dLon;
}

///////////////////////////////////////////////////////////////
///////////////////RowSegment//////////////////////////////////
//////////////////////////////////////////////////////////////

RowSegment::RowSegment() {
  _endPoint = { 0, 0 };
}

RowSegment::RowSegment(MapPosition& first, MapPosition& second) {
  SetSegment(first, second);
}

RowSegment::~RowSegment() {
}

float RowSegment::SetSegment(const MapPosition& first, const MapPosition& second) {
  _origin = MapPosition(first);
  _isOriginSet = true;

  MapPosition temp = second - first;
  
  _endPoint.X = temp.GetCoorinateX();
  _endPoint.Y = temp.GetCoorinateY();

  _length2 = SquaredDistance(_zeroPosition, _endPoint);

  return DirectionAB(_zeroPosition, _endPoint);
}

float RowSegment::UpdateCurrentPosition(const MapPosition& pos, float pitch) {
  if(!_isOriginSet) return 0;

  MapPosition temp = pos - _origin;

  _currentPosition.X = temp.GetCoorinateX();
  _currentPosition.Y = temp.GetCoorinateY();

  float corr = cos(radians(pitch)) * ANTENNA_HIGHT;

  return DistanceFromPathToPoint(_zeroPosition, _endPoint, _currentPosition) + corr; 
}

float RowSegment::UpdateOriginPosition(const MapPosition& pos, bool oppoiteDirection = false)
{
  if(!_isOriginSet) return 0;
  _origin = MapPosition(pos);

  if(oppoiteDirection)
  {
    _endPoint.X *= -1;
    _endPoint.Y *= -1;
  }

  return DirectionAB(_zeroPosition, _endPoint);
  
}

float RowSegment::DirectionAB(const ScenePosition A, ScenePosition B) {  
  float brng = atan2(A.Y - B.Y, B.X - A.X);
  brng = degrees(brng);// radians to degrees

  if(brng < 0)
    brng += 360;
  else if(brng >= 360)
    brng -= 360;

  return brng;
}

float RowSegment::DistanceFromPathToPoint(const ScenePosition A, const ScenePosition B, const ScenePosition pos)
{
  float result;

  float dot1 = DotProductBA_BC(A, B, pos);
  float dot2 = DotProductBA_BC(B, A, pos);
  
  if (dot1 < 0)
  {
      result = SquaredDistance(B, pos);
  }
  else if (dot2 < 0)
  {
      result = SquaredDistance(A, pos);
  }
  else
  {
      float segmentVec2d[2];

      float t;
      if(_length2 <= 10) {
        t = 0;
      }
      else {
        t = dot2 / _length2;
      }

      segmentVec2d[0] = B.X - A.X;
      segmentVec2d[1] = B.Y - A.Y;

      ScenePosition closestPoint;
      closestPoint.X = A.X + (t * segmentVec2d[0]);
      closestPoint.Y = A.Y + (t * segmentVec2d[1]);

      result = SquaredDistance(closestPoint, pos);
  }
  result = sqrtf(result);

  if(CrossProduct(A, B, pos) > 0) {
    result *= -1;
  }
  
  return result / 100;
}

float RowSegment::DotProductBA_BC(const ScenePosition& A, const ScenePosition& B, const ScenePosition& C)
{
  float BA[2];
  float BC[2];
  
  BA[0] = A.X - B.X;
  BA[1] = A.Y - B.Y;
  BC[0] = C.X - B.X;
  BC[1] = C.Y - B.Y;

  float mul1 = BA[0] * BC[0];
  float mul2 = BA[1] * BC[1];
  
  float dot = mul1 + mul2;

  return dot;
}

float RowSegment::SquaredDistance(const ScenePosition A, const ScenePosition B)
{ 
  float d1 = A.X - B.X;
  float d2 = A.Y - B.Y;

  float mul1 = d1 * d1;
  float mul2 = d2 * d2;

  float result = mul1 + mul2;
  
  return result;
}

float RowSegment::CrossProduct(const ScenePosition& A, const ScenePosition& B, const ScenePosition& C)
{
    float AB[2];
    float AC[2];
    AB[0] = (B.X - A.X);
    AB[1] = (B.Y - A.Y);
    AC[0] = (C.X - A.X);
    AC[1] = (C.Y - A.Y);

    float mul1 = AB[0] * AC[1];
    float mul2 = AB[1] * AC[0];
    
    float cross = mul1 - mul2;

    return cross;
}
