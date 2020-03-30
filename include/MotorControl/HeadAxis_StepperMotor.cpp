
#include "HeadAxis_StepperMotor.h"

HeadAxis_StepperMotor::HeadAxis_StepperMotor()
{
	
	// DONT IMPLEMENT!
}



HeadAxis_StepperMotor::HeadAxis_StepperMotor(GPIO cs, GPIO dir, GPIO step)
{
	// TODO - implement HeadAxis_StepperMotor::HeadAxis_StepperMotor
}

void HeadAxis_StepperMotor::Move(int position) 
{
	// TODO - implement HeadAxis_StepperMotor::Move
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
	// TODO - implement HeadAxis_StepperMotor::GetCurrentPosition
}

byte HeadAxis_StepperMotor::IsMoving() 
{
	// TODO - implement HeadAxis_StepperMotor::IsMoving
}

byte HeadAxis_StepperMotor::OnError() 
{
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
