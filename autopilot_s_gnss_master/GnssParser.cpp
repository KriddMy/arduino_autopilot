#include "GnssParser.h"

GnssSerialParser::GnssSerialParser() {
  GNSS_SERIAL.begin(GNSS_SERIAL_SPEED);
}

GnssSerialParser::~GnssSerialParser() {
  GNSS_SERIAL.end();
}

bool GnssSerialParser::ParseGNRMC(bool withGNGST = false) {  
  bool result = true;  
  
  if(!FindMessage("$GNRMC", withGNGST)) {
    result = false;
  }

  GNSS_SERIAL.flush();
  
  return result;
}

bool GnssSerialParser::ParseGNGGA(bool withGNGST = false) {
  bool result = true; 
   
  if(!FindMessage("$GNGGA", withGNGST)) {
    result = false;
  }

  GNSS_SERIAL.flush();
  
  return result;
}

bool GnssSerialParser::ParseGNGST() {
  bool result = true;  
  
  if(!FindMessage("$GNGST")) {
    result = false;
  }

  GNSS_SERIAL.flush();
  
  return result;
}

bool GnssSerialParser::FindMessage(String key, bool withGST = false){
  bool finish = false;
  bool writeKey = false;
  bool foundMsg = false;
  bool foundGST = false;
  char keyBuffer[8];
  int i = 0;

  const unsigned int waitTime = 1000;
  unsigned int beginTime = millis();
  
  while(!finish)
  {
    if(!foundMsg)
    {
      unsigned int currentTime = millis();
      if( currentTime - beginTime > waitTime)
        return false;
    }
    else
    {
      unsigned int currentTime = millis();
      if( currentTime - beginTime > 3000)
        return false;
    }
    
    if(GNSS_SERIAL.available())
    {
      char c = GNSS_SERIAL.read();
      //Serial.print(c);
      if(c == '$')
      {
        i = 0;
        keyBuffer[i++] = c;
        writeKey = true;
        foundMsg = false;
        foundGST = false;
      }
      else if(writeKey)
      {
        keyBuffer[i++] = c;
        if(i == 6)
        {
          keyBuffer[6] = '\0';
          writeKey = false;
          i = 0;
          if(key.equals(keyBuffer))
          {
            foundMsg = true;
          }
          else if(withGST && String("$GNGST").equals(keyBuffer))
          {
            foundGST = true;
          }
        }
      }
      else if(foundMsg)
      {
        if (c != '\n' && c != '*') {
            gpsBuffer[i++] = c;
            if(i == 96) return false;
        } else {
            gpsBuffer[i] = '\0';
            if(key.equals("$GNRMC"))
            {
              if(!ReadGNRMC(gpsBuffer, connectSat, time, date, latitude, longitude, speed, heading, magneticDecl))
                return false;
            }
            else if(key.equals("$GNGGA"))
            {
              if(!ReadGNGGA(gpsBuffer, time, latitude, longitude, navStatus, hdop))
                return false;
            }
            else if(key.equals("$GNGST"))
            {
              if(!ReadGNGST(gpsBuffer, time, accuracy))
                return false;
            }
            
            finish = true;
        }
      }
      else if(foundGST)
      {
        if (c != '\n' && c != '*') {
            gpsBuffer[i++] = c;
            if(i == 96) return false;
        } else {
          gpsBuffer[i] = '\0';
          ReadGNGST(gpsBuffer, time, accuracy);
          
          foundGST = false;
          beginTime = millis();
        }
      }
    }
  }
  
  if (connectSat[0] != 'A') {
    return false;
  }
  return true;
}

bool GnssSerialParser::ReadGNRMC(char* gpsBuffer, char* connectSat, char* time, 
        char* date, char* latitude, char* longitude, char* speed, char* heading, char* magneticDecl) {
    int i = 0;
    int j = 0;
  
    if (gpsBuffer[i] == '$') {
        i++;
        while (gpsBuffer[i] != ',') {
            if(i==6) return false;
            i++;
        }
    }
    // запись времени
    if (gpsBuffer[i] == ',') {
        i++;
        j = 0;
        if(gpsBuffer[i] == ',')
          return false;
          
        while (gpsBuffer[i] != '.') {
            time[j++] = gpsBuffer[i++];
            if(j == 16) return false;
        }
        i++;
        time[j] = '\0';
        while (gpsBuffer[i] != ',') {
            i++;
            j++;
            if(j == 16) return false;
        }
    }
    // состояние GPS
    if (gpsBuffer[i] == ',') {
        i++;
        connectSat[0] = gpsBuffer[i];
        connectSat[1] = '\0';
        while (gpsBuffer[i] != ',') {
          i++;
        }
    }
  
    // запись данных широты
    if (gpsBuffer[i] == ',') {
        i++;
        j = 0;
        while (gpsBuffer[i] != ',') {
            latitude[j++] = gpsBuffer[i++];
            if(j == 16) return false;
        }
        i++;
        while (gpsBuffer[i] != ',') {
            latitude[j++] = gpsBuffer[i++];
            if(j == 16) return false;
        }
        latitude[j] = '\0';
    }
  
    // запись данных долготы
    if (gpsBuffer[i] == ',') {
        i++;
        j = 0;
        while (gpsBuffer[i] != ',') {
            longitude[j++] = gpsBuffer[i++];
            if(j == 16) return false;
        }
        i++;
        while (gpsBuffer[i] != ',') {
            longitude[j++] = gpsBuffer[i++];
            if(j == 16) return false;
        }
        longitude[j] = '\0';
    }
  
    // запись данных скорости
    if (gpsBuffer[i] == ',') {
        i++;
        j = 0;
        while (gpsBuffer[i] != ',') {
        speed[j++] = gpsBuffer[i++];
        if(j == 8) return false;
        }
        speed[j] = '\0';
    }
  
    //запись данных курса
    if (gpsBuffer[i] == ',') {
        i++;
        j = 0;
        while (gpsBuffer[i] != ',') {
            heading[j++] = gpsBuffer[i++];
            if(j == 8) return false;
        }
        heading[j] = '\0';
    }
  
    // запись даты
    if (gpsBuffer[i] == ',') {
        i++;
        j = 0;
        while (gpsBuffer[i] != ',') {
            date[j++] = gpsBuffer[i++];
            if(j == 16) return false;
        }
        date[j] = '\0'; 
    }
  
    //запись магнитного склонения
    if (gpsBuffer[i] == ',') {
        i++;
        j = 0;
        while (gpsBuffer[i] != ',') {
            magneticDecl[j++] = gpsBuffer[i++];
            if(j == 8) return false;
        }
        i++;
        while (gpsBuffer[i] != ',') {
            latitude[j++] = gpsBuffer[i++];
            if(j == 8) return false;
        }
        magneticDecl[j] = '\0'; 
    }

    return true;
}

