#ifndef HEADAXIS_SERVOMOTOR_H
#define HEADAXIS_SERVOMOTOR_H

// Default constructor  Error when using cpp files with "arduino.h"
///
/// If you get an error the Library's add within the Library .h file 
/// a default constructor without parameters. example:
///	|||	Wont compile (some cases) = Class A { A(int k){} } 
///	|||	compiles				  =	Class A{ A(){} A(int k){}}


#include <Arduino.h>

#include "IHeadAxis.h"
#include <PololuMaestro.h>
#include <SoftwareSerial.h>


class HeadAxis_ServoMotor : IHeadAxis 
{
private:

	MicroMaestro* ServoController;
	CalibrationSet* MotorCalibration;
	int _channel;

	int _std_Accel = 127;
	int _std_Speed = 25 ;

public:
	void Update();
	
	HeadAxis_ServoMotor();
	HeadAxis_ServoMotor(MicroMaestro* ServoHandler, int channel, CalibrationSet* motorCalibration);

	void Move(int position);

	void Move(int position, int speed);

	void Move(int position, int speed, int acceleration);

	int GetCurrentPosition();

	byte IsMoving();

	byte OnError();

	void setSpeed(byte min, byte max);

	void setAcceleration(byte min, byte max);
};

#endif
