#include "HeadAxis_ServoMotor.h"


HeadAxis_ServoMotor::HeadAxis_ServoMotor() {
	// DONT IMPLEMENT 
}

HeadAxis_ServoMotor::HeadAxis_ServoMotor(SoftwareSerial serialPort, int seralBaudRate, int channel) {
	// TODO - implement HeadAxis_ServoMotor::HeadAxis_ServoMotor
}

void HeadAxis_ServoMotor::Move(int position) {
	// TODO - implement HeadAxis_ServoMotor::Move
}

void HeadAxis_ServoMotor::Move(int position, int speed) {
	// TODO - implement HeadAxis_ServoMotor::Move
}

void HeadAxis_ServoMotor::Move(int position, int speed, int acceleration) {
	// TODO - implement HeadAxis_ServoMotor::Move
}

int HeadAxis_ServoMotor::GetCurrentPosition() {
	return 0;// TODO - implement HeadAxis_ServoMotor::GetCurrentPosition
}

byte HeadAxis_ServoMotor::IsMoving() {
	return 0;// TODO - implement HeadAxis_ServoMotor::IsMoving
}

byte HeadAxis_ServoMotor::OnError() {
	return 0;// TODO - implement HeadAxis_ServoMotor::OnError
}

void HeadAxis_ServoMotor::setSpeed(byte min, byte max) {
	// TODO - implement HeadAxis_ServoMotor::setSpeed
}

void HeadAxis_ServoMotor::setAcceleration(byte min, byte max) {
	// TODO - implement HeadAxis_ServoMotor::setAcceleration
}
