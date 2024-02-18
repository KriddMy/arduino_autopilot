#ifndef _ERROR_HANDLER_CLASS
#define _ERROR_HANDLER_CLASS

#define ERR_NOGNGGA_FLAG (1 << 1)
#define ERR_NOGNRMC_FLAG (1 << 2)
#define ERR_NOWHEEL_CONNECTION (1 << 3)
#define ERR_NOCALC_CONNECTION (1 << 4)

#include "Arduino.h"
#include <string.h>

class ErrorHandler
{
  private:
  unsigned long errorFlags = 0;
  unsigned int errorCount = 0;

  public:
  void SetError(unsigned long errFlag);
  void UnsetError(unsigned long errFlag);

  void SetErrorString(char* pStr, int num);
};

#endif //_ERROR_HANDLER_CLASS