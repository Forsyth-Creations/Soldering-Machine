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

     Current Total Pins = 22
  */
  int allPins[numberOfPinsUsed] = {stepperMotorPinA1, stepperMotorPinA2, stepperMotorPinA3, stepperMotorPinA4, stepperMotorPinB1, stepperMotorPinB2, stepperMotorPinB3, stepperMotorPinB4, stepperMotorPinC1, stepperMotorPinC2, stepperMotorPinC3, stepperMotorPinC4, servoMotorPin, solderingInitButton, menuRotar1, menuRotar2, lcdSDA, lcdSCl, limiterA, limiterB, limiterC};
  Serial.begin(9600);
  for (int i = 0; i <= numberOfPinsUsed + 2; i++) {
    if (i == 3 || i == 4 || i == 5) { //All Pins Used as Inputs Should Be Listed Here
      pinMode(allPins[i], INPUT);
      Serial.print("Input Pin Init: ");
      Serial.println(allPins[i]);
    }
    else { //All Pins Used As Outputs
      pinMode(allPins[i], OUTPUT);
      digitalWrite(allPins[i], LOW);
      Serial.print("Output Pin Init: ");
      Serial.println(allPins[i]);
    }
  }
}

void SolderingMachine::initAll() {

}

void SolderingMachine::initLCD() {

}

void SolderingMachine::initServo() {

}

void SolderingMachine::initStepper(char whichStepper) {
  int pins[4];
  int limitSwitch;
  switch (whichStepper) {
    case 'A':
      pins[4] = stepperMotorPinA[4];
      limitSwitch = limitSwitches[1];
      break;
    case 'B':
      pins[4] = stepperMotorPinB[4];
      limitSwitch = limitSwitches[2];
      break;
    case 'C':
      pins[4] = stepperMotorPinC[4];
      limitSwitch = limitSwitches[3];
      break;
  }
}

