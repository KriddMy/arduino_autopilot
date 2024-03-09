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
  
  static constexpr float _fromMilesToMeters = 1852.107;
  static constexpr float _fromMilesToCantimeters = _fromMilesToMeters * 100;
  
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

class Kalman {
public:
    Kalman();

    // The angle should be in degrees and the rate should be in degrees per second and the delta time in seconds
    float getAngle(float newAngle, float newRate, float dt);

    void setAngle(float angle); // Used to set angle, this should be set as the starting angle
    float getRate(); // Return the unbiased rate

    /* These are used to tune the Kalman filter */
    void setQangle(float Q_angle);
    /**
     * setQbias(float Q_bias)
     * Default value (0.003f) is in Kalman.cpp. 
     * Raise this to follow input more closely,
     * lower this to smooth result of kalman filter.
     */
    void setQbias(float Q_bias);
    void setRmeasure(float R_measure);

    float getQangle();
    float getQbias();
    float getRmeasure();

private:
    /* Kalman filter variables */
    float Q_angle; // Process noise variance for the accelerometer
    float Q_bias; // Process noise variance for the gyro bias
    float R_measure; // Measurement noise variance - this is actually the variance of the measurement noise

    float angle; // The angle calculated by the Kalman filter - part of the 2x1 state vector
    float bias; // The gyro bias calculated by the Kalman filter - part of the 2x1 state vector
    float rate; // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate

    float P[2][2]; // Error covariance matrix - This is a 2x2 matrix
};

class SimpleKalmanFilter
{

public:
  SimpleKalmanFilter(float mea_e, float est_e, float q);
  float updateEstimate(float mea);
  void setMeasurementError(float mea_e);
  void setEstimateError(float est_e);
  void setProcessNoise(float q);
  float getKalmanGain();
  float getEstimateError();

private:
  float _err_measure;
  float _err_estimate;
  float _q;
  float _current_estimate = 0;
  float _last_estimate = 0;
  float _kalman_gain = 0;

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
  float UpdateCurrentPosition(char* lat, char* lon, float pitch);
  float NewRowFromPosition(char* lat, char* lon);
  float NewRowFromPositionOpposite(char* lat, char* lon);

  float GetRowLength() { return _rowLength; }
  float GetRowDirection() { return _rowDirection; }
  float GetRowOffset() { return _currentPosOffset; }
  
};

#endif //_CALCULATION_HELPER_CLASS
