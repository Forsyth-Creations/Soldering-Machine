#include "SolderingMachine.h"

SolderingMachine MESASolderingMachine(11, 10, 9 , 8 , 7 , 6, 7, 8, 9 , 10, 11, 12, 22, 14 , 15 , 22 , 17 , 18 , 19 , 20 , 21);

void setup() {
  Serial.begin(9600);
  //delay(1000);
  MESASolderingMachine.initAll();
  MESASolderingMachine.boot();
}

void loop() {
  // put your main code here, to run repeatedly:

}
