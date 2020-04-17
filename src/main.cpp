#include <Arduino.h>
#include <SoftwareSerial.h>

#include <TMC26XStepper.h>
#include <PololuMaestro.h>
#include <GPIO.h>

#include "IHeadAxis.h"
#include "HeadAxis_StepperMotor.h"
#include "HeadAxis_ServoMotor.h"
#include "HeadControl.h"
#include "Communicator.h"


// MAPPING Motors:
///         | degrees min | degrees center | degrees max |  | realVal min | realVal center | realVal max
///         | ------------|----------------|-------------|--|-------------|----------------|-------------
///    PAN  | -90         | 0              | +90         |><| 0           |                | 70800+-     (val in Steps /32e)
///    TILT | +55         | 0              | -10         |><| 1300/5200   | 1850/7400      | 2000/8000   (val in uS)/(val in programUnits)
///    ROLL | -45         | 0              | +45         |><| 1248/5000   | 1645/6580      | 2000/8000   (val in uS)/(val in programUnits)
///
// motor calibration:            Degrees  , program units   
CalibrationSet PanCalibration =  {  {-90  , 0      },      //min     (auto calibration)
                                    {0    , 0      },      //center  (auto calibration)
                                    {90   , 0      }};     //max     (auto calibration)
CalibrationSet TiltCalibration = {  {-10  , 8000   },      //min     
                                    {0    , 7400   },      //center
                                    {55   , 5200   }};     //max
CalibrationSet RollCalibration = {  {-45  , 5000   },      //min
                                    {0    , 6580   },      //center
                                    {45   , 8000   }};     //max
// End of motor mapping.


// PIN DEFINE! warning this does not initialise pins. use GPIO_InitPinFromStruct() function for that.
// control pins steppermotor 
GPIO TMC_CS_Pin     = {.DIR = OUTPUT, .PORT = PORT_D, .PIN = 7};
GPIO TMC_DIR_Pin    = {.DIR = OUTPUT, .PORT = PORT_D, .PIN = 6};
GPIO TMC_STEP_Pin   = {.DIR = OUTPUT, .PORT = PORT_D, .PIN = 5};

// SENSORS steppermotor
GPIO ENC1_PAN       = {.DIR = INPUT,  .PORT = PORT_D, .PIN = 2}; // not used at the moment.
GPIO ENC2_PAN       = {.DIR = INPUT,  .PORT = PORT_D, .PIN = 3}; // not used at the moment.
GPIO HALL1_PAN      = {.DIR = INPUT,  .PORT = PORT_B, .PIN = 0};
GPIO HALL2_PAN      = {.DIR = INPUT,  .PORT = PORT_B, .PIN = 1};

// UART interface pins servomotors and library instance of the controller.
GPIO mcu_TX         = {.DIR = OUTPUT, .PORT = PORT_D, .PIN = 4};
GPIO mcu_RX         = {.DIR = INPUT,  .PORT = PORT_C, .PIN = 5};
SoftwareSerial ServoCommunicator(GPIO_getArduinoPin(&mcu_RX),GPIO_getArduinoPin(&mcu_TX));
MicroMaestro ServoController(ServoCommunicator);

// Motors
HeadAxis_StepperMotor   PanMotor;
HeadAxis_ServoMotor     TiltMotor;
HeadAxis_ServoMotor     RollMotor;

// abstract Motor pointers
IHeadAxis *PanHandler    = &PanMotor;
IHeadAxis *TiltHandler   = &TiltMotor;
IHeadAxis *RollHandler   = &RollMotor;

// Headcontroller (main system)
HeadControl Head;


// ADD all Motor Update functions here
ISR(TIMER1_COMPA_vect)
{
   PanMotor.Update();
   TiltMotor.Update();
   RollMotor.Update();
}

// Initialisation
void setup()
{
   ServoCommunicator.begin(9600);
   Serial.begin(9600);
   delay(10);

   // Setting up Motors
   PanMotor  = HeadAxis_StepperMotor(&TMC_CS_Pin, &TMC_DIR_Pin, &TMC_STEP_Pin, &HALL1_PAN, &HALL2_PAN, 120);
   TiltMotor = HeadAxis_ServoMotor(&ServoController, 1, &TiltCalibration);
   RollMotor = HeadAxis_ServoMotor(&ServoController, 0, &RollCalibration);

   // Starting and initialising/calibrate a stepperMotor
   PanMotor.Calibrate();
   HeadAxis_StepperMotor::StartAutoUpdater();

   //init HeadController
   Head = HeadControl(PanHandler , TiltHandler , RollHandler);

 Serial.println("# initComplete");
 delay(10);
}



void loop() 
{
   PanMotor.Move(0);

   RollMotor.Move(0);
  // TiltMotor.Move(00);
   delay(2000);
   //RollMotor.Move(-25);
   //TiltMotor.Move(45);
   delay(1000);

/*
if(GPIO_PinRead(&HALL1_PAN) == LOW)
{   
   Serial.println("H1_LOW");
}
if(GPIO_PinRead(&HALL2_PAN) == LOW)
{
   
   Serial.println("H2_LOW");
}
delay(100);
*/


 //GPIO_PinWrite(&TMC_STEP_Pin,HIGH);
 //delay(1);
// GPIO_PinWrite(&TMC_STEP_Pin,LOW);
 //delay(1);


 // delay(1000);
 // PanMotor.Move(400);
 // while(1)
 // {
 //PanMotor.Update();
 // }

}