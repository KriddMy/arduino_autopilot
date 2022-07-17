#include <Wire.h>

#define I2C_ADDRESS 23

#define WITHOUT_RESISTOR

//пины для драйвера двигателя руля
#define PIN_DIR 12
#define PIN_PUL 13
#define PIN_ENA 11

#define PIN_SENSOR1 1
#define PIN_SENSOR2 2
#define PIN_SENSOR3 3

#define DESIGNED_MOTOR_STEPS 200  //фактическое количество шагов из спецификации двигателя
#define PULSES_PER_REV 400        //берем из таблицы драйвера двигателя
#define RESISTOR_ERROR 4
#define MOTOR_TO_WHEEL_RATIO 30/3

//даитчик положения руля
#define PIN_RESISTOR A0

//константы сообщений по I2C шине
const String ANGLE("ANG");
const String AGRESSION("AGR");
const String POWER("PWR");
const String CENTER("CTR");

//Скорость поворота двигателя. Определяет задержку
//между импульсами в микросекундах. Всегда больше 2 и
//рассичтывается из заданного времени полного оборота
int WheelAgression = 16383;

//Данные с датчика при центральной позиции руля
int WheelCenterPosition = 290;

//программный счетчик шагов руля
//(-) влево (+) вправо
int WheelPositionCalculated = 0;

//связь между потоками
int WheelPositionToGo = 0;      //текушяя позиция куда стремится повернуть руль в шагах двигателя
int WheelPostionIncrement = 0;  //коефициент для программного счетчика шагов. Если положительный - руль проворачивается по часовой.

//поправка для перевода значений резистора
//в удобные для чтения
float RESISTOR_TO_PULSES_MULTIPLIER;
float RESISTOR_TO_DEGREES_MULTIPLIER;
int   PULSES_PER_STEP;

//положение руля на резисторе переведенное в значение шагов
int WheelPositionResistor = 0;
//положение руля на резисторе переведенное в значение градусов
int WheelPositionDegrees = 0;

void setup() {
  Serial.begin(9600);

  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(recieveEvent);
  Wire.onRequest(requestEvent);
  
  //расчитываем коэфицент перевода из начального значения на резисторе в эквивалент градусов
  RESISTOR_TO_DEGREES_MULTIPLIER = 1 / 1;
  RESISTOR_TO_DEGREES_MULTIPLIER *=  360;
  RESISTOR_TO_DEGREES_MULTIPLIER /= 98;

  //расчитываем коэфицент перевода из начального значения на резисторе в эквивалент шагов
  RESISTOR_TO_PULSES_MULTIPLIER = 1 / 1;
  RESISTOR_TO_PULSES_MULTIPLIER *= PULSES_PER_REV;
  RESISTOR_TO_PULSES_MULTIPLIER /= 98;

  PULSES_PER_STEP = PULSES_PER_REV / DESIGNED_MOTOR_STEPS;
  
  Serial.print("Wheel Coeff: ");
  Serial.println(RESISTOR_TO_PULSES_MULTIPLIER);
  
  pinMode( PIN_DIR,       OUTPUT );
  pinMode( PIN_PUL,       OUTPUT );
  pinMode( PIN_ENA,       OUTPUT );
  pinMode( PIN_RESISTOR,  INPUT );

  pinMode(PIN_SENSOR1,        INPUT);
  pinMode(PIN_SENSOR2,        INPUT);
  pinMode(PIN_SENSOR3,        INPUT);

  CalculateAgression(5);
}

void loop() {
  if(WheelPositionCalculated != WheelPositionToGo) {
    digitalWrite( PIN_PUL, 1 );
    delayMicroseconds(WheelAgression);
    digitalWrite( PIN_PUL, 0 );
    delayMicroseconds(WheelAgression);
    WheelPositionCalculated += WheelPostionIncrement;
  }
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
    Serial.print("Angle: ");
    Serial.println(value);
  }
  else if(AGRESSION.equals(sCode)) 
  {
    CalculateAgression(value);
    Serial.print("Agression: ");
    Serial.println(value);
  }
  else if(POWER.equals(sCode)) 
  {
    digitalWrite(PIN_ENA, (bool)value);
    Serial.print("ENA: ");
    Serial.println((bool)value);
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
    Calibrate();
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
    Serial.println("Calibartion OK");
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

  Serial.print("Rotating to: ");
  Serial.println(deg);
  Serial.print("Pulses: ");
  Serial.println(pulsesTodo);

  //устанавливае значения, к которому поворачивает руль
  WheelPositionToGo = (int)pulses;
}

void UpdateWheelPostionSensor(int center)
{
  int RowResistorInput = analogRead(PIN_RESISTOR);
  Serial.print("Resistor input: ");
  Serial.println(RowResistorInput);
  
  WheelPositionResistor = RowResistorInput - center;
  WheelPositionDegrees = WheelPositionResistor * RESISTOR_TO_DEGREES_MULTIPLIER;
  WheelPositionResistor *= RESISTOR_TO_PULSES_MULTIPLIER;
}

void Calibrate()
{
  bool sensor1 = analogRead(PIN_SENSOR1) < 100 ? false : true;
  bool sensor2 = analogRead(PIN_SENSOR2) < 100 ? false : true;
  bool sensor3 = analogRead(PIN_SENSOR3) < 100 ? false : true;

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
  else if(sensor1 == 1 && sensor2 == 0 && sensor3 == 1)
  {
    WheelPositionCalculated = 0;
    return;
  }
  else if(sensor1 == 0 && sensor2 == 1 && sensor3 == 0)
  {
    for(int i = 0; i < 10; i++)
    {
      digitalWrite( PIN_PUL, 1 );
      delayMicroseconds(WheelAgression);
      digitalWrite( PIN_PUL, 0 );
      delayMicroseconds(WheelAgression);
    }

    Calibrate();
  }

  while(true)
  {
    for(int i = 0; i < 10; i++)
    {
      digitalWrite( PIN_PUL, 1 );
      delayMicroseconds(WheelAgression);
      digitalWrite( PIN_PUL, 0 );
      delayMicroseconds(WheelAgression);
    }

    if(sensor1 == 1 && sensor2 == 0 && sensor3 == 1)
    {
      WheelPositionCalculated = 0;
      return;
    }
  }
}
