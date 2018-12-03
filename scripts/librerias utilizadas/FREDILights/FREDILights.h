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
Clase FREDIHole para manipular un solo agujero y sus
luces, siendo el objeto de mas bajo nivel
*/

class FREDIHole{
public:
  FREDIHole(int _id);
  FREDIHole(int _id, int _state);

public:
  void setState(int _state);
  int getState( void );
  void init( void );
  void printInfo( void );

private:
  void setLightState(int _state);
  void setLightZeroState( void );
  int state, id;
  const int pwmFrequency, maxBrightness;
  int *ledPins;
};

/*
Clase FREDIHoles para manipular los multiples agujeros
de FREDI. Llama a FREDIHole para manipular cada agujero
y operar en alto nivel.
*/

class FREDIHoles{
public:
  FREDIHoles(int _holesAmount);
  //FREDIHoles(int _holesAmount, int *initState);
  void setState(int _state[]);
  void setState(int hole, int state);
  void setState(int hole, int state, int blinkFreq);
  void init( void );
  void printState( void );

private:
  const int holesAmount;
  std::vector<FREDIHole> holesVec;
};
