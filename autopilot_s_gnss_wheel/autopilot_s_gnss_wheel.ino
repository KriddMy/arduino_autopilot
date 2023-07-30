#include <Wire.h>

#define I2C_ADDRESS 23

#define WITHOUT_RESISTOR //старый варианет считывания положения руля был по регулируемому резистору (не удобно и не точно)
//#define SERIAL_SHOW_SENSORS_VALUES

//пины для драйвера двигателя
#define PIN_DIR 12
#define PIN_PUL 13
#define PIN_ENA 11

//пины индукционных сенсоров положения руля
#define PIN_SENSOR1 A2
#define PIN_SENSOR2 A1
#define PIN_SENSOR3 A3

#define DESIGNED_MOTOR_STEPS 400    //фактическое количество шагов из спецификации двигателя
#define PULSES_PER_REV 800          //берем из таблицы драйвера двигателя
#define RESISTOR_ERROR 4            //ожидаемая ошибка резистора руля в градусах
#define MOTOR_TO_WHEEL_RATIO 30/3   //передаточное число между шестеренкой руля и шестеренкой шагового двигателя

//даитчик положения руля
#define PIN_RESISTOR A0

//константы сообщений по I2C шине
const String ANGLE("ANG");
const String AGRESSION("AGR");
const String POWER("PWR");
const String CENTER("CTR");

void RotateLoop(int);
void CalibrateLoop(int);
typedef void (*LoopFunction) (int = 0);
LoopFunction loopFunc = RotateLoop;

//Скорость поворота двигателя. Определяет задержку
//между импульсами в микросекундах. Всегда больше 2 и
//рассичтывается из заданного времени полного оборота
int WheelAgression = 16383;

//Данные с резитсора при центральной позиции руля(если используется)
int WheelCenterPosition = 290;

//программный счетчик шагов руля
//(-) влево (+) вправо
int WheelPositionCalculated = 0;

//связь между потоками
int WheelPositionToGo = 0;      //текушяя позиция куда стремится повернуть руль в шагах двигателя
int WheelPostionIncrement = 0;  //коэффициент для программного счетчика шагов. Если положительный - руль проворачивается по часовой.

//поправка для перевода значений резистора в удобные для чтения

//расчитываем коэффициент перевода из сырого значения, считанного с резистора, в эквивалент шагов
constexpr float RESISTOR_TO_PULSES_MULTIPLIER = PULSES_PER_REV / 98;
//расчитываем коэффициент перевода из сырого значения, считанного с резистора, в эквивалент градусов
constexpr float RESISTOR_TO_DEGREES_MULTIPLIER = 360 / 98;

//количество импцульсов, которые необходимо подать на драйвер двигателя,
//чтобы пройти один шаг
constexpr int   PULSES_PER_STEP = PULSES_PER_REV / DESIGNED_MOTOR_STEPS;

//положение руля на резисторе переведенное в значение шагов
int WheelPositionResistor = 0;
//положение руля на резисторе переведенное в значение градусов
int WheelPositionDegrees = 0;

void setup() {
  Serial.begin(9600);

  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(recieveEvent);
  Wire.onRequest(requestEvent);
  
  //Serial.print("Wheel Coeff: ");
  //Serial.println(RESISTOR_TO_PULSES_MULTIPLIER);
  
  pinMode( PIN_DIR,       OUTPUT );
  pinMode( PIN_PUL,       OUTPUT );
  pinMode( PIN_ENA,       OUTPUT );

  #ifndef WITHOUT_RESISTOR
  pinMode( PIN_RESISTOR,  INPUT );
  #endif

  pinMode(PIN_SENSOR1,        INPUT);
  pinMode(PIN_SENSOR2,        INPUT);
  pinMode(PIN_SENSOR3,        INPUT);

  CalculateAgression(5);
}