bool GnssSerialParser::ReadGNGGA(char* gpsBuffer, char* time, char* latitude, char* longitude, char* navStatus, char* hdop) {
  int i = 0;
  int j = 0;

  if (gpsBuffer[i] == '$') {
      i++;
      while (gpsBuffer[i] != ',') {
          if(i == 6) return false;
          i++;
      }
  }
  //запись времени
  if (gpsBuffer[i] == ',') {
      i++;
      j = 0;
      if(gpsBuffer[i] == ',')
        return false;
      while (gpsBuffer[i] != '.') {
          time[j++] = gpsBuffer[i++];
          if(j == 16) return false;
      }
      i++;
      time[j] = '\0';
      while (gpsBuffer[i] != ',') {
          i++;
          j++;
          if(j == 16) return false;
      }
  }
  
  // запись данных широты
  if (gpsBuffer[i] == ',') {
      i++;
      j = 0;
      while (gpsBuffer[i] != ',') {
          latitude[j++] = gpsBuffer[i++];
          if(j == 16) return false;
      }
      i++;
      while (gpsBuffer[i] != ',') {
          latitude[j++] = gpsBuffer[i++];
          if(j == 16) return false;
      }
      latitude[j] = '\0';
  }

  // запись данных долготы
  if (gpsBuffer[i] == ',') {
      i++;
      j = 0;
      while (gpsBuffer[i] != ',') {
          longitude[j++] = gpsBuffer[i++];
          if(j == 16) return false;
      }
      i++;
      while (gpsBuffer[i] != ',') {
          longitude[j++] = gpsBuffer[i++];
          if(j == 16) return false;
      }
      longitude[j] = '\0';
  }

  // запись данных о способе получения координат
  if (gpsBuffer[i] == ',') {
      i++;
      navStatus[0] = gpsBuffer[i];
      navStatus[1] = '\0';
      i++;
      
      if(navStatus[0] <= '8' || navStatus[0] >= '1') {
        connectSat[0] = 'A';
        connectSat[1] = '\0';
      }
      else {
        connectSat[0] = 'V';
        connectSat[1] = '\0';
      }
  }

  //пропускаем данные о количестве спутников
  if (gpsBuffer[i] == ',') {
      i++;
      j = 0;
      while (gpsBuffer[i] != ',') {
          i++;
          j++;
          if(j == 4) return false;
      }
  }
  
  // запись фактора ухудшения горизонтальной точности
  if (gpsBuffer[i] == ',') {
      i++;
      j = 0;
      while (gpsBuffer[i] != ',') {
          hdop[j++] = gpsBuffer[i++];
          if(j == 5) return false;
      }
      hdop[j] = '\0';
  }

  return true;
}

bool GnssSerialParser::ReadGNGST(char* gpsBuffer, char* time, char* accuracy)
{
  int i = 0;
  int j = 0;

  if (gpsBuffer[i] == '$') {
      i++;
      while (gpsBuffer[i] != ',') {
          if(i == 6) return false;
          i++;
      }
  }
  //запись времени
  if (gpsBuffer[i] == ',') {
      i++;
      j = 0;
      while (gpsBuffer[i] != '.') {
          time[j++] = gpsBuffer[i++];
          if(j == 16) return false;
      }
      i++;
      time[j] = '\0';
      while (gpsBuffer[i] != ',') {
          i++;
          j++;
          if(j == 16) return false;
      }
  }

  // запись данных точности
  if (gpsBuffer[i] == ',') {
      i++;
      j = 0;
      while (gpsBuffer[i] != ',') {
      accuracy[j++] = gpsBuffer[i++];
      if(j == 8) return false;
      }
      accuracy[j] = '\0';
  }
  
  return true;
}

void GnssSerialParser::ClearVariables() 
{
  memset(connectSat, 0, sizeof(connectSat));
  memset(speed, 0, sizeof(speed));
  memset(altitude, 0, sizeof(altitude));
  memset(sat, 0, sizeof(sat));
  memset(time, 0, sizeof(time));
  memset(date, 0, sizeof(date));
  memset(latitude, 0, sizeof(latitude));
  memset(longitude, 0, sizeof(longitude));
  memset(heading, 0, sizeof(heading));
  memset(navStatus, 0, sizeof(navStatus));
  memset(magneticDecl, 0, sizeof(magneticDecl));
  memset(hdop, 0, sizeof(hdop));
  memset(accuracy, 0, sizeof(accuracy));
}
