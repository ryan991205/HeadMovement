#ifndef HEADAXIS_STEPPERMOTOR_H
#define HEADAXIS_STEPPERMOTOR_H

// Default constructor  Error when using cpp files with "arduino.h"
///
/// If you get an error the Library's add within the Library .h file 
/// a default constructor without parameters. example:
///	|||	Wont compile (some cases) = Class A { A(int k){} } 
///	|||	compiles				  =	Class A{ A(){} A(int k){}}

#include <Arduino.h>

#include "IHeadAxis.h"
#include <TMC26XStepper.h>
//#include <Encoder.h>
#include "GPIO.h"

#define BEGINPOINTSENSORPIN 9
#define ENDPOINTSENSORPIN 8

class HeadAxis_StepperMotor : public IHeadAxis {

private:
	GPIO *CS_PIN;
	GPIO *DIR_PIN;
	GPIO *STEP_PIN;
	GPIO *HALL1;
	GPIO *HALL2;

	CalibrationSet* MotorCalibration;

	// stepper orientation
	long StepBeginPoint 	= 0;
	long StepEndPoint 		= 0;
	long StepCenterPoint	= 0;
	long StepPosition		= 0;
	long NewStepPosition 	= 0;


	uint8_t MotorRotation 	= 0;
	uint8_t MotorRunning 	= 0;



	TMC26XStepper MotorControlChip = TMC26XStepper(200, 5, 5, 5, 5, 200);

	void MoveToInitPoint(GPIO *hallSensor, int direction, long readDelay);
	void MoveToBeginPoint();
	void MoveToEndPoint();

	void PositionUpdater();

public:
	static void StartAutoUpdater();
	static void StopAutoUpdater();

	void Calibrate();
	void Update();

	HeadAxis_StepperMotor();

	HeadAxis_StepperMotor(GPIO *cs, GPIO *dir, GPIO *step, GPIO *hall1, GPIO *hall2, int current, CalibrationSet *motorCalibration);

	void Move(int position);
	void Move(int position, int speed);
	void Move(int position, int speed, int acceleration);

	int GetCurrentPosition();

	byte IsMoving();

	byte OnError();

	void setMaxCurrent(int I_mA);

	void setSpeed(int speed);

	static void HandleSteps()
	{

	}	
};

#endif
