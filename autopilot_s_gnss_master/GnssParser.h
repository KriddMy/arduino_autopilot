#ifndef _GNSS_PARSER_CLASS
#define _GNSS_PARSER_CLASS

#include <Arduino.h>

// настройки соединения GNSS 
#define GNSS_SERIAL         Serial2
#define GNSS_SERIAL_SPEED   57600

class GnssSerialParser
{
  private:
  char gpsBuffer[96];
  char connectSat[4];
  char speed[8];
  char altitude[8];
  char sat[8];
  char time[16];
  char date[16];
  char latitude[16];
  char longitude[16];
  char heading[8];
  char navStatus[8];
  char magneticDecl[8];
  char hdop[5];
  char accuracy[8];
  
  bool FindMessage(String key, bool withGST = false);
  
  void ClearVariables();
  
  bool ReadGNRMC(char* gpsBuffer, char* connectSat, char* time, 
      char* date, char* latitude, char* longitude, char* speed, char* heading, char* magneticDecl);
      
  bool ReadGNGGA(char* gpsBuffer, char* time, char* latitude, char* longitude, char* navStatus, char* hdop);
  
  bool ReadGNGST(char* gpsBuffer, char* time, char* accuracy);
  
  public:
  GnssSerialParser();
  ~GnssSerialParser();

  bool ParseGNRMC(bool withGNGST = false);
  bool ParseGNGGA(bool withGNGST = false);
  bool ParseGNGST();

  char* GetLatitudeStr()  { return latitude; }
  char* GetLongitudeStr() { return longitude; }
  char* GetHDOPStr()      { return hdop; }
  char* GetStatusStr()    { return navStatus; }
  char* GetMagneticsStr() { return magneticDecl; }
  char* GetHeadingStr()   { return heading; }
  char* GetSpeedStr()     { return speed; }
  char* GetAccuracyStr()  { return accuracy; }
  
};

#endif //_GNSS_PARSER_CLASS
