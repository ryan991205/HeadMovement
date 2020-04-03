




#include <Arduino.h>

#include <SoftwareSerial.h>

#include <TMC26XStepper.h>
#include <PololuMaestro.h>
#include <GPIO.h>

#include "IheadAxis.h"
#include "HeadAxis_StepperMotor.h"
#include "HeadAxis_ServoMotor.h"

//extern "C" void __cxa_pure_virtual(void);


// PIN DEFINE! warning this does not initialise pins. use GPIO_InitPinFromStruct() function for that.

// STEPPERMOTOR
GPIO TMC_CS_Pin     = {.DIR = OUTPUT, .PORT = PORT_D, .PIN = 7};
GPIO TMC_DIR_Pin    = {.DIR = OUTPUT, .PORT = PORT_D, .PIN = 6};
GPIO TMC_STEP_Pin   = {.DIR = OUTPUT, .PORT = PORT_D, .PIN = 5};

// SENSORS steppermotor
GPIO ENC1_PAN       = {.DIR = INPUT,  .PORT = PORT_D, .PIN = 2};
GPIO ENC2_PAN       = {.DIR = INPUT,  .PORT = PORT_D, .PIN = 3};
GPIO HALL1_PAN      = {.DIR = INPUT,  .PORT = PORT_B, .PIN = 0};
GPIO HALL2_PAN      = {.DIR = INPUT,  .PORT = PORT_B, .PIN = 1};

// UART interface pins servomotors
GPIO mcu_TX         = {.DIR = OUTPUT, .PORT = PORT_D, .PIN = 4};
GPIO mcu_RX         = {.DIR = INPUT,  .PORT = PORT_C, .PIN = 5};
SoftwareSerial ServoCommunicator = SoftwareSerial(GPIO_getArduinoPin(&mcu_RX),GPIO_getArduinoPin(&mcu_TX));

 // Motors
HeadAxis_StepperMotor   PanMotor  = HeadAxis_StepperMotor(TMC_CS_Pin,TMC_DIR_Pin,TMC_STEP_Pin);
HeadAxis_ServoMotor     TiltMotor = HeadAxis_ServoMotor(ServoCommunicator, 9600, 0);
HeadAxis_ServoMotor     RollMotor = HeadAxis_ServoMotor(ServoCommunicator, 9600, 1);

IHeadAxis *motor = &PanMotor;

void setup()
{
  
  delay(5);

}



void loop() 
{

}