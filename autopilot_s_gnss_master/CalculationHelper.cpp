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

//////////////////////////////////////////////////////////////
////////////////////KALMAN FILTER/////////////////////////////
//////////////////////////////////////////////////////////////

Kalman::Kalman() {
    /* We will set the variables like so, these can also be tuned by the user */
    Q_angle = 0.001f;
    Q_bias = 0.003f;
    R_measure = 0.03f;

    angle = 0.0f; // Reset the angle
    bias = 0.0f; // Reset bias

    P[0][0] = 0.0f; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
    P[0][1] = 0.0f;
    P[1][0] = 0.0f;
    P[1][1] = 0.0f;
};

// The angle should be in degrees and the rate should be in degrees per second and the delta time in seconds
float Kalman::getAngle(float newAngle, float newRate, float dt) {
    // KasBot V2  -  Kalman filter module - http://www.x-firm.com/?page_id=145
    // Modified by Kristian Lauszus
    // See my blog post for more information: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it

    // Discrete Kalman filter time update equations - Time Update ("Predict")
    // Update xhat - Project the state ahead
    /* Step 1 */
    rate = newRate - bias;
    angle += dt * rate;

    // Update estimation error covariance - Project the error covariance ahead
    /* Step 2 */
    P[0][0] += dt * (dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt;

    // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
    // Calculate Kalman gain - Compute the Kalman gain
    /* Step 4 */
    float S = P[0][0] + R_measure; // Estimate error
    /* Step 5 */
    float K[2]; // Kalman gain - This is a 2x1 vector
    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    // Calculate angle and bias - Update estimate with measurement zk (newAngle)
    /* Step 3 */
    float y = newAngle - angle; // Angle difference
    /* Step 6 */
    angle += K[0] * y;
    bias += K[1] * y;

    // Calculate estimation error covariance - Update the error covariance
    /* Step 7 */
    float P00_temp = P[0][0];
    float P01_temp = P[0][1];

    P[0][0] -= K[0] * P00_temp;
    P[0][1] -= K[0] * P01_temp;
    P[1][0] -= K[1] * P00_temp;
    P[1][1] -= K[1] * P01_temp;

    return angle;
};

void Kalman::setAngle(float angle) { this->angle = angle; }; // Used to set angle, this should be set as the starting angle
float Kalman::getRate() { return this->rate; }; // Return the unbiased rate

/* These are used to tune the Kalman filter */
void Kalman::setQangle(float Q_angle) { this->Q_angle = Q_angle; };
void Kalman::setQbias(float Q_bias) { this->Q_bias = Q_bias; };
void Kalman::setRmeasure(float R_measure) { this->R_measure = R_measure; };

float Kalman::getQangle() { return this->Q_angle; };
float Kalman::getQbias() { return this->Q_bias; };
float Kalman::getRmeasure() { return this->R_measure; };

SimpleKalmanFilter::SimpleKalmanFilter(float mea_e, float est_e, float q)
{
  _err_measure=mea_e;
  _err_estimate=est_e;
  _q = q;
}

float SimpleKalmanFilter::updateEstimate(float mea)
{
  _kalman_gain = _err_estimate/(_err_estimate + _err_measure);
  _current_estimate = _last_estimate + _kalman_gain * (mea - _last_estimate);
  _err_estimate =  (1.0f - _kalman_gain)*_err_estimate + fabsf(_last_estimate-_current_estimate)*_q;
  _last_estimate=_current_estimate;

  return _current_estimate;
}

void SimpleKalmanFilter::setMeasurementError(float mea_e)
{
  _err_measure=mea_e;
}

void SimpleKalmanFilter::setEstimateError(float est_e)
{
  _err_estimate=est_e;
}

void SimpleKalmanFilter::setProcessNoise(float q)
{
  _q=q;
}

float SimpleKalmanFilter::getKalmanGain() {
  return _kalman_gain;
}

float SimpleKalmanFilter::getEstimateError() {
  return _err_estimate;
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

float CalcultionHelper::UpdateCurrentPosition(char* lat, char* lon, float pitch) {
  int lengthLat = strlen(lat);
  int lengthLon = strlen(lon);
  byte msg[lengthLat + lengthLon + sizeof(float) + 6];

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
  
  msg[index++] = ' ';

  for(int i = 0; i < sizeof(float); i++)
  {
    msg[index++] = ((uint8_t*)&pitch)[i];
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
    rawValue[i] = Wire.read();
  
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
