#include <Arduino.h>
#include <Encoder4Mot.h>
#include <BlocMoteurs.h>
#include <Reglages.h>


int loopRate_ms = 10;
uint32_t time_ms = 0;
Encoder4Mot encoder;


void setup() {
  /* Initialize Serial */
  Serial.begin(115200);
  while (!Serial) yield();
  time_ms = millis();


}

void loop() {
  if(millis() > time_ms + loopRate_ms)
  {

  }
}
