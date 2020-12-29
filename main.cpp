
#include <Arduino.h>
#include "TorchHeight.h"
#include "WifiAddon.h"


// the setup function runs once when you press reset or power the board
void setup()
{
  // Initialize digital pin LED_BUILTIN as an output.
  //This is used to enable the MKS driver board. Plus it flashes and flashes are cool.
  pinMode(LED_BUILTIN, OUTPUT);

  // Begin the object with a baud rate of 9600
  THCNex.begin();  // If no parameter was given in the begin(), the default baud rate of 9600 will be used
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //initialize the variables we're linked to
  // Load EEPROM Addresses for Setpoints or set defaults
  SetpointPage1 = EEPROM.readInt(addressPage1);
  if (SetpointPage1 == 0) {
    SetpointPage1 = defaultSetpoint;
  }

  SetpointPage2 = EEPROM.readInt(addressPage2);
  if (SetpointPage2 == 0) {
    SetpointPage2 = defaultSetpoint;
  }

  SetpointPage3 = EEPROM.readInt(addressPage3);
  if (SetpointPage3 == 0) {
    SetpointPage3 = defaultSetpoint;
  }

  SetpointPage4 = EEPROM.readInt(addressPage4);
  if (SetpointPage4 == 0) {
    SetpointPage4 = defaultSetpoint;
  }

  SetpointPage5 = EEPROM.readInt(addressPage5);
  if (SetpointPage5 == 0) {
    SetpointPage5 = defaultSetpoint;
  }

  SetpointPage6 = EEPROM.readInt(addressPage6);
  if (SetpointPage6 == 0) {
    SetpointPage6 = defaultSetpoint;
  }

  scale = EEPROM.readDouble(addressScale);
  if (scale == 0) {
    scale = 1;
  }

  gap = EEPROM.readInt(addressGap);
  if (gap == 0) {
    gap = 500;
  }

  threshold = EEPROM.readInt(addressThreshold);
  if (threshold == 0) {
    threshold = 4000;
  }

  arcStabilizeDelay = EEPROM.readInt(addressDelay);
  if (arcStabilizeDelay == 0) {
    arcStabilizeDelay = 150;
  }

  steps_per_mm = EEPROM.readInt(addressSteps);
  if (steps_per_mm == 0) {
    steps_per_mm = 200;
  }

  maxPos = EEPROM.readInt(addressMaxpos);
  if (maxPos == 0) {
    maxPos = 40 * steps_per_mm;
  }

  minPos = EEPROM.readInt(addressMinpos);
  if (minPos == 0) {
    minPos = -(40 * steps_per_mm);
  }

  aggKp = EEPROM.readFloat(addressAP);
  if (aggKp == 0) {
    aggKp = 0.175;
  }

  aggKi = EEPROM.readFloat(addressAI);
  if (aggKi == 0) {
    aggKi = 0.1;
  }

  aggKd = EEPROM.readFloat(addressAD);
  if (aggKd == 0) {
    aggKd = 0.1;
  }

  Kp = EEPROM.readFloat(addressCP);
  if (Kp == 0) {
    Kp = 0.075;
  }

  Ki = EEPROM.readFloat(addressCI);
  if (Ki == 0) {
    Ki = 0.01;
  }

  Kd = EEPROM.readFloat(addressCD);
  if (Kd == 0) {
    Kd = 0.01;
  }

  CalibrationOffset = EEPROM.readInt(addressCalibrate);
  if (CalibrationOffset == 0) {
    CalibrationOffset = 0;
  }

  // Wait for Nextion Screen to bootup
  delay(2500);
  THCNex.writeNum("CustomSetPoint.val", SetpointPage1);
  THCNex.writeNum("CustomSetPoint.val", SetpointPage1); //Make sure it set
  THCNex.writeNum("CustomSetPoint.val", SetpointPage1); //One more time
  SetPoint = SetpointPage1;

  //Setup Stepper Driver
  stepper.setMaxSpeed(1500000); //thru experimentation I found these values to work... Change for your setup.
  stepper.setAcceleration(200000);
  //Enable MKS Driver Board
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}


// the loop function runs over and over again forever
void loop()
{
  THCNex.NextionListen();
  Input = map(analogRead(PLASMA_INPUT_PIN), 0, 1023, 0, 25000) + CalibrationOffset; //reads plasma arc voltage and convert to millivolt
  process(); //This is the main method of the application it calulates position and move steps if Input Voltage is over threshold.
  if (CurrentPageNumber <= 6 || CurrentPageNumber == 11) {
    report();
  }
  //wifi addon...
  loop_wifi();
 }

}
