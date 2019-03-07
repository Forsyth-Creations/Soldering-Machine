/*
  SolderingMachine.cpp - Library for running MESA Soldering Iron
  Created by Robert Forsyth, March 4, 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "SolderingMachine.h"

SolderingMachine::SolderingMachine(int stepperMotorPinA1, int stepperMotorPinA2, int stepperMotorPinA3, int stepperMotorPinA4, int stepperMotorPinB1, int stepperMotorPinB2, int stepperMotorPinB3, int stepperMotorPinB4, int stepperMotorPinC1, int stepperMotorPinC2, int stepperMotorPinC3, int stepperMotorPinC4, int servoMotorPin, int solderingInitButton, int menuRotar1, int menuRotar2, int lcdSDA, int lcdSCl, int limiterA, int limiterB, int limiterC)
{
  /*
     This is the constructor for our soldering iron machine. The data you need to feed it is as follows:
     The first four numbers should be the four pins used for stepper motor A
     The next four numbers should be the four pins used for stepper motor B
     The next four numbers should be the four pins used for stepper motor C
     The next number should be the pin used for your servo motor
     The next number should be the pin used for the soldering iron z level init button
     The next two number should be the pins used for the menu rotar
     The next two number should be the pins used for the LCD's SDA and SCL pins (USING AN I2C Module)
     The next three numbers should be the limiter switches for the stepper motors (A, B, and C in that order)

     Current Total Pins = 21
  */
  int allPins[numberOfPinsUsed] = {stepperMotorPinA1, stepperMotorPinA2, stepperMotorPinA3, stepperMotorPinA4, stepperMotorPinB1, stepperMotorPinB2, stepperMotorPinB3, stepperMotorPinB4, stepperMotorPinC1, stepperMotorPinC2, stepperMotorPinC3, stepperMotorPinC4, servoMotorPin, solderingInitButton, menuRotar1, menuRotar2, lcdSDA, lcdSCl, limiterA, limiterB, limiterC};
  memcpy(_allPins, allPins, sizeof(allPins[0])*numberOfPinsUsed); //copies array into global variable
}

void SolderingMachine::initAll() {
  initLCD();
  initServo();
  initStepper('A');
  initStepper('B');
  initStepper('C');
}

void SolderingMachine::initLCD() {

}

void SolderingMachine::initServo() {

}

void SolderingMachine::initStepper(char whichStepper) { //initializes one stepper motor using limiter switch
  int pins[4];
  int limitSwitch;
  int startingValue = 0;
  switch (whichStepper) {
    case 'A':
      startingValue = 4;
      Serial.println("A");
      //memcpy(pins, _allPins, sizeof(_allPins[0]) * 4); //copies global variable values into pin value
      limitSwitch = _limitSwitches[1];
      break;
    case 'B':
      startingValue = 8;
      Serial.println("B");
      //memcpy(pins, _allPins, (sizeof(_allPins[0]) * 4) + 1); //copies global variable values into pin value
      limitSwitch = _limitSwitches[2];
      break;
    case 'C':
      startingValue = 3;
      createArray(startingValue, 4, pins[0]);
      Serial.println("C");
      limitSwitch = _limitSwitches[3];
      break;
  }
  Serial.println(pins[0]);
  Serial.println(pins[1]);
  Serial.println(pins[2]);
  Serial.println(pins[3]);
}

void SolderingMachine::boot() {
  Serial.println("Welcome to the Soldering Machine Interface");
  //delay(2000);
  Serial.println("Beginning Boot Now");
  //delay(2000);
  listAllPins();
}

void SolderingMachine::listAllPins() {
  for (int i = 0; i <= numberOfPinsUsed - 1 ; i++) {
    if (i + 1 == 3 || i + 1 == 4 || i + 1 == 5) { //All Pins Used as Inputs Should Be Listed Here. Note that an array indexes starting at 0, so the '+1' is to offset this
      pinMode(_allPins[i], INPUT);
      Serial.print("Input Pin Init: ");
      Serial.println(_allPins[i]);
    }
    else { //All Pins Used As Outputs
      pinMode(_allPins[i], OUTPUT);
      digitalWrite(_allPins[i], LOW);
      Serial.print("Output Pin Init: ");
      Serial.println(_allPins[i]);
    }
  }
}

void SolderingMachine::copyArray(int* src, int* dst, int len) {
  memcpy(dst, src, sizeof(src[0])*len);
}

void SolderingMachine::createArray(int startingVal, int arrayLength, int* destination[]) { //You need to feed this function the starting index, the amount of successive terms you want from the _allPins array, and the destination of the new pins
  Serial.println("Starting to Make Array");
  for (int i = startingVal; i <= startingVal + arrayLength; i++) {
    destination[i] = _allPins[i];
    //Serial.println(_allPins[i]);
  }
}

