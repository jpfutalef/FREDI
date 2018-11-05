#include <FrediLib.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;

// MOSI 11
// MISO 12
// SCK 13

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10

#define latchPin 8 //Pin connected to latch pin (ST_CP) of 74HC595 -> 12
#define clockPin 6 //Pin connected to clock pin (SH_CP) of 74HC595 -> 11
#define dataPin 7 //Pin connected to Data in (DS) of 74HC595 -> 14
#define connected_leds 6

Bateria bateria = Bateria(latchPin, clockPin, dataPin, connected_leds);
FrediTx frediTx = FrediTx(CE_PIN, CSN_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("reset");
  ina219.begin();
  frediTx.begin();
  delay(200);
}

int i;
float bat_voltage;
void loop() {
  bat_voltage = ina219.getBusVoltage_V();
  bat_voltage = 3.9;
  i = bateria.showLevel(bat_voltage);
  Serial.print("v : ");Serial.print(bat_voltage);Serial.print("\t i : ");Serial.println(i);
  
  //enviamos los datos
  bool ok = frediTx.send();
  //reportamos por el puerto serial los datos enviados
  if(ok) frediTx.printData();
  else Serial.println("no se ha podido enviar");
  
  delay(500);
  //Serial.println();
}
