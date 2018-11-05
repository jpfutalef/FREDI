#include <FrediLib.h>
 
//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10
 
FrediRx frediRx = FrediRx(CE_PIN, CSN_PIN);

void setup()
{
  Serial.begin(9600); 
  frediRx.begin();
  delay(200);
}
 
void loop() {
 uint8_t numero_canal;
 //if ( radio.available(&numero_canal) )
 if(frediRx.available()){    
     frediRx.read();
     frediRx.printData();
 }else{
     //Serial.println("No hay datos de radio disponibles");
 }
 delay(250);
}
