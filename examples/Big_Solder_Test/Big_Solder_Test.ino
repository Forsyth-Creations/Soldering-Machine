#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>
#include <Stepper.h>
#include "menuOptions.h"

//-------------- All Int -----------------------------
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
long oldPosition  = -999;
int howManyRevolutions = 3;
int absoluteXPos = 0;
int absoluteYPos = 0;
int absoluteZPos = 0;
const int stepperRangeX = 0; //Measured in steps
const int stepperRangeY = 0; //Measured in steps
const int stepperRangeZ = 0; //Measured in steps
//------------- Pin Definitions --------------------------
#define encoderButtonPin 4
#define encoder1 6
#define encoder2 5
const int xButton = 4;
const int yButton = 3;
const int zButton = 2;
//------------- Objects --------------------------
LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD address to 0x27 for a 20 chars and 4 line display
Encoder myEnc(encoder1, encoder2);
//------------- Initialize Stepper Motors ------------
Stepper zAxis(stepsPerRevolution, 52, 51, 50, 49);
Stepper xAxis(stepsPerRevolution, 48, 47, 46, 45);
Stepper yAxis(stepsPerRevolution, 44, 43, 42, 41);

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  initLCD();
}

void loop()
{
  runStepperMotorTest();
}

void readEncoder() {
  long newPosition = myEnc.read() / 4;
  Serial.println(newPosition);
}

void printMenu(char* inputArray[], int menuLength) {
  for (int i = 0; i <= 3; i++) {
    //int x = ((rotarRead + i) % menuLength);
    lcd.setCursor(2, i);
    lcd.print(inputArray[i]);
  }
  //whereInMenu = ((rotarRead) % menuLength);
}

void moveCursor(int y) {
  lcd.setCursor(0, y);
  lcd.print("->");
}

void runStepperMotorTest() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  yAxis.step(stepsPerRevolution * howManyRevolutions);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  yAxis.step(-stepsPerRevolution * howManyRevolutions);
  delay(500);
}

void initLCD() {
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("--------------------");
  lcd.setCursor(0, 1);
  lcd.print("     Soldering");
  lcd.setCursor(0, 2);
  lcd.print("      Station ");
  lcd.setCursor(0, 3);
  lcd.print("--------------------");
  delay(2000);
  //lcd.clear();
  delay(1000);
}

void moveSteppers(Stepper &theStepper, int movementDelta, int stepperSpeed, int absStore, int stepperRange) {
  //This is a function intended to run the stepper motor, and log the position in the global scope. Here is
  //what each variable does:
  //stepper pointer (self explanitory)
  //movementDelta is a value for which the stepper motor will be moved (measured in steps)
  //int stepperSpeed sets the stepper speed
  //int absStore is the value where the asssumed true value of the stepper is stored
  //The stepper range is the length of the lead screw per axis, measured in steps

  theStepper.setSpeed(stepperSpeed);
  int proposedNewPosition = absStore + movementDelta;
  if (proposedNewPosition > stepperRange) {
    Serial.println("Cannot reach position requested. Moving to range limit. Error Code 001");
    theStepper.step(movementDelta - abs(stepperRange - proposedNewPosition));

  }
  if (proposedNewPosition < 0) {
    Serial.println("Cannot reach position requested. Moving to range limit. Error Code 002");
    theStepper.step(movementDelta + abs(0 - proposedNewPosition));
  }
  Serial.println("Position Reached");
}

void initStepper(Stepper &theStepper, int movementDirection, int buttonPin) {
  /*
   * Stepper Pointer
   * -1 or 1
   * Button Pin From Global Scope
   */
  int startTime = millis();
  while (digitalRead(buttonPin) == LOW ) {
    theStepper.step(movementDirection);
    if (startTime + 10000 == millis()) {
      break;
      Serial.println("Stepper Calibration Failed. Error Code 004");
    }
  }
  Serial.println("Stepper Calibration Successful!");
  theStepper.step(-stepsPerRevolution * movementDirection);
}

