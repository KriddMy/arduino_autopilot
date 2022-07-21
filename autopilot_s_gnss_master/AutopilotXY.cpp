#include "AutopilotXY.h"

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

#include <RemoteXY.h>

// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 1213 bytes
  { 255,25,0,227,0,182,4,16,162,4,2,1,80,1,17,7,0,2,26,31,
  31,79,78,0,79,70,70,0,2,0,39,10,27,5,1,2,26,31,31,208,
  160,208,181,208,178,208,181,209,128,209,129,0,79,70,70,0,129,0,13,12,
  13,4,1,17,208,146,208,187,208,181,208,178,208,190,0,129,0,73,13,15,
  4,1,17,208,146,208,191,209,128,208,176,208,178,208,190,0,8,0,48,17,
  14,14,1,24,1,0,83,22,11,11,1,135,31,43,0,1,0,70,22,11,
  11,1,36,31,45,0,7,20,45,32,20,5,1,2,26,2,7,20,45,44,
  20,5,1,2,26,2,7,20,45,50,20,5,1,2,26,2,2,0,45,56,
  20,6,1,2,26,31,31,79,78,0,79,70,70,0,1,2,69,39,28,11,
  1,2,31,208,151,208,176,208,180,208,176,209,130,209,140,32,208,186,209,131,
  209,128,209,129,0,1,2,69,51,28,11,1,6,31,208,166,208,181,208,189,
  209,130,209,128,32,209,128,209,131,208,187,209,143,32,0,129,0,4,33,30,
  4,1,17,208,154,209,131,209,128,209,129,32,208,183,208,176,208,180,208,176,
  208,189,208,189,209,139,208,185,0,129,0,4,39,35,4,1,17,208,159,208,
  190,208,187,208,190,208,182,208,181,208,189,208,184,208,181,32,208,186,208,190,
  208,187,208,181,209,129,0,129,0,4,45,23,4,1,17,208,166,208,181,208,
  189,209,130,209,128,32,209,128,209,131,208,187,209,143,0,129,0,4,51,30,
  4,1,17,208,161,208,186,208,190,209,128,208,190,209,129,209,130,209,140,32,
  209,128,209,131,208,187,209,143,0,129,0,4,58,39,4,1,17,208,160,209,
  131,209,135,208,189,208,190,208,181,32,208,163,208,191,209,128,208,176,208,178,
  208,187,208,181,208,189,208,184,208,181,0,67,4,3,10,9,6,1,2,26,
  8,67,4,45,38,20,5,1,2,26,8,67,4,89,11,9,6,1,2,26,
  8,69,1,48,0,10,10,0,131,0,28,1,23,7,1,2,31,208,154,208,
  190,208,188,208,191,208,176,209,129,0,131,0,55,1,23,7,2,2,31,208,
  157,208,176,209,129,209,130,209,128,208,190,208,185,208,186,208,184,0,129,0,
  2,16,35,5,2,17,208,159,208,181,209,128,208,178,208,176,209,143,32,209,
  130,208,190,209,135,208,186,208,176,58,0,131,1,3,1,22,7,3,2,31,
  71,78,83,83,0,129,0,1,33,34,5,2,17,208,146,209,130,208,190,209,
  128,208,176,209,143,32,209,130,208,190,209,135,208,186,208,176,58,0,67,4,
  37,30,42,6,2,2,26,16,1,1,80,11,19,6,2,135,31,208,151,208,
  176,208,180,208,176,209,130,209,140,0,1,1,80,29,19,6,2,135,31,208,
  151,208,176,208,180,208,176,209,130,209,140,0,129,0,4,23,37,4,1,17,
  208,154,209,131,209,128,209,129,32,209,132,208,176,208,186,209,130,208,184,209,
  135,208,181,209,129,208,186,208,184,208,185,0,67,4,50,10,45,5,3,2,
  26,16,67,4,50,16,45,5,3,2,26,16,129,0,5,13,46,5,3,17,
  208,162,208,181,208,186,209,131,209,137,208,176,209,143,32,208,191,208,190,208,
  183,208,184,209,134,208,184,209,143,58,32,0,67,4,18,22,41,5,3,2,
  26,16,129,0,3,23,14,4,3,17,208,161,209,130,208,176,209,130,209,131,
  209,129,58,0,129,0,64,23,13,4,3,17,72,68,79,80,58,0,67,4,
  78,22,19,5,3,2,26,8,129,0,2,51,46,5,2,17,208,157,208,176,
  208,191,209,128,208,176,208,178,208,187,208,181,208,189,208,184,208,181,58,0,
  67,4,37,50,14,5,2,2,26,8,129,0,82,48,6,6,3,17,208,188,
  46,0,10,53,5,55,48,7,3,37,135,31,208,158,209,129,209,130,208,176,
  208,189,208,190,208,178,208,184,209,130,209,140,0,31,208,161,209,130,208,176,
  209,128,209,130,0,67,4,5,47,55,6,3,17,162,33,129,0,2,30,25,
  5,3,17,208,161,208,186,208,190,209,128,208,190,209,129,209,130,209,140,58,
  0,67,4,27,30,20,5,3,2,26,8,129,0,47,30,10,5,3,17,208,
  186,208,188,47,209,135,0,67,4,37,12,42,6,2,2,26,16,67,4,37,
  19,42,6,2,2,26,16,67,4,37,37,42,6,2,2,26,16,129,0,64,
  30,13,5,3,17,208,154,209,131,209,128,209,129,58,0,67,4,78,30,19,
  5,3,2,26,8,129,0,52,50,29,5,2,17,208,160,208,176,209,129,209,
  129,209,130,208,190,209,143,208,189,208,184,208,181,58,0,67,4,83,49,14,
  5,2,2,26,8,129,0,2,39,25,5,3,17,208,162,208,190,209,135,208,
  189,208,190,209,129,209,130,209,140,58,0,67,4,27,39,20,5,3,2,26,
  8,129,0,48,38,6,6,3,17,208,188,46,0,7,52,78,38,19,5,3,
  2,26,2,129,0,59,39,19,4,3,17,208,156,208,176,208,179,46,32,209,
  129,208,186,208,187,46,58,0,1,1,58,55,33,7,3,204,31,208,157,208,
  190,208,178,209,139,208,185,32,209,128,209,143,208,180,0,1,1,80,19,19,
  6,2,37,31,208,163,208,180,208,176,208,187,208,184,209,130,209,140,0,1,
  1,80,36,19,6,2,37,31,208,163,208,180,208,176,208,187,208,184,209,130,
  209,140,0,67,4,60,48,20,5,3,2,26,8 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  uint8_t top_switch; // =1 если переключатель включен и =0 если отключен 
  uint8_t revers_switch; // =1 если переключатель включен и =0 если отключен 
  float compass_course; // oт 0 до 359.999 
  uint8_t course_inc; // =1 если кнопка нажата, иначе =0 
  uint8_t course_dec; // =1 если кнопка нажата, иначе =0 
  int16_t course_to_go;  // 32767.. +32767 
  int16_t resistor_center;  // 32767.. +32767 
  int16_t agress;  // 32767.. +32767 
  uint8_t manual_switch; // =1 если переключатель включен и =0 если отключен 
  uint8_t calibrate; // =1 если кнопка нажата, иначе =0 
  uint8_t center; // =1 если кнопка нажата, иначе =0 
  uint8_t set_first_point; // =1 если кнопка нажата, иначе =0 
  uint8_t set_second_point; // =1 если кнопка нажата, иначе =0 
  uint8_t start_gnnss_pushSwitch; // =1 если включено, иначе =0 
  int16_t declonation;  // 32767.. +32767 
  uint8_t set_new_row; // =1 если кнопка нажата, иначе =0 
  uint8_t del_first_point; // =1 если кнопка нажата, иначе =0 
  uint8_t del_second_point; // =1 если кнопка нажата, иначе =0 

    // output variables
  char sLeftCourseCorrection[8];  // =строка UTF8 оканчивающаяся нулем 
  char sWheelPosition[8];  // =строка UTF8 оканчивающаяся нулем 
  char sRightCourseCorrection[8];  // =строка UTF8 оканчивающаяся нулем 
  int16_t buzzer; // =0 нет звука, иначе ID звука, для примера 1001, смотри список звуков в приложении 
  char sSecondPointLat[16];  // =строка UTF8 оканчивающаяся нулем 
  char sCurrentLatitude[16];  // =строка UTF8 оканчивающаяся нулем 
  char sCurrentLongitude[16];  // =строка UTF8 оканчивающаяся нулем 
  char sNavigationalSolution[16];  // =строка UTF8 оканчивающаяся нулем 
  char sHdop[8];  // =строка UTF8 оканчивающаяся нулем 
  char sRowDirection[8];  // =строка UTF8 оканчивающаяся нулем 
  char sNearestPointTitle[33];  // =строка UTF8 оканчивающаяся нулем 
  char sSpeed[8];  // =строка UTF8 оканчивающаяся нулем 
  char sFirstPointLat[16];  // =строка UTF8 оканчивающаяся нулем 
  char sFirstPointLon[16];  // =строка UTF8 оканчивающаяся нулем 
  char sSecondPointLon[16];  // =строка UTF8 оканчивающаяся нулем 
  char sGnssCourse[8];  // =строка UTF8 оканчивающаяся нулем 
  char sRowLength[8];  // =строка UTF8 оканчивающаяся нулем 
  char sAccuracy[8];  // =строка UTF8 оканчивающаяся нулем 
  char sNearestPointDistance[8];  // =строка UTF8 оканчивающаяся нулем 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)


/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


AutopilotXY::AutopilotXY() {
}

AutopilotXY::~AutopilotXY() {
}

void AutopilotXY::Init() {
  RemoteXY_Init ();

  Serial.begin(9600);
  Serial.println("Serial started at 9600");
  
  pinMode( PIN_CALIBRATION_LEFT,  INPUT_PULLUP );
  pinMode( PIN_CALIBRATION_RIGHT, INPUT_PULLUP );
  pinMode( PIN_ON_OFF,            INPUT_PULLUP );
  pinMode( PIN_SET_COURSE,        INPUT_PULLUP );
  pinMode( PIN_REVERS,            INPUT_PULLUP );
  pinMode( PIN_MANUAL_MODE,       INPUT_PULLUP );



  //начальное значение времени одного оборота
  RemoteXY.agress = INITIAL_TURN_SPEED_SECONDS;
  _wheelHandler.UpdateAgression(RemoteXY.agress);

  RemoteXY.resistor_center = INITIAL_RESISTOR_CENTER;
  _wheelHandler.SetWheelCenter(INITIAL_RESISTOR_CENTER);

  strcpy(RemoteXY.sSecondPointLat, NA_STRING);
  strcpy(RemoteXY.sSecondPointLon, NA_STRING);
  strcpy(RemoteXY.sFirstPointLat, NA_STRING);
  strcpy(RemoteXY.sFirstPointLon, NA_STRING);
  strcpy(RemoteXY.sRowDirection, NA_STRING);
  strcpy(RemoteXY.sRowLength, NA_STRING);

  strcpy(RemoteXY.sNavigationalSolution, NA_STRING);
  strcpy(RemoteXY.sCurrentLongitude, NA_STRING);
  strcpy(RemoteXY.sCurrentLatitude, NA_STRING);
  strcpy(RemoteXY.sHdop, NA_STRING);
  strcpy(RemoteXY.sSpeed, NA_STRING);
  strcpy(RemoteXY.sGnssCourse, NA_STRING);
  strcpy(RemoteXY.sAccuracy, NA_STRING);
  strcpy(RemoteXY.sNearestPointTitle, "Ближайшая точка: ");
}

bool AutopilotXY::UpdatePosition() {
  static unsigned int prevTime = millis();
  static bool requreRmcFlag = false;
  bool isSucceed = true;

  //if(RemoteXY.connect_flag == 0)
    //return false;

  if(requreRmcFlag) {
    if(_gnssParser.ParseGNRMC())
    {
      UpdateRmcInformation();
      _calculationHelper.NotifySensorUpdate();
      prevTime = millis();
    }
    else 
    {
      Serial.println("GNRMC reading failed...");
      isSucceed = false;
    }
    requreRmcFlag = false;
  }
  else {
    if(_gnssParser.ParseGNGGA()) 
    {
      UpdateGgaInformation();
      _calculationHelper.NotifySensorUpdate();
      prevTime = millis();
    }
    else 
    {
      Serial.println("GNGGA reading failed...");
      isSucceed = false;
    }
    requreRmcFlag = true;
  }

  if(strlen(_gnssParser.GetAccuracyStr()) == 0) {
    strcpy(RemoteXY.sAccuracy, NA_STRING);
  }
  else {
    strcpy(RemoteXY.sAccuracy, _gnssParser.GetAccuracyStr());
  }

  unsigned int currentTime = millis();
  if(_isPositionRecived && ((currentTime - prevTime) > 3000))
  {
    Serial.println("timeot gnss");
    strcpy(RemoteXY.sNavigationalSolution, NA_STRING);
    strcpy(RemoteXY.sCurrentLongitude, NA_STRING);
    strcpy(RemoteXY.sCurrentLatitude, NA_STRING);
    strcpy(RemoteXY.sHdop, NA_STRING);
    strcpy(RemoteXY.sSpeed, NA_STRING);
    strcpy(RemoteXY.sGnssCourse, NA_STRING);
    strcpy(RemoteXY.sAccuracy, NA_STRING);
    
    _isPositionRecived = false;
  }
  
  return isSucceed;
}

void AutopilotXY::UpdateGgaInformation() {
  _isPositionRecived = true;
  _needPositionPostprosses = true;
  
  strcpy(RemoteXY.sCurrentLatitude, _gnssParser.GetLatitudeStr());
  strcpy(RemoteXY.sCurrentLongitude, _gnssParser.GetLongitudeStr());
  
  if(strlen(_gnssParser.GetStatusStr()) == 0) {
    strcpy(RemoteXY.sNavigationalSolution, NA_STRING);
  }
  else {
    switch(_gnssParser.GetStatusStr()[0]) {
      case '0':
        strcpy(RemoteXY.sNavigationalSolution, "поиск");
      break;
      case '1':
        strcpy(RemoteXY.sNavigationalSolution, "автоном.");
      break;
      case '2':
        strcpy(RemoteXY.sNavigationalSolution, "дифф.");
      break;
      case '3':
        strcpy(RemoteXY.sNavigationalSolution, "PPS");
      break;
      case '4':
        strcpy(RemoteXY.sNavigationalSolution, "Fix RTK");
      break;
      case '5':
        strcpy(RemoteXY.sNavigationalSolution, "Float RTK");
      break;
      case '6':
        strcpy(RemoteXY.sNavigationalSolution, "экст.");
      break;
      case '7':
        strcpy(RemoteXY.sNavigationalSolution, "фикс. к.");
      break;
      case '8':
        strcpy(RemoteXY.sNavigationalSolution, "сим.");
      break;
    }
  }

  if(strlen(_gnssParser.GetHDOPStr()) == 0) {
    strcpy(RemoteXY.sHdop, NA_STRING);
  }
  else {
    strcpy(RemoteXY.sHdop, _gnssParser.GetHDOPStr());
  }
}

void AutopilotXY::UpdateRmcInformation() {
  _isPositionRecived = true;
  _needPositionPostprosses = true;
      
  strcpy(RemoteXY.sCurrentLatitude, _gnssParser.GetLatitudeStr());
  strcpy(RemoteXY.sCurrentLongitude, _gnssParser.GetLongitudeStr());

  if(strlen(_gnssParser.GetSpeedStr()) == 0) {
    strcpy(RemoteXY.sSpeed, NA_STRING);
  }
  else {
    float speed = String(_gnssParser.GetSpeedStr()).toFloat();
    speed *= 1.85; //перевод из узлов в км.ч.
    dtostrf(speed, 7, 3, RemoteXY.sSpeed);
  }
  
  if(strlen(_gnssParser.GetHeadingStr()) == 0) {
    strcpy(RemoteXY.sGnssCourse, NA_STRING);
  }
  else {
    strcpy(RemoteXY.sGnssCourse, _gnssParser.GetHeadingStr());
  }
}

void AutopilotXY::UpdateUI() {
  
  //здесь обрабатываються нажатия кнопок
  UpdatePhysicalButtons();
  UpdateUIButtonsAndText();

  //звук нажатия кнопки выкл
  SoundUpdate();
  
  RemoteXY_Handler ();
  
  //если смартфон потерял соединение или верхиний переключатель выключен - дальше вычисления не выполняем
  if(RemoteXY.top_switch == 0 || RemoteXY.connect_flag == 0)
  {
    RemoteXY.manual_switch = 0;
    RemoteXY.top_switch = 0;
    RemoteXY.start_gnnss_pushSwitch = 0;
    strcpy(RemoteXY.sLeftCourseCorrection, "");
    strcpy(RemoteXY.sWheelPosition, "");
    strcpy(RemoteXY.sRightCourseCorrection, "");
    _wheelHandler.PowerSwitch(false);
    
    return;
  }
  
  //действия с поправкой курса в этой функции
  UpdateUICourseCorrection();

  //если ручное управление включено - продолжаем цикл
  if(RemoteXY.manual_switch == 0 || 
      (!_isPositionRecived && RemoteXY.start_gnnss_pushSwitch == 1)) {
    return;
  }

  if(_isPointASet && _isPointBSet && _isPositionRecived && RemoteXY.start_gnnss_pushSwitch == 1) {
    SetCourseFromCoorinates();
  }

  if(_reversCoeff == -1)
  {
    RemoteXY.course_to_go += 180;
  }

  //переводим значения курса
  //пределы (0; 359)
  while(RemoteXY.course_to_go < 0)
  {
    RemoteXY.course_to_go += 360;
  }
  while(RemoteXY.course_to_go >= 360)
  {
    RemoteXY.course_to_go -= 360;
  }
  
  //разница межуду заданным и фактическим курсом
  int diff = RemoteXY.course_to_go - (int)RemoteXY.compass_course;
  if(_reversCoeff == -1)
    diff -= 180;
    
  //переводим значения которые 
  //больше 180 в пределы (-180; 180)
  while(diff > 180)
  {
    diff -= 360;
  }
  while(diff < -180)
  {
    diff += 360;
  }

  SetWheelAngle(diff);
}

void AutopilotXY::UpdateUIButtonsAndText() {
  static bool is_autopilot_on = false;
  static bool is_gnss_on = false;
  static bool is_top_switch = false;

  //отображаем положение руля на смартфон
  dtostrf(_wheelHandler.GetWheelPosition(), 3, 0, RemoteXY.sWheelPosition);

  //вычисляем агрессию по заданному значению
  //времени одного оборота двигателя
  static uint16_t prevAgression;
  if(prevAgression != RemoteXY.agress) {
    _wheelHandler.UpdateAgression(RemoteXY.agress);
    prevAgression = RemoteXY.agress;
  }

    //установка центра руля
  static uint16_t prevCenter;
  if(prevCenter != RemoteXY.resistor_center) {
    _wheelHandler.SetWheelCenter(RemoteXY.resistor_center);
    prevCenter = RemoteXY.resistor_center;
  }
    
  if(RemoteXY.top_switch == 0 && is_top_switch)
  {
    is_top_switch = false;
    SoundStart();
  }
  else if(RemoteXY.top_switch == 1 && !is_top_switch)
  {
    is_top_switch = true;
    SoundStart();
  }

  if(RemoteXY.top_switch == 0)
  {
    return;
  }
  
  //назначаем текущий курс, как заданный курс
  else if(RemoteXY.calibrate == 1)
  {
    _courseCorrection = 0;
    strcpy(RemoteXY.sLeftCourseCorrection, "0");
    strcpy(RemoteXY.sRightCourseCorrection, "0");
    
    RemoteXY.course_to_go = (int)RemoteXY.compass_course;

    if(_isPointASet && _isPointASet) {
      
      if(RemoteXY.declonation == 0) {
        RemoteXY.declonation = _calculationHelper.GetRowDirection() - RemoteXY.compass_course;
      }
      else {
        float oldOffset = RemoteXY.compass_course + RemoteXY.declonation - _calculationHelper.GetRowDirection();
        RemoteXY.declonation = _calculationHelper.GetRowDirection() - RemoteXY.compass_course;
        if(oldOffset < -90 && oldOffset > 90)
        {
          RemoteXY.declonation += 180;
        }
        
      }
      //переводим значения которые
      //больше 180 в пределы (-180; 180)
      while(RemoteXY.declonation > 180)
      {
        RemoteXY.declonation -= 360;
      }
      while(RemoteXY.declonation < -180)
      {
        RemoteXY.declonation += 360;
      }
    }

    RemoteXY.center = 1;
    RemoteXY.calibrate = 0;
    SoundStart();
  }
  
  //присваиваем текущее значение с резистора как центральное
  if(RemoteXY.center == 1)
  {
    RemoteXY.resistor_center = prevCenter = _wheelHandler.SetWheelCenter();
    RemoteXY.center = 0;
    SoundStart();
  }
  
  //поправка курса в положительную сторону
  else if(RemoteXY.course_inc == 1 && _reversCoeff == 1 || RemoteXY.course_dec == 1 && _reversCoeff == -1)
  {
    _courseCorrection = _courseCorrection + 1;
    RemoteXY.course_to_go += 1;
    RemoteXY.course_inc = 0;
    RemoteXY.course_dec = 0;
    SoundStart();
  }
  //поправка курса в отрицательную
  else if(RemoteXY.course_dec == 1 && _reversCoeff == 1 || RemoteXY.course_inc == 1 && _reversCoeff == -1)
  {
    _courseCorrection = _courseCorrection - 1;
    RemoteXY.course_to_go -= 1;
    RemoteXY.course_inc = 0;
    RemoteXY.course_dec = 0;
    SoundStart();
  }
  
  //для хода назад
  if(RemoteXY.revers_switch == 1 && _reversCoeff == 1)
  {
    _reversCoeff = -1;
    SoundStart();
  }
  else if(RemoteXY.revers_switch == 0 && _reversCoeff == -1)
  {
    _reversCoeff = 1;
    SoundStart();
  }

  if(!_isPointASet && !_isPointBSet)
  {
    RemoteXY.start_gnnss_pushSwitch = 0;
    is_gnss_on = false;
  }

  if(RemoteXY.start_gnnss_pushSwitch == 0 && is_gnss_on)
  {
    RemoteXY.manual_switch = RemoteXY.start_gnnss_pushSwitch;
    is_gnss_on = false;
    SoundStart();
  }
  else if(RemoteXY.start_gnnss_pushSwitch == 1 && !is_gnss_on)
  {
    RemoteXY.manual_switch = RemoteXY.start_gnnss_pushSwitch;
    is_gnss_on = true;
    SoundStart();
  }
  
  if(RemoteXY.manual_switch == 0 && is_autopilot_on)
  {
    RemoteXY.start_gnnss_pushSwitch = RemoteXY.manual_switch;
    _wheelHandler.PowerSwitch(false);
    is_autopilot_on = false;
    SoundStart();
  }
  else if(RemoteXY.manual_switch == 1 && !is_autopilot_on)
  {
    _wheelHandler.PowerSwitch(true);
    is_autopilot_on = true;
    SoundStart();
  }

  if(RemoteXY.set_first_point == 1 && _isPositionRecived)
  {
    strcpy(RemoteXY.sFirstPointLat, _gnssParser.GetLatitudeStr());
    strcpy(RemoteXY.sFirstPointLon, _gnssParser.GetLongitudeStr());
      
    _pointA = MapPosition(_gnssParser.GetLatitudeStr(), _gnssParser.GetLongitudeStr());
    _isPointASet = true;
    _calculationHelper.SetSegmentA(_gnssParser.GetLatitudeStr(), _gnssParser.GetLongitudeStr());
    
    RemoteXY.set_first_point = 0;
    SoundStart();
  }

  if(RemoteXY.set_second_point == 1 && _isPositionRecived)
  {
    strcpy(RemoteXY.sSecondPointLat, _gnssParser.GetLatitudeStr());
    strcpy(RemoteXY.sSecondPointLon, _gnssParser.GetLongitudeStr());
    
    _pointB = MapPosition(_gnssParser.GetLatitudeStr(), _gnssParser.GetLongitudeStr());
    _isPointBSet = true;
    _calculationHelper.SetSegmentB(_gnssParser.GetLatitudeStr(), _gnssParser.GetLongitudeStr());
    
    RemoteXY.set_second_point = 0;
    SoundStart();
  }

  if(RemoteXY.del_first_point == 1 && _isPointASet)
  {
    strcpy(RemoteXY.sFirstPointLat, NA_STRING);
    strcpy(RemoteXY.sFirstPointLon, NA_STRING);

    _isPointASet = false;
    _calculationHelper.UnsetSegmentA();
    
    RemoteXY.del_first_point = 0;
    SoundStart();
  }

  if(RemoteXY.del_second_point == 1 && _isPointBSet)
  {
    strcpy(RemoteXY.sSecondPointLat, NA_STRING);
    strcpy(RemoteXY.sSecondPointLon, NA_STRING);

    _isPointBSet = false;
    _calculationHelper.UnsetSegmentB();
    
    RemoteXY.del_second_point = 0;
    SoundStart();
  }

  if(RemoteXY.set_new_row == 1 && _isPointASet && _isPointBSet)
  {
    int temp = _calculationHelper.GetRowDirection() - RemoteXY.compass_course - RemoteXY.declonation;
    while(temp < 0)
    {
      temp += 360;
    }
    while(temp >= 360)
    {
      temp -= 360;
    }

    if(temp < 270 && temp > 90) {
      _calculationHelper.NewRowFromPositionOpposite(_gnssParser.GetLatitudeStr(), _gnssParser.GetLongitudeStr());
    }
    else{
      _calculationHelper.NewRowFromPosition(_gnssParser.GetLatitudeStr(), _gnssParser.GetLongitudeStr());
    }
    
    
    RemoteXY.set_new_row = 0;
    SoundStart();
  }

}

void AutopilotXY::UpdateUICourseCorrection() {
    if(_courseCorrection > 0)
    {
       strcpy(RemoteXY.sLeftCourseCorrection, "0");
       dtostrf(_courseCorrection, 2, 0, RemoteXY.sRightCourseCorrection);
    }
    else if(_courseCorrection < 0)
    {
       strcpy(RemoteXY.sRightCourseCorrection, "0");
       dtostrf(_courseCorrection, 2, 0, RemoteXY.sLeftCourseCorrection);
    }
    else
    {
      strcpy(RemoteXY.sLeftCourseCorrection, "0");
      strcpy(RemoteXY.sRightCourseCorrection, "0");
    }
}

void AutopilotXY::UpdatePhysicalButtons() {
  //переменные состояний
  static bool isCalibrationLeftDone    = false;
  static bool isCalibrationRightDone   = false;
  static bool isOnOffDone              = false;
  static bool isSetCiurseDone          = false;
  static bool isReversDone             = false;
  static bool isManualModeDone         = false;

  //обнулфем флаги, если кнопка отжата
  if(digitalRead(PIN_ON_OFF) == 1) {
    isOnOffDone = false;
  }

  if(digitalRead(PIN_MANUAL_MODE) == 1) {
    isManualModeDone = false;
  }
  
  if(digitalRead(PIN_REVERS) == 1) {
    isReversDone = false;
  }

  if(digitalRead(PIN_SET_COURSE) == 1) {
    isSetCiurseDone = false;
  }

  if(digitalRead(PIN_CALIBRATION_LEFT) == 1) {
    isCalibrationLeftDone = false;
  }

  if(digitalRead(PIN_CALIBRATION_RIGHT) == 1) {
    isCalibrationRightDone = false;
  }
  
  if(digitalRead(PIN_ON_OFF) == 0 && !isOnOffDone) {
    isOnOffDone = true;
    if(RemoteXY.top_switch == 0)
      RemoteXY.top_switch = 1;
    else
      RemoteXY.top_switch = 0;
  }
  
  if(digitalRead(PIN_MANUAL_MODE) == 0 && !isManualModeDone) {
    isManualModeDone = true;
    if(RemoteXY.manual_switch == 0)
      RemoteXY.manual_switch = 1;
    else
      RemoteXY.manual_switch = 0;
  }

  if(digitalRead(PIN_REVERS) == 0 && !isReversDone) {
    isReversDone = true;
    if(RemoteXY.revers_switch == 0)
      RemoteXY.revers_switch = 1;
    else
      RemoteXY.revers_switch = 0;
  }

  if(digitalRead(PIN_SET_COURSE) == 0 && !isSetCiurseDone) {
    isSetCiurseDone = true;
    RemoteXY.calibrate = 1;
  }

  if(digitalRead(PIN_CALIBRATION_LEFT) == 0 && !isCalibrationLeftDone) {
    isCalibrationLeftDone = true;
    RemoteXY.course_dec = 1;
  }

  if(digitalRead(PIN_CALIBRATION_RIGHT) == 0 && !isCalibrationRightDone) {
    isCalibrationRightDone = true;
    RemoteXY.course_inc = 1;
  }
}

void AutopilotXY::SetCourseFromCoorinates() {
  
  int trueCourse =  RemoteXY.compass_course + RemoteXY.declonation;
  int rowDirection = _calculationHelper.GetRowDirection();
  while(trueCourse < 0)
  {
    trueCourse += 360;
  }
  while(trueCourse >= 360)
  {
    trueCourse -= 360;
  }
  
  int delta = _calculationHelper.GetRowDirection() - trueCourse;
  while(delta < 0)
  {
    delta += 360;
  }
  while(delta >= 360)
  {
    delta -= 360;
  }

  float offset = String(_calculationHelper.GetRowOffset()).toFloat();
  
  if(delta < 270 && delta > 90) {
    rowDirection += 180;
    offset *= -1;
  }


  if(RemoteXY.start_gnnss_pushSwitch == 0) {
    dtostrf(offset, 7, 2, RemoteXY.sNearestPointDistance);
    return;
  }

  offset += _courseCorrection;
  dtostrf(offset, 7, 2, RemoteXY.sNearestPointDistance);

  while(rowDirection < 0)
  {
    rowDirection += 360;
  }
  while(rowDirection >= 360)
  {
    rowDirection -= 360;
  }

  offset = offset * 100; //cm
  
  if(offset >= 0 && offset < 5) {
    RemoteXY.course_to_go = rowDirection - (0 * _reversCoeff);
  }
  else if(offset <= 0 && offset > -5) {
    RemoteXY.course_to_go = rowDirection + (0 * _reversCoeff);
  }
  else if(offset >= 5 && offset < 15) {
    RemoteXY.course_to_go = rowDirection - (2 * _reversCoeff);
  }
  else if(offset <= -5 && offset > -15) {
    RemoteXY.course_to_go = rowDirection + (2 * _reversCoeff);
  }
  else if(offset >= 5 && offset < 15) {
    RemoteXY.course_to_go = rowDirection - (5 * _reversCoeff);
  }
  else if(offset <= -5 && offset > -15) {
    RemoteXY.course_to_go = rowDirection + (5 * _reversCoeff);
  }
  else if(offset >= 15 && offset < 50) {
    RemoteXY.course_to_go = rowDirection - (10 * _reversCoeff);
  }
  else if(offset <= -15 && offset > -50) {
    RemoteXY.course_to_go = rowDirection + (10 * _reversCoeff);
  }
  else if(offset >= 50) {
    RemoteXY.course_to_go = rowDirection - (15 * _reversCoeff);
  }
  else {
    RemoteXY.course_to_go = rowDirection + (15 * _reversCoeff);
  }

  RemoteXY.course_to_go -= RemoteXY.declonation;
}

void AutopilotXY::SetWheelAngle(int diff) {
  // руль прямо
  if(diff <= DEAD_ZONE && diff >= -DEAD_ZONE)
  {
    _wheelHandler.RotateTo(0);
  }
  //небольшой поворот вправо
  else if(diff <= SMALL_TURN_ZONE && diff > DEAD_ZONE)
  {
    _wheelHandler.RotateTo(SMALL_TURN_AMOUNT * _reversCoeff);
  }
  //небольшой поворот влево 
  else if(diff >= -SMALL_TURN_ZONE && diff < -DEAD_ZONE) 
  {
    _wheelHandler.RotateTo(-SMALL_TURN_AMOUNT * _reversCoeff);
  }
  //средний поворот влево
  else if(diff <= MEDIUM_TURN_ZONE && diff > SMALL_TURN_ZONE)
  {
    _wheelHandler.RotateTo(MEDIUM_TURN_AMOUNT * _reversCoeff);
  }
  //средний поворот влево 
  else if(diff >= -MEDIUM_TURN_ZONE && diff < -SMALL_TURN_ZONE) 
  {
    _wheelHandler.RotateTo(-MEDIUM_TURN_AMOUNT * _reversCoeff);
  }
  //большой поворот влево
  else if(diff <= BIG_TURN_ZONE  && diff > MEDIUM_TURN_ZONE)
  {
    _wheelHandler.RotateTo(BIG_TURN_AMOUNT * _reversCoeff);
  }
  //большой поворот влево 
  else if(diff >= -BIG_TURN_ZONE && diff < -MEDIUM_TURN_ZONE) 
  {
    _wheelHandler.RotateTo(-BIG_TURN_AMOUNT * _reversCoeff);
  }
  else if(diff > BIG_TURN_ZONE)
  {
    _wheelHandler.RotateTo(MAX_TURN_AMOUNT * _reversCoeff);
  }
  //большой поворот влево 
  else if(diff < -BIG_TURN_ZONE) 
  {
    _wheelHandler.RotateTo(-MAX_TURN_AMOUNT * _reversCoeff);
  }
}

void AutopilotXY::PositionPostprosses()
{
  if(_needPositionPostprosses) {
    _currentPosition = MapPosition(_gnssParser.GetLatitudeStr(), _gnssParser.GetLongitudeStr());
    _calculationHelper.UpdateCurrentPosition(_gnssParser.GetLatitudeStr(), _gnssParser.GetLongitudeStr());
    if(_isPointASet && _isPointBSet)
    {
      dtostrf((int)_calculationHelper.GetRowDirection(), 3, 0, RemoteXY.sRowDirection);
      if(_calculationHelper.GetRowLength() < 1)
      {
        dtostrf(_calculationHelper.GetRowLength(), 7, 2, RemoteXY.sRowLength);
      }
      else
      {
        dtostrf(_calculationHelper.GetRowLength(), 7, 0, RemoteXY.sRowLength);
      }
    }
    else
    {
      strcpy(RemoteXY.sRowDirection, NA_STRING);
      strcpy(RemoteXY.sRowLength, NA_STRING);
    }
    
    _needPositionPostprosses = false;
  }
}

void AutopilotXY::SoundStart()
{
  _soundStartTime = millis();
  RemoteXY.buzzer = BUZZER_ID;
}

void AutopilotXY::SoundUpdate()
{
  unsigned int currentTime = millis();
  if(!_isPositionRecived && RemoteXY.start_gnnss_pushSwitch == 1)
  {
    RemoteXY.buzzer = ALARM_ID;
  }
  else if((currentTime - _soundStartTime) > 500)
  {
    RemoteXY.buzzer = 0;
  }
}
