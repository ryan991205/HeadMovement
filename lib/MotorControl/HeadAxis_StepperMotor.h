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

class HeadAxis_StepperMotor : IHeadAxis {

private:
	int BeginPoint;
	int EndPoint;


	TMC26XStepper Motor;
	//Encoder Encoder;

public:

	HeadAxis_StepperMotor();
	
	HeadAxis_StepperMotor(GPIO cs, GPIO dir, GPIO step);

	void Move(int position);

	void Move(int position, int speed);

	void Move(int position, int speed, int acceleration);

	int GetCurrentPosition();

	byte IsMoving();

	byte OnError();

	void setMaxCurrent(int I_mA);

	void setMaxSpeed(int speed);

	static void HandleSteps()
	{

	}


	// BEGIN:
	void Calibrate();
	

	
};

#endif
