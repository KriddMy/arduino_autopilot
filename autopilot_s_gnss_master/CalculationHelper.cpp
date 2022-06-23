#include "CalculationHelper.h"


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

CalcultionHelper::CalcultionHelper() {
}

CalcultionHelper::~CalcultionHelper() {
}

float CalcultionHelper::SetSegmentA(char* lat, char* lon) {
  int lengthLat = strlen(lat);
  int lengthLon = strlen(lon);
  byte msg[lengthLat + lengthLon + 5];

  int index = 0;
  
  msg[index++] = 'S';
  msg[index++] = 'E';
  msg[index++] = 'A';

  //msg[index++] = ' ';
  
  for(int i = 0; i < lengthLat; i++)
  {
    msg[index++] = lat[i];
  }

  msg[index++] = ' ';
  
  for(int i = 0; i < lengthLon; i++)
  {
    msg[index++] = lon[i];
  }

  msg[index++] = '\0';
  
  Wire.beginTransmission(CALC_ADRESS);
  Wire.write(msg, sizeof(msg));
  Wire.endTransmission();
}

float CalcultionHelper::SetSegmentB(char* lat, char* lon) {
  int lengthLat = strlen(lat);
  int lengthLon = strlen(lon);
  byte msg[lengthLat + lengthLon + 5];

  int index = 0;
  
  msg[index++] = 'S';
  msg[index++] = 'E';
  msg[index++] = 'B';

  //msg[index++] = ' ';
  
  for(int i = 0; i < lengthLat; i++)
  {
    msg[index++] = lat[i];
  }

  msg[index++] = ' ';
  
  for(int i = 0; i < lengthLon; i++)
  {
    msg[index++] = lon[i];
  }

  msg[index++] = '\0';
  
  Wire.beginTransmission(CALC_ADRESS);
  Wire.write(msg, sizeof(msg));
  Wire.endTransmission();
}

void CalcultionHelper::UnsetSegmentA()
{
  byte msg[5];

  int index = 0;
  
  msg[index++] = 'U';
  msg[index++] = 'S';
  msg[index++] = 'A';
  msg[index++] = ' ';
  msg[index++] = '\0';

  Wire.beginTransmission(CALC_ADRESS);
  Wire.write(msg, sizeof(msg));
  Wire.endTransmission();
}

void CalcultionHelper::UnsetSegmentB()
{
  byte msg[5];

  int index = 0;
  
  msg[index++] = 'U';
  msg[index++] = 'S';
  msg[index++] = 'B';
  msg[index++] = ' ';
  msg[index++] = '\0';

  Wire.beginTransmission(CALC_ADRESS);
  Wire.write(msg, sizeof(msg));
  Wire.endTransmission();
}

float CalcultionHelper::UpdateCurrentPosition(char* lat, char* lon) {
  int lengthLat = strlen(lat);
  int lengthLon = strlen(lon);
  byte msg[lengthLat + lengthLon + 5];

  int index = 0;
  
  msg[index++] = 'U';
  msg[index++] = 'P';
  msg[index++] = 'O';
  
  for(int i = 0; i < lengthLat; i++)
  {
    msg[index++] = lat[i];
  }

  msg[index++] = ' ';
  
  for(int i = 0; i < lengthLon; i++)
  {
    msg[index++] = lon[i];
  }

  msg[index++] = '\0';
  
  Wire.beginTransmission(CALC_ADRESS);
  Wire.write(msg, sizeof(msg));
  Wire.endTransmission();

  return ReciveCalculatedValues();
}

float CalcultionHelper::NewRowFromPosition(char* lat, char* lon)
{
  int lengthLat = strlen(lat);
  int lengthLon = strlen(lon);
  byte msg[lengthLat + lengthLon + 5];

  int index = 0;
  
  msg[index++] = 'N';
  msg[index++] = 'P';
  msg[index++] = 'N';
  
  for(int i = 0; i < lengthLat; i++)
  {
    msg[index++] = lat[i];
  }

  msg[index++] = ' ';
  
  for(int i = 0; i < lengthLon; i++)
  {
    msg[index++] = lon[i];
  }

  msg[index++] = '\0';
  
  Wire.beginTransmission(CALC_ADRESS);
  Wire.write(msg, sizeof(msg));
  Wire.endTransmission();

  return ReciveCalculatedValues();
}

float CalcultionHelper::NewRowFromPositionOpposite(char* lat, char* lon)
{
  int lengthLat = strlen(lat);
  int lengthLon = strlen(lon);
  byte msg[lengthLat + lengthLon + 5];

  int index = 0;
  
  msg[index++] = 'N';
  msg[index++] = 'P';
  msg[index++] = 'O';
  
  for(int i = 0; i < lengthLat; i++)
  {
    msg[index++] = lat[i];
  }

  msg[index++] = ' ';
  
  for(int i = 0; i < lengthLon; i++)
  {
    msg[index++] = lon[i];
  }

  msg[index++] = '\0';
  
  Wire.beginTransmission(CALC_ADRESS);
  Wire.write(msg, sizeof(msg));
  Wire.endTransmission();

  return ReciveCalculatedValues();
}

float CalcultionHelper::ReciveCalculatedValues()
{
  byte rawValue[12];
  Wire.requestFrom(CALC_ADRESS, 12);

  for(int i = 0; i < 12; i++)
  {
    rawValue[i] = Wire.read();
  }
  
  float offset, direction, length;

  ((uint8_t*)&offset)[0] = rawValue[0];
  ((uint8_t*)&offset)[1] = rawValue[1];
  ((uint8_t*)&offset)[2] = rawValue[2];
  ((uint8_t*)&offset)[3] = rawValue[3];

  ((uint8_t*)&direction)[0] = rawValue[4];
  ((uint8_t*)&direction)[1] = rawValue[5];
  ((uint8_t*)&direction)[2] = rawValue[6];
  ((uint8_t*)&direction)[3] = rawValue[7];

  ((uint8_t*)&length)[0] = rawValue[8];
  ((uint8_t*)&length)[1] = rawValue[9];
  ((uint8_t*)&length)[2] = rawValue[10];
  ((uint8_t*)&length)[3] = rawValue[11];
  
  _currentPosOffset = offset;
  _rowDirection = direction;
  _rowLength = length;
  
  return offset;
}
