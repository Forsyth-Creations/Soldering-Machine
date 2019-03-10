/*
  SolderingMachine.h - Library for running MESA Soldering Iron
  Created by Robert Forsyth, March 4, 2019.
  Released into the public domain.
*/
#ifndef SolderingMachine_h
#define SolderingMachine_h

#include "Arduino.h"
//INCLUDE OTHER LIBRARIES HERE
//#include <LiquidCrystal.h>
#include <Encoder.h>
#include <Stepper.h>
//This Library makes use of https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library for the I2C backpack
//You will need to download it to make use of the functionality
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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
    void boot();
    int _stepperMotorPinA[4];
    int _stepperMotorPinB[4];
    int _stepperMotorPinC[4];
  private:
    int servoPin[2];
    int limitSwitches[3];
    int numberOfPinsUsed = 21;
    int _allPins[21]; //remember to change both values, since the compiler doesn't like having these intermingle
    void listAllPins();
    int _limitSwitches[3];
    void copyArray(int* src, int* dst, int len);
    void createArray(int startingVal, int arrayLength, int* destination);
    boolean stepperCalibrate(Stepper &stepperToInit, int limitSwitchValue);
    int _solderServoPin;
    void initObjects();

};

//----------------- Declaring all Necessary Objects Here -------------------------

#endif