void loop() {
  #ifdef SERIAL_SHOW_SENSORS_VALUES
  Serial.print(analogRead(PIN_SENSOR1));
  Serial.print(" ");
  Serial.print(analogRead(PIN_SENSOR2));
  Serial.print(" ");
  Serial.println(analogRead(PIN_SENSOR3));
  #endif
  digitalWrite(PIN_ENA, false);
  digitalWrite( PIN_PUL, 1 );
    delayMicroseconds(WheelAgression);
    digitalWrite( PIN_PUL, 0 );
    delayMicroseconds(WheelAgression);

  //функция калибровки либо поворота на заданный угол
  //выставляется ниже
  //loopFunc(0);
}

void requestEvent()
{
  byte msg[4];
  
  #ifndef WITHOUT_RESISTOR
  UpdateWheelPostionSensor(WheelCenterPosition);
  #else
  WheelPositionDegrees = -1;
  #endif
  
  msg[0] = WheelPositionDegrees >> 8;
  msg[1] = WheelPositionDegrees;
    
  msg[2] = WheelCenterPosition >> 8;
  msg[3] = WheelCenterPosition;

  Wire.write(msg, 4);
}

void recieveEvent(int num) {
  String sCode;
  int value;
  unsigned char rawValue[2];

  #ifndef WITHOUT_RESISTOR
  UpdateWheelPostionSensor(WheelCenterPosition);
  #else
  WheelPositionDegrees = -1;
  #endif
  
  for(int i = 0; i < num - 2; i++)
  {
    char c = Wire.read();
    sCode += c;
  }
  
  rawValue[0] = Wire.read();
  rawValue[1] = Wire.read();

  value = (rawValue[0] << 8) | (rawValue[1]);

  if(ANGLE.equals(sCode))
  {
    RotateTo(value);
    //Serial.print("Angle: ");
    //Serial.println(value);
  }
  else if(AGRESSION.equals(sCode)) 
  {
    CalculateAgression(value);
    //Serial.print("Agression: ");
    //Serial.println(value);
  }
  else if(POWER.equals(sCode)) 
  {
    digitalWrite(PIN_ENA, (bool)value);
    //Serial.print("ENA: ");
    //Serial.println((bool)value);
  }
  else if(CENTER.equals(sCode)) 
  {
    #ifndef WITHOUT_RESISTOR 
    if(value == -1)
      
      WheelCenterPosition = WheelPositionDegrees;
    else
      WheelCenterPosition = value;

    Serial.print("Center set: ");
    Serial.println(value);
    #else
    loopFunc = CalibrateLoop;
    #endif
  }
}

int CalculateAgression(int singleRevTime)
{
  uint64_t temp = singleRevTime * 1000000;
  temp /= PULSES_PER_REV;
  WheelAgression = temp;
  WheelAgression /= 2;
  if(WheelAgression < 2)
  {
    WheelAgression = 2;
  }
  
  return WheelAgression;
}

//свиряет значение положения руля на резисторе с внутренним вычислением с учетом погрешности датчика
bool IsCalibrated()
{
  const int range = RESISTOR_TO_PULSES_MULTIPLIER * RESISTOR_ERROR;
  int low_limit = WheelPositionResistor - range;
  int high_limit = WheelPositionResistor + range;
  
  if(WheelPositionCalculated > low_limit && WheelPositionCalculated < high_limit)
  {
    return true;
  }
  return false;
  
}

//функиця принимет значение в градусах
//определяющее на какой угол относительно
//нулевого значения нужно повернуть
void RotateTo(int deg)
{ 
  
  #ifndef WITHOUT_RESISTOR
  //сверяем значения с резисотра с текущим положением
  if(!IsCalibrated())
  {
    WheelPositionCalculated = WheelPositionResistor;
    //Serial.println("Calibartion OK");
  }
  #endif
  
  //конвертируем градусы в шаги двигателя
  float pulses = deg / (float)360;
  pulses *= (float)PULSES_PER_REV * MOTOR_TO_WHEEL_RATIO;

  //вычисляем на сколько шагов довернуть
  int pulsesTodo = (int)pulses - WheelPositionCalculated;

  if(pulsesTodo == 0)
  {
    return;
  }
  
  //если разница отрицательна
  //поворачиваем против часововй
  else if(pulsesTodo < 0 && WheelPostionIncrement != -1)
  {    
    WheelPostionIncrement = -1;
    digitalWrite( PIN_DIR, 0 );
    delayMicroseconds(5);
  }
  //если положительна, то поворот по часовой стрелке
  else if(pulsesTodo > 0 && WheelPostionIncrement != 1)
  {
    WheelPostionIncrement = 1;
    digitalWrite(PIN_DIR, 1 );
    delayMicroseconds(5);
  }

  //Serial.print("Rotating to: ");
  //Serial.println(deg);
  //Serial.print("Pulses: ");
  //Serial.println(pulsesTodo);

  //устанавливае значения, к которому поворачивает руль
  WheelPositionToGo = (int)pulses;
}

