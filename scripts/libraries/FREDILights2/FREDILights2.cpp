#include "FREDILights2.h"
#include <ShiftPWM.h>
#include <Arduino.h>
#include <ArduinoSTL.h>
#include <vector>

/*
 Clase FREDILights para controlar multiples unidades de luces.
 No puede instanciarse pues tiene un metodo virtual implementado en las
 subclases
*/

FREDILights::FREDILights(int _unitsAmount){
  unitsAmount = _unitsAmount;
}

void FREDILights::init(void){
  this->vec[0].init();
  return;
}

void FREDILights::setState(int _state[]){
  // int _state[]: array con ints, donde cada uno es el estado de un agujero
  for (int i = 0; i < unitsAmount; i++) {
    setState(i, _state[i]);
  }
}

void FREDILights::setState(int unitId, int _state){
  // int unitId: agujero a modificar, de 0 a holesAmount-1
  // int _state: estado a asignar al agujero
  if (unitId >= unitsAmount)
    return;
  this->vec[unitId].setState(_state);
}

void FREDILights::printState( void ){
  Serial.print("Estado: {");
  for (int i = 0; i < unitsAmount; i++) {
    int ss = this->vec[i].getState();
    Serial.print(ss);
    if (i < unitsAmount - 1)
      Serial.print(", ");
  }
  Serial.println("}");
}

// FREDILlaves modifica el constructor
FREDILlaves::FREDILlaves(int _unitsAmount) : FREDILights(_unitsAmount){
  unitsAmount = _unitsAmount;
  for (int i = 0; i < _unitsAmount; i++) {
    this->vec.push_back(FREDILlave(i));
  }
}

// FREDIHoyos modifica el constructor
FREDIHoyos::FREDIHoyos(int _unitsAmount) : FREDILights(_unitsAmount){
  unitsAmount = _unitsAmount;
  for (int i = 0; i < _unitsAmount; i++) {
    this->vec.push_back(FREDIHoyo(i));
  }
}

/*
LightUnit Class
*/

LightUnit::LightUnit(int _id) :
    pwmFrequency(PWM_FREQ), maxBrightness(MAX_BRIGHTNESS){
  id = _id;
  state = 0;
  ledPins = (int *)malloc(sizeof(int)*3);
  for (int i = 0; i < 3; i++) {
    ledPins[i] = i + 3*_id;
  }
}

LightUnit::LightUnit(int _id, int _state) :
    pwmFrequency(PWM_FREQ), maxBrightness(MAX_BRIGHTNESS){
  id = _id;
  state = _state;
  ledPins = (int *)malloc(sizeof(int)*3);
  for (int i = 0; i < 3; i++) {
    ledPins[i] = i + 3*_id;
  }
}

void LightUnit::init(void){
  ShiftPWM.SetAmountOfRegisters(2);
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  ShiftPWM.SetAll(0);
}

void LightUnit::setState(int _state){
  /*
  if (_state > MAX_STATES - 1 || _state < MIN_STATES)
    _state = DEFAULT_ZERO_STATE;
    */
  state = _state;
  setLightState(_state);
}

int LightUnit::getState(){
  return state;
}

void LightUnit::setLightZeroState( void ){
  for (int i = 0; i < 3; i++) {
    ShiftPWM.SetOne(ledPins[i],0);
  }
}

void LightUnit::printInfo( void ){
  Serial.print("***** INFO AGUJERO ");
  Serial.print(id);
  Serial.println(" *****");
  Serial.println("LED PINS:");
  for (int i = 0; i < 3; i++) {
    Serial.print("  ");
    Serial.println(ledPins[i]);
  }
  Serial.println("");
}

/*
FREDIHoyo solo hace override al setting de luces
*/

void FREDIHoyo::setLightState(int _state){
  switch (_state) {
    case 0:
      setLightZeroState();
      break;
    case 1:
      setLightZeroState();
      ShiftPWM.SetOne(ledPins[2],maxBrightness);
      break;
    case 2:
      setLightZeroState();
      ShiftPWM.SetOne(ledPins[0],maxBrightness);
      break;
    case 3:
      setLightZeroState();
      ShiftPWM.SetOne(ledPins[1],maxBrightness);
      break;
    default:
      ShiftPWM.SetAll(0);
      break;
  }
}

/*
FREDILlave solo hace override al setting de luces
*/

void FREDILlave::setLightState(int _state){
  switch (_state) {
    case 0:
      setLightZeroState();
      break;
    case 1: //Esperando
      setLightZeroState();
      ShiftPWM.SetOne(ledPins[2],maxBrightness);
      break;
    case 2:
      setLightZeroState();
      ShiftPWM.SetOne(ledPins[0],180);
      ShiftPWM.SetOne(ledPins[1],240);
      ShiftPWM.SetOne(ledPins[2],80);
      break;
    case 3:
      setLightZeroState();
      ShiftPWM.SetOne(ledPins[0],120);
      ShiftPWM.SetOne(ledPins[1],255);
      ShiftPWM.SetOne(ledPins[2],70);
      break;
    case 4:
      setLightZeroState();
      ShiftPWM.SetOne(ledPins[1],maxBrightness);
      break;
    default:
      ShiftPWM.SetAll(0);
      break;
  }
}
