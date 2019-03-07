#include "SolderingMachine.h"

SolderingMachine MESASolderingMachine(2, 1, 3 , 4 , 5 , 6, 7, 8, 9 , 10, 11, 12, 13, 14 , 15 , 22 , 17 , 18 , 19 , 20 , 21);

void setup() {
  Serial.begin(9600);
  //delay(1000);
  MESASolderingMachine.boot();
  MESASolderingMachine.initAll();
}

void loop() {
  // put your main code here, to run repeatedly:

}
