#include <Arduino.h>
#include <BlocMoteurs.h>
#include "Encoder4Mot.h"
#include <Reglages.h>



int loopRate_ms = 10;
uint32_t time_ms = 0;
// Encoder4Mot* encoder;
// BlocMoteurs* mot;
// //SpeedPIDController* contr;
Encoder* enco;





void setup() {
  /* Initialize Serial */
  // encoder = new Encoder4Mot();
  Serial.begin(115200);
  while (!Serial) yield();
  enco = new Encoder(PC_1,PC_0,motorPlacement::BG,false);
  
  



}

void loop() {
  enco->update();
  std::cout << "Enco Count : "<< enco->getCount() << " Enco ellTick " << enco->getEllapsedTick() << " Enco speed : "<< enco->getSpeed() << std::endl; 

  
  delay(100);
}
