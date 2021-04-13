#include "em.h"

EnergyMonitor emon1;

void setup(){
  Serial.begin(115200);
  
  emon1.setPin(32);
}

void loop(){
  double Irms1 = emon1.calcIrms(9000);
  
  Serial.println("Irms1:" + String(Irms1));
  delay(1000);
}
