#include "FrediLib.h"
#include <Wire.h> // not used?
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


int fixedClampStepped(float v, float x, float y, int a, int b, float stepped){
  float val = constrain(map(v*100,x*100,y*100,a,b+1),a,b)/stepped;
  return (int)floor(val)*stepped; // or floor?
}

Bateria::Bateria(int latchPin, int clockPin, int dataPin, int connected_leds){
  _latchPin = latchPin;
  _dataPin = dataPin;
  _clockPin = clockPin;
  _connected_leds = connected_leds;
  pinMode(_latchPin, OUTPUT);
  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
}

int Bateria::showLevel(float level){
  int _i, _numberToDisplay;
  _i = fixedClampStepped(level, _minLevel, _maxLevel, 0, _connected_leds, 1);
  _numberToDisplay = _leds_states[_i];
  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, MSBFIRST, _numberToDisplay);
  digitalWrite(_latchPin, HIGH);
  return _i;
}

FrediTx::FrediTx(int CE_PIN, int CSN_PIN){
  _CE_PIN = CE_PIN;
  _CSN_PIN = CSN_PIN;
  _radio = new RF24(_CE_PIN, _CSN_PIN); // TRICKY
}
void FrediTx::begin(){
  _radio->begin(); // TRICKY
  _radio->setPALevel(RF24_PA_MAX);
  _radio->setDataRate(RF24_250KBPS);
  //_radio.setPayloadSize(4);
  //_radio.setChannel(2);
  //_radio.setRetries(15, 15);
  _radio->openWritingPipe(_direccion); //Abrimos un canal de escritura
}
bool FrediTx::send(){
  _datos[0] += 1;
  return _radio->write(_datos, sizeof(_datos));
}
void FrediTx::printData(){
  Serial.print("Datos enviados: ");
  Serial.print(_datos[0]);
  Serial.print(" , ");
  Serial.print(_datos[1]);
  Serial.print(" , ");
  Serial.println(_datos[2]);
}

// =============================================================

FrediRx::FrediRx(int CE_PIN, int CSN_PIN){
  _CE_PIN = CE_PIN;
  _CSN_PIN = CSN_PIN;
  _radio = new RF24(_CE_PIN, _CSN_PIN); // TRICKY
}
void FrediRx::begin(){
  _radio->begin(); // TRICKY
  _radio->setPALevel(RF24_PA_MAX);
  _radio->setDataRate(RF24_250KBPS);
  //_radio.setPayloadSize(4);
  //_radio.setChannel(2);
  //_radio.setRetries(15, 15);
  _radio->openWritingPipe(_direccion); //Abrimos un canal de escritura
  _radio->startListening();
}
bool FrediRx::available(){
  return _radio->available();
}
void FrediRx::read(){
  _radio->read(_datos, sizeof(_datos));
}
void FrediRx::printData(){
  Serial.print("Datos enviados: ");
  Serial.print(_datos[0]);
  Serial.print(" , ");
  Serial.print(_datos[1]);
  Serial.print(" , ");
  Serial.println(_datos[2]);
}
