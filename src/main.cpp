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
///    PAN  | -177        | 0              | +177        |><| 0           |                | 70800+-     (val in Steps /32e)
///    TILT | +55         | 0              | -10         |><| 1300/5200   | 1850/7400      | 2000/8000   (val in uS)/(val in programUnits)
///    ROLL | -45         | 0              | +45         |><| 1248/5000   | 1645/6580      | 2000/8000   (val in uS)/(val in programUnits)
///
// motor calibration:            Degrees  , program units   
CalibrationSet PanCalibration =  {  {-177  , 0     },      //min     (auto calibration)
                                    {0    , 0      },      //center  (auto calibration)
                                    {177   , 0     }};     //max     (auto calibration)
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

// Communication Protocol / Main controller
Communicator COM; 


// ADD all stepper motors update functions here 
ISR(TIMER1_COMPA_vect)
{
   PanMotor.Update();
}

// Initialisation
void setup()
{
   ServoCommunicator.begin(9600);
   delay(10);

   // Setting up Motors
   PanMotor  = HeadAxis_StepperMotor(&TMC_CS_Pin, &TMC_DIR_Pin, &TMC_STEP_Pin, &HALL1_PAN, &HALL2_PAN, 100, &PanCalibration);
   TiltMotor = HeadAxis_ServoMotor(&ServoController, 1, &TiltCalibration);
   RollMotor = HeadAxis_ServoMotor(&ServoController, 0, &RollCalibration);

   HeadAxis_StepperMotor::StartAutoUpdater();

   //init HeadController
   Head = HeadControl(PanHandler , TiltHandler , RollHandler);
   Head.MoveTo(0,0,0);

   // init Communication handling 
   COM = Communicator(9600,&Head);

   delay(100);
}



void loop() 
{
   COM.Update();
   delay(50);
}