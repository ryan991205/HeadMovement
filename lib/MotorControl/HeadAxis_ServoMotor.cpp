#include "HeadAxis_ServoMotor.h"


void HeadAxis_ServoMotor::Update()
{

}


HeadAxis_ServoMotor::HeadAxis_ServoMotor() 
{
	// DONT IMPLEMENT 
}

HeadAxis_ServoMotor::HeadAxis_ServoMotor(MicroMaestro* servoController, int channel, CalibrationSet* motorCalibration) 
{
	_channel = channel;
	ServoController = servoController;
	MotorCalibration = motorCalibration;
}

void HeadAxis_ServoMotor::Move(int position) 
{
	Move(position, _std_Speed, _std_Accel);
}

void HeadAxis_ServoMotor::Move(int position, int speed) 
{
	Move(position, speed, _std_Accel);
}

void HeadAxis_ServoMotor::Move(int position, int speed, int acceleration) 
{	
	if(position == IGNORE_MOVEMENT)return;

	if( position < MotorCalibration->MinPoint.PointInDegrees || 
		position > MotorCalibration->MaxPoint.PointInDegrees)
		{
			return;
		}
	
	int motorVal = map(	position,
						MotorCalibration->MinPoint.PointInDegrees,			MotorCalibration->MaxPoint.PointInDegrees,
						MotorCalibration->MinPoint.PointInMotorRotation,	MotorCalibration->MaxPoint.PointInMotorRotation);

	ServoController->setSpeed(_channel, speed);
	ServoController->setAcceleration(_channel, acceleration);
	ServoController->setTarget(_channel,motorVal);
}

// WARNING NOT IMPLEMENTED 
int HeadAxis_ServoMotor::GetCurrentPosition() 
{	
	return 0;
	// still needs to be edited to return good value from:  ServoController->getPosition(_channel);
}

byte HeadAxis_ServoMotor::IsMoving() 
{
	return ServoController->getMovingState();
}

// WARNING ! NOT IMPLEMENTED
byte HeadAxis_ServoMotor::OnError() 
{
	
	return 0;// TODO - implement HeadAxis_ServoMotor::OnError
}

void HeadAxis_ServoMotor::setSpeed(byte min, byte max) 
{
	// TODO - implement HeadAxis_ServoMotor::setSpeed
}

void HeadAxis_ServoMotor::setAcceleration(byte min, byte max)
{
	// TODO - implement HeadAxis_ServoMotor::setAcceleration
}
