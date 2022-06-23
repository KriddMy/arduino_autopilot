#ifndef _AUTOPILOT_XY_CLASS
#define _AUTOPILOT_XY_CLASS

#include "GnssParser.h"
#include "WheelStepperMotor.h"
#include "CalculationHelper.h"

//звук нажатия кнопок
#define BUZZER_ID 2019

//кнопки управления
#define PIN_CALIBRATION_LEFT  5
#define PIN_CALIBRATION_RIGHT 4
#define PIN_ON_OFF            8
#define PIN_SET_COURSE        9
#define PIN_REVERS            10
#define PIN_MANUAL_MODE       3

//начальные значения
#define INITIAL_TURN_SPEED_SECONDS  5
#define INITIAL_RESISTOR_CENTER     290
#define NA_STRING                   "N/A"
#define NOT_SET_STRING              "не задана"

//константы поведения руля
//задаются в градусах
#define DEAD_ZONE           0   //зона когда руль не реагирует на отклонения
#define SMALL_TURN_ZONE     1   //если разница меньше этого значения - небольшой поворот
#define MEDIUM_TURN_ZONE    2   //если разница меньше этого значения - средний поворот
#define BIG_TURN_ZONE       5   //если разница меньше этого значения - большой поворот

#define SMALL_TURN_AMOUNT   90    //угол поворота руля на небольшой поворот
#define MEDIUM_TURN_AMOUNT  150   //угол поворота рулая на средний поворот
#define BIG_TURN_AMOUNT     200   //угол поворота руля на большой поворот
#define MAX_TURN_AMOUNT     250   //максимальный угол поворота руля

// настройки соединения RemoteXY
#define REMOTEXY_SERIAL         Serial1
#define REMOTEXY_SERIAL_SPEED   19200

// определение режима соединения и подключение библиотеки RemoteXY 
#define REMOTEXY_MODE__HARDSERIAL

class AutopilotXY {
  private:
  bool _isFirstPositionRecived   = false;
  bool _isPositionRecived        = false;
  bool _needPositionPostprosses  = false;

  int _courseCorrection = 0; //поправка курса из интерфейса
  int _reversCoeff      = 1; //поправка на обратный ход

  unsigned int _soundStartTime = 0;

  MapPosition   _currentPosition;
  bool          _isPointASet = false;
  bool          _isPointBSet = false;
  MapPosition   _pointA;
  MapPosition   _pointB;
  
  CalcultionHelper   _calculationHelper;
  GnssSerialParser  _gnssParser;
  WheelStepperMotor _wheelHandler;

  void ProcessUIButtons();
  void ProcessUICourseCorrection();
  void ProcessPhysicalButtons();

  void SetCourseFromCoorinates();
  
  void SetWheelAngle(int);

  void UpdateRmcInformation();
  void UpdateGgaInformation();

  void SoundStart();
  void SoundUpdate();

  public:
  AutopilotXY();
  ~AutopilotXY();

  void Init();

  bool UpdatePosition();
  void UpdateUI();
  void PositionPostprosses();
};

#endif //_AUTOPILOT_XY_CLASS
