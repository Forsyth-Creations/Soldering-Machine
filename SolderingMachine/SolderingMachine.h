/*
  SolderingMachine.h - Library for running MESA Soldering Iron
  Created by Robert Forsyth, March 4, 2019.
  Released into the public domain.
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class SolderingMachine
{
  public:
    SolderingMachine(int stepperMotorPinA1, int stepperMotorPinA2, int stepperMotorPinA3, int stepperMotorPinA4,
                     int stepperMotorPinB1, int stepperMotorPinB2, int stepperMotorPinB3, int stepperMotorPinB4,
                     int stepperMotorPinC1, int stepperMotorPinC2, int stepperMotorPinC3, int stepperMotorPinC4,
                     int servoMotorPin, int solderingInitButton, int menuRotar1, int menuRotar2,
                     int lcdSDA, int lcdSCl, int limiterA, int limiterB, int limiterC);

    void initAll();
    void initLCD();
    void initStepper(char whichStepper);
    void initServo();
  private:
    int stepperMotorPinA[4];
    int stepperMotorPinB[4];
    int stepperMotorPinC[4];
    int servoPin[2];
    int limitSwitches[3];
    const int numberOfPinsUsed = 21;
};

#endif
