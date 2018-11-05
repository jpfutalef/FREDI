#ifndef FrediLib_h
#define FrediLib_h

#include "Arduino.h"

class RF24;

// =============================================================

class Bateria
{
  public:
    Bateria(int latchPin, int clockPin, int dataPin, int connected_leds);
    int showLevel(float level);
  private:
    //int fixedClampStepped(float v, float x, float y, int a, int b, float stepped);
    const int _leds_states[7] = {B000000, B000001, B000011, B000111, B001111, B011111, B111111};
    char _state = 0; // 0 = normal, 1 = cargando, 2 = bateria baja
    int _latchPin;
    int _dataPin;
    int _clockPin;
    int _connected_leds;
    float _minLevel = 3.5;
    float _maxLevel = 4.2;
};

// =============================================================

class FrediTx
{
  public:
    FrediTx(int CE_PIN, int CSN_PIN);
    void begin();
    bool send();
    void printData();
  private:
    int _CE_PIN;
    int _CSN_PIN;
    RF24 *_radio; // TRICKY
    byte _direccion[5] = {'c','a','n','a','l'}; //Variable con la dirección del canal por donde se va a transmitir
    float _datos[3] = {1,2,3}; //vector con los datos a enviar
};

// =============================================================

class FrediRx
{
  public:
    FrediRx(int CE_PIN, int CSN_PIN);
    void begin();
    bool available();
    void read();
    void printData();
  private:
    int _CE_PIN;
    int _CSN_PIN;
    RF24 *_radio; // TRICKY
    byte _direccion[5] = {'c','a','n','a','l'}; //Variable con la dirección del canal por donde se va a transmitir
    float _datos[3]; //vector con los datos a enviar
};

#endif
