/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "SolderingMachine.h"

SolderingMachine::SolderingMachine(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}
