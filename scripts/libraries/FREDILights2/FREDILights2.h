#include <Arduino.h>
#include <ArduinoSTL.h>
#include <vector>

#ifndef MAX_BRIGHTNESS
#define MAX_BRIGHTNESS 255
#endif

#ifndef PWM_FREQ
#define PWM_FREQ 150
#endif

#ifndef DEFAULT_ZERO_STATE
#define DEFAULT_ZERO_STATE 0
#endif

#ifndef MAX_STATES
#define MAX_STATES 4
#endif

#ifndef MIN_STATES
#define MIN_STATES 0
#endif

// Handlers para el objeto ShiftPWM
const int ShiftPWM_latchPin = 8;
const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad = false;

/*
Clase LightUnit para manipular una sola unidad, a mas bajo nivel
*/
class LightUnit{
public:
  LightUnit(int _id);
  LightUnit(int _id, int _state);

public:
  void setState(int _state);
  int getState( void );
  void init( void );
  void printInfo( void );

protected:
  virtual void setLightState(int _state);
  void setLightZeroState( void );
  int state, id;
  const int pwmFrequency, maxBrightness;
  int *ledPins;
};

/*
Clase FREDIHoyo para manipular un solo agujero y sus
luces
*/

class FREDIHoyo : public LightUnit{
using LightUnit::LightUnit;
private:
  void setLightState(int _state);
};

/*
Clase FREDIllave para manipular un solo agujero y sus
luces
*/

class FREDILlave : public LightUnit{
using LightUnit::LightUnit;
private:
  void setLightState(int _state);
};

/*
Clase FREDILights para manipular multiples unidades de luz
*/

class FREDILights{
public:
  FREDILights(int _unitsAmount);
  void setState(int _state[]);
  void setState(int unitId, int state);
  void setState(int unitId, int state, int blinkFreq);
  void init( void );
  void printState( void );

protected:
  int unitsAmount;
  std::vector<LightUnit> vec;
};

// FREDILlaves incluye vector de FREDILlave
class FREDILlaves : public FREDILights{
public:
  FREDILlaves(int _unitsAmount);
private:
  std::vector<FREDILlave> vec;
};

// FREDIHoyos incluye vector de FREDIHoyo
class FREDIHoyos : public FREDILights{
public:
  FREDIHoyos(int _unitsAmount);
private:
  std::vector<FREDIHoyo> vec;
};
