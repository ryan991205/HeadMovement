
#include "HeadAxis_StepperMotor.h"

#define CW 0
#define CCW 1


void HeadAxis_StepperMotor::Update()
{
	MotorControlChip.move();
}



void HeadAxis_StepperMotor::MoveToInitPoint(GPIO *hallSensor, int direction, long readDelay)
{
	long SensorBeforeReadCount = 0;
	GPIO_PinWrite(DIR_PIN, direction);
	while(1)
	{
		GPIO_PinToggle(STEP_PIN);
		_delay_us(25);

		SensorBeforeReadCount++;
		if((GPIO_PinRead(hallSensor) == LOW) && (SensorBeforeReadCount > readDelay))
		{
			break;
		}
	}
}

void HeadAxis_StepperMotor::MoveToBeginPoint()
{
	MoveToInitPoint(HALL1, CCW, 12000);
}

void HeadAxis_StepperMotor::MoveToEndPoint()
{
		MoveToInitPoint(HALL2, CW, 2500);
}

void HeadAxis_StepperMotor::MoveToCenterPoint()
{

}


void HeadAxis_StepperMotor::Calibrate()
{
	MoveToBeginPoint();
	// save shit
	delay(500);
	MoveToEndPoint();
	// save shit
}





HeadAxis_StepperMotor::HeadAxis_StepperMotor()
{	
	// DONT IMPLEMENT!
}

HeadAxis_StepperMotor::HeadAxis_StepperMotor(GPIO *cs, GPIO *dir, GPIO *step, GPIO *hall1, GPIO *hall2, int current)
{
	CS_PIN		= cs;
	DIR_PIN 	= dir;
	STEP_PIN 	= step;
	HALL1		= hall1;
	HALL2		= hall2;

	GPIO_InitPinFromStruct(CS_PIN);
	GPIO_InitPinFromStruct(DIR_PIN);
	GPIO_InitPinFromStruct(STEP_PIN);
	GPIO_InitPinFromStruct(HALL1);
	GPIO_InitPinFromStruct(HALL2);

	//MotorControlChip = TMC26XStepper(200,7,6,5,current);
	MotorControlChip = TMC26XStepper(800,GPIO_getArduinoPin(cs),GPIO_getArduinoPin(dir),GPIO_getArduinoPin(step),current);
	MotorControlChip.setRandomOffTime(0);
	MotorControlChip.setSpreadCycleChopper(2,24,8,6,0);
	MotorControlChip.setStallGuardThreshold(4,0);
	MotorControlChip.setMicrosteps(64);

	MotorControlChip.start();
	MotorControlChip.setSpeed(100);
	delay(1000);
	

	// TODO - implement initialisation 
}

void HeadAxis_StepperMotor::Move(int position) 
{
	MotorControlChip.step(position);
	//	MotorControlChip.step(1000);
}

void HeadAxis_StepperMotor::Move(int position, int speed) 
{
	// TODO - implement HeadAxis_StepperMotor::Move
}

void HeadAxis_StepperMotor::Move(int position, int speed, int acceleration) 
{
	// TODO - implement HeadAxis_StepperMotor::Move
}

int HeadAxis_StepperMotor::GetCurrentPosition() 
{
	return 0;
	// TODO - implement HeadAxis_StepperMotor::GetCurrentPosition
}

byte HeadAxis_StepperMotor::IsMoving() 
{
	return 0;
	// TODO - implement HeadAxis_StepperMotor::IsMoving
}

byte HeadAxis_StepperMotor::OnError() 
{
	return 0;
	// TODO - implement HeadAxis_StepperMotor::OnError
}

void HeadAxis_StepperMotor::setMaxCurrent(int I_mA) 
{
	// TODO - implement HeadAxis_StepperMotor::setMaxCurrent
}

void HeadAxis_StepperMotor::setMaxSpeed(int speed) 
{
	// TODO - implement HeadAxis_StepperMotor::setMaxSpeed
}
