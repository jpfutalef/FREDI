#include "FREDILights.h"
#include <ShiftPWM.h>
#include <Arduino.h>
#include <ArduinoSTL.h>
#include <vector>

FREDIHoles::FREDIHoles(int _holesAmount) :
    holesAmount(_holesAmount){
  for (int i = 0; i < _holesAmount; i++) {
    holesVec.push_back(FREDIHole(i));
  }
}

void FREDIHoles::init(void){
  holesVec[0].init();
  return;
}

void FREDIHoles::setState(int _hole, int _state){
  // int _hole: agujero a modificar, de 0 a holesAmount-1
  // int _state: estado a asignar al agujero
  if (_hole >= holesAmount)
    return;
  holesVec[_hole].setState(_state);
}

void FREDIHoles::setState(int _state[]){
  // int _state[]: array con ints, donde cada uno es el estado de un agujero
  /*
  int givenSize = sizeof(_state)/sizeof(_state[0]);
  Serial.print("Given size: ");
  Serial.println(_state);
  if (givenSize != holesAmount)
    return;
  */
  for (int i = 0; i < holesAmount; i++) {
    setState(i, _state[i]);
  }
}


void FREDIHoles::printState( void ){
  Serial.print("Estado: {");
  for (int i = 0; i < holesAmount; i++) {
    int ss = holesVec[i].getState();
    Serial.print(ss);
    if (i < holesAmount - 1)
      Serial.print(", ");
  }
  Serial.println("}");
}


/*
FREDI HOLE Class
*/

FREDIHole::FREDIHole(int _id) :
    pwmFrequency(PWM_FREQ), maxBrightness(MAX_BRIGHTNESS){
  id = _id;
  state = 0;
  ledPins = (int *)malloc(sizeof(int)*3);
  for (int i = 0; i < 3; i++) {
    ledPins[i] = i + 3*_id;
  }
}

FREDIHole::FREDIHole(int _id, int _state) :
    pwmFrequency(PWM_FREQ), maxBrightness(MAX_BRIGHTNESS){
  id = _id;
  state = _state;
  ledPins = (int *)malloc(sizeof(int)*3);
  for (int i = 0; i < 3; i++) {
    ledPins[i] = i + 3*_id;
  }
}

void FREDIHole::init(void){
  ShiftPWM.SetAmountOfRegisters(2);
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  ShiftPWM.SetAll(0);
}

void FREDIHole::setState(int _state){
  if (_state > MAX_STATES - 1 || _state < MIN_STATES)
    _state = DEFAULT_ZERO_STATE;
  state = _state;
  setLightState(_state);
}

int FREDIHole::getState(){
  return state;
}

void FREDIHole::setLightState(int _state){
  switch (_state) {
    case 0:
      setLightZeroState();
      break;
    case 1:
      setLightZeroState();
      ShiftPWM.SetOne(ledPins[0],maxBrightness);
      break;
    case 2:
      setLightZeroState();
      ShiftPWM.SetOne(ledPins[1],maxBrightness);
      break;
    case 3:
      setLightZeroState();
      ShiftPWM.SetOne(ledPins[2],maxBrightness);
      break;
    default:
      ShiftPWM.SetAll(0);
      break;
  }
}

void FREDIHole::setLightZeroState( void ){
  for (int i = 0; i < 3; i++) {
    ShiftPWM.SetOne(ledPins[i],0);
  }
}

void FREDIHole::printInfo( void ){
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