void UpdateWheelPostionSensor(int center)
{
  int RowResistorInput = analogRead(PIN_RESISTOR);
  //Serial.print("Resistor input: ");
  //Serial.println(RowResistorInput);
  
  WheelPositionResistor = RowResistorInput - center;
  WheelPositionDegrees = WheelPositionResistor * RESISTOR_TO_DEGREES_MULTIPLIER;
  WheelPositionResistor *= RESISTOR_TO_PULSES_MULTIPLIER;
}

void RotateLoop(int unused = 0)
{
  if(WheelPositionCalculated != WheelPositionToGo) {
    digitalWrite( PIN_PUL, 1 );
    delayMicroseconds(WheelAgression);
    digitalWrite( PIN_PUL, 0 );
    delayMicroseconds(WheelAgression);
    WheelPositionCalculated += WheelPostionIncrement;
  }
}

void CalibrateLoop(int nStackCount = 0)
{
  loopFunc = RotateLoop;

  bool sensor1 = analogRead(PIN_SENSOR1) > 512 ? false : true;
  bool sensor2 = analogRead(PIN_SENSOR2) > 512 ? false : true;
  bool sensor3 = analogRead(PIN_SENSOR3) > 512 ? false : true;

  //руль - центр
  if(sensor1 == 1 && sensor2 == 0 && sensor3 == 1)
  {
    WheelPositionCalculated = 0;
    return;
  }
  //руль в положении лиюо 45 градусов либо справа, либо слева. Неопределенное положение
  //сдвинем положение руля пока не выйдем из неопределенной зоны
  else if(sensor1 == 0 && sensor2 == 1 && sensor3 == 0)
  {
    //проверка на StackOverflow еслм датчики по какой то причине не работают
    if(nStackCount > 10)
      return;

    //поворот на градус
    for(int i = 0; i < PULSES_PER_REV / 360; i++)
    {
      digitalWrite( PIN_PUL, 1 );
      delayMicroseconds(WheelAgression);
      digitalWrite( PIN_PUL, 0 );
      delayMicroseconds(WheelAgression);
    }

    return CalibrateLoop(++nStackCount);
  }

  //////////////////////////////////////////////////////////////
  ////////////////////руль - в центр////////////////////////////
  //////////////////////////////////////////////////////////////
  if(sensor1 == 1 && sensor2 == 0 && sensor3 == 0 ||
      sensor1 == 1 && sensor2 == 1 && sensor3 == 0 ||
      sensor1 == 1 && sensor2 == 1 && sensor3 == 1)
  {
    digitalWrite(PIN_DIR, 1 );
  }
  else if(sensor1 == 0 && sensor2 == 1 && sensor3 == 1 ||
      sensor1 == 0 && sensor2 == 0 && sensor3 == 1 ||
      sensor1 == 0 && sensor2 == 0 && sensor3 == 0)
  {
    digitalWrite(PIN_DIR, 0 );
  }

  while(true)
  {
    // ОК - руль в центре
     if(sensor1 == 1 && sensor2 == 0 && sensor3 == 1)
    {
      WheelPositionCalculated = 0;
      return;
    }
     
    for(int i = 0; i < 10; i++)
    {
      digitalWrite( PIN_PUL, 1 );
      delayMicroseconds(WheelAgression);
      digitalWrite( PIN_PUL, 0 );
      delayMicroseconds(WheelAgression);
    }
  }
}
