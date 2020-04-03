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


class HeadAxis_ServoMotor : IHeadAxis {

public:
	//MicroMaestro ServoCommunicator;
	
	//static void EnableServoCommunicator(SoftwareSerial serial);
	HeadAxis_ServoMotor();
	HeadAxis_ServoMotor(SoftwareSerial serialPort, int seralBaudRate, int channel);

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
