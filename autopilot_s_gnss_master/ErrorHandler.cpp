#include "ErrorHandler.h"

void ErrorHandler::SetError(unsigned long errFlag)
{
  if((errorFlags & errFlag) == 0)
  {
    errorFlags |= errFlag;
    errorCount++;
  }
  
}

void ErrorHandler::UnsetError(unsigned long errFlag)
{
  if(errorFlags & errFlag)
  {
    errorFlags |= ~errFlag;
    errorCount--;
  }
  
}

void ErrorHandler::SetErrorString(char *pStr, int num)
{
  static unsigned long prevMillis = millis();
  static unsigned int nCounter = 0;

  if(errorFlags == 0)  return;

  nCounter %= errorCount;

  int errorIndex = 0;
  unsigned long errorCode = 0;
  for(int i = 0; i < sizeof(errorFlags); i++) {
    unsigned long cur = (1 << i);
    if(errorFlags & cur)
    {
      errorIndex++;
      if(errorIndex == nCounter) 
      {
        errorCode = cur; 
        break;
      }
    }
  }

  switch(errorCode)
  {
    case ERR_NOGNGGA_FLAG:
      strncpy(pStr, "ERR GPS GNGGA", num - 1);
      pStr[num] = 0;
      break;

      case ERR_NOGNRMC_FLAG:
      strncpy(pStr, "ERR GPS GNRMC", num - 1);
      pStr[num] = 0;
      break;
  }

  if(prevMillis - millis() > 3000)
  {
    prevMillis = millis();
    nCounter++;
  }
}