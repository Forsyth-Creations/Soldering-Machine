/*
  SolderingMachine.cpp - Library for running MESA Soldering Iron
  Created by Robert Forsyth, March 4, 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "SolderingMachine.h"
#include <Encoder.h>
#include <Stepper.h>
#include <Servo.h>
//This Library makes use of https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library for the I2C backpack
//You will need to download it to make use of the functionality
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//----------------- Declaring all Necessary Objects Here -------------------------
// ****************** ISSUE HERE *********************************
LiquidCrystal_I2C lcd(0x27, 20, 4);
Stepper stepperA(60,_stepperMotorPinA[0], _stepperMotorPinA[1], _stepperMotorPinA[2], _stepperMotorPinA[3]);
Stepper stepperB(60,_stepperMotorPinB[0], _stepperMotorPinB[1], _stepperMotorPinB[2], _stepperMotorPinB[3]);
Stepper stepperC(60,_stepperMotorPinC[0], _stepperMotorPinC[1], _stepperMotorPinC[2], _stepperMotorPinC[3]);
Servo solderServo;

//--------------------------------------------------------------------------------

SolderingMachine::SolderingMachine(int stepperMotorPinA1, int stepperMotorPinA2, int stepperMotorPinA3, int stepperMotorPinA4, int stepperMotorPinB1, int stepperMotorPinB2, int stepperMotorPinB3, int stepperMotorPinB4, int stepperMotorPinC1, int stepperMotorPinC2, int stepperMotorPinC3, int stepperMotorPinC4, int servoMotorPin, int solderingInitButton, int menuRotar1, int menuRotar2, int lcdSDA, int lcdSCl, int limiterA, int limiterB, int limiterC) {
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
  copyArray(allPins, _allPins, numberOfPinsUsed); //copies array into global variable
  createArray(0, 4,  _stepperMotorPinA);
  createArray(4, 4,  _stepperMotorPinB);
  createArray(8, 4,  _stepperMotorPinC);
  createArray(18, 3,  _limitSwitches);
  _solderServoPin = _allPins[12];
}

void SolderingMachine::initAll() {
  initLCD();
  initServo();
  initStepper('A');
  initStepper('B');
  initStepper('C');
}

void SolderingMachine::initLCD() {
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" St.Martin     ");
  lcd.setCursor(0, 1);
  lcd.print(" Soldering Station: ");
  lcd.setCursor(0, 2);
  lcd.print(" Designed and Built ");
  lcd.setCursor(0, 3);
  lcd.print(" By: Robert Forsyth ");
}

void SolderingMachine::initServo() {
  Serial.println("------- Resetting Solder Position ----------");
  solderServo.write(180);
  delay(2000);
  solderServo.write(90);
  Serial.println("-------- Solder Reset Complete ------------");
}

void SolderingMachine::initStepper(char whichStepper) { //initializes one stepper motor using limiter switch
  int pins[4];
  int limitSwitch;
  int startingValue = 0;
  switch (whichStepper) {
    case 'A':
      Serial.println("----- A Stepper -----");
      copyArray(_stepperMotorPinA, pins, 4);
      limitSwitch = _limitSwitches[0];
      stepperCalibrate(stepperA, limitSwitch);
      break;
    case 'B':
      Serial.println("----- B Stepper -----");
      copyArray(_stepperMotorPinB, pins, 4);
      limitSwitch = _limitSwitches[1];
      stepperCalibrate(stepperB, limitSwitch);
      break;
    case 'C':
      Serial.println("----- C Stepper -----");
      copyArray(_stepperMotorPinC, pins, 4);
      limitSwitch = _limitSwitches[2];
      stepperCalibrate(stepperC, limitSwitch);
      break;
  }
  Serial.println("Pins used for this component: ");
  Serial.println(pins[0]);
  Serial.println(pins[1]);
  Serial.println(pins[2]);
  Serial.println(pins[3]);

  Serial.print("Limit swtich used for this operation was: ");
  Serial.println(limitSwitch);
}

void SolderingMachine::boot() {
  Serial.println("Welcome to the Soldering Machine Interface");
  //delay(2000);
  Serial.println("Beginning Boot Now");
  //delay(2000);
  solderServo.attach(_solderServoPin);
  listAllPins();

}

void SolderingMachine::listAllPins() {
  for (int i = 0; i <= numberOfPinsUsed - 1 ; i++) {
    if (false) { //All Pins Used as Inputs Should Be Listed Here. Note that an array indexes starting at 0, so the '+1' is to offset this (i + 1 == 3 || i + 1 == 4 || i + 1 == 5)
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

void SolderingMachine::createArray(int startingVal, int arrayLength, int* destination) { //You need to feed this function the starting index, the amount of successive terms you want from the _allPins array, and the destination of the new pins
  //Serial.println("Starting to Make Array");
  for (int i = 0; i <= arrayLength - 1; i++) {
    destination[i] = _allPins[startingVal + i];
  }
}

boolean SolderingMachine::stepperCalibrate (Stepper &stepperToInit, int limitSwitchValue) {
  //Calibrartion Code for a Stepper Motor. Aborts after 10 seconds if no position is reached
  //Returns a false of false if the calibration fails

  stepperToInit.setSpeed(70);
  Serial.println("initializing steppper");
  long timeCheck = millis();
  while ((digitalRead(limitSwitchValue) == 0 && (timeCheck + 4000) > millis()) && digitalRead(limitSwitchValue) == LOW) {
    //Serial.println(digitalRead(-limitSwitchValue));
    stepperToInit.setSpeed(45);
    stepperToInit.step(-20);
    delay(20);
  }
  //delay(1000);
  if (digitalRead(limitSwitchValue) == 1) {
    Serial.println("Stepper Motor for Bow Calibrated");
    stepperToInit.setSpeed(15);
    stepperToInit.step(20);
    return true;
  }
  else {
    Serial.println("Calibration Failed. Check hardware, then restart program");
    return false;
  }

}
