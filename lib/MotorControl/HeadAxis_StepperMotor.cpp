
#include "HeadAxis_StepperMotor.h"
#include "Timer.h"

#define CW 0
#define CCW 1


void HeadAxis_StepperMotor::StartAutoUpdater()
{
	// init
	TIMER1_R->CR_A = 0; 
	TIMER1_R->CR_B = 0;
	TIMER1_R->CR_B |= TIMER1_CRB_WGM12_M;		// put Timer one in CTC mode 
	TIMER1_R->CR_B |= CS_No_Prescale_1;	

	TIMER1_R->OUTPUT_COMPARE_A = 350;	// updatefreq

	// timer enable
	TIMER1_R->TIMER_COUNTER = 0;
	TIMER_INTERRUPTS_R->TIMER_1 |= TIMER_INT_COMPARE_A_ENABLE_M;
}

void HeadAxis_StepperMotor::StopAutoUpdater()
{
	TIMER1_R->TIMER_COUNTER = 0;
	TIMER_INTERRUPTS_R->TIMER_1 &= ~TIMER_INT_COMPARE_A_ENABLE_M;
}
// end TIMER fucnt 




void HeadAxis_StepperMotor::PositionUpdater()
{
	if(MotorRotation == CCW) 	{ StepPosition--;}
	else 						{ StepPosition++;}

	if((StepPosition > NewStepPosition-20) && (StepPosition < NewStepPosition +20))
	{
		MotorRunning = false;
	}
}

void HeadAxis_StepperMotor::Update()
{
	if(MotorRunning)
	{
		PositionUpdater();
		GPIO_PinToggle(STEP_PIN);
	}
}

void HeadAxis_StepperMotor::MoveToInitPoint(GPIO *hallSensor, int direction, long readDelay)
{
	long SensorBeforeReadCount = 0;
	GPIO_PinWrite(DIR_PIN, direction);
	MotorRotation = direction;
	while(1)
	{
		GPIO_PinToggle(STEP_PIN);
		_delay_us(40);
		if(direction == CW)
		{
			StepPosition++;
		}

		SensorBeforeReadCount++;
		if((GPIO_PinRead(hallSensor) == LOW) && (SensorBeforeReadCount > readDelay))
		{
			if(direction == CCW)
			{
				StepPosition = 0;
				StepBeginPoint= 0;
				MotorCalibration->MinPoint.PointInMotorRotation = 0;
			}
			else
			{
				StepEndPoint = StepPosition;
				MotorCalibration->MaxPoint.PointInMotorRotation = StepPosition;
			}	
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


void HeadAxis_StepperMotor::Calibrate()
{
	MoveToBeginPoint();
	delay(200);
	MoveToEndPoint();
	delay(200);
}





HeadAxis_StepperMotor::HeadAxis_StepperMotor()
{	
	// DONT IMPLEMENT!
}

HeadAxis_StepperMotor::HeadAxis_StepperMotor(GPIO *cs, GPIO *dir, GPIO *step, GPIO *hall1, GPIO *hall2, int current, CalibrationSet *motorCalibration)
{
	CS_PIN		= cs;
	DIR_PIN 	= dir;
	STEP_PIN 	= step;
	HALL1		= hall1;
	HALL2		= hall2;
	MotorCalibration = motorCalibration;

	GPIO_InitPinFromStruct(CS_PIN);
	GPIO_InitPinFromStruct(DIR_PIN);
	GPIO_InitPinFromStruct(STEP_PIN);
	GPIO_InitPinFromStruct(HALL1);
	GPIO_InitPinFromStruct(HALL2);

	// The motor contol library is not used to move the motor. only to setup the Chip and extra functions microstep &SpreadCycleChopper
	MotorControlChip = TMC26XStepper(0,GPIO_getArduinoPin(cs),GPIO_getArduinoPin(dir),GPIO_getArduinoPin(step),current);
	MotorControlChip.setRandomOffTime(-1);
	MotorControlChip.setSpreadCycleChopper(2,24,8,6,0);
	MotorControlChip.setStallGuardThreshold(50,-1);
	MotorControlChip.setCoolStepEnabled(true);
	MotorControlChip.setMicrosteps(64);
	MotorControlChip.start();
	delay(100);
	Calibrate();



}

void HeadAxis_StepperMotor::Move(int position) 
{
	//NewStepPosition = map(position,MotorCalibration->MinPoint.PointInDegrees,MotorCalibration->MaxPoint.PointInDegrees,
	//								StepBeginPoint,StepEndPoint);
	if(position == IGNORE_MOVEMENT)return;

	if( position < MotorCalibration->MinPoint.PointInDegrees || 
		position > MotorCalibration->MaxPoint.PointInDegrees)
		{
			return;
		}

	NewStepPosition = map(position,MotorCalibration->MinPoint.PointInDegrees,MotorCalibration->MaxPoint.PointInDegrees,
									MotorCalibration->MinPoint.PointInMotorRotation,MotorCalibration->MaxPoint.PointInMotorRotation);

	if(NewStepPosition == StepPosition)
	{
		MotorRunning = false;
		return;
	} 
	else if(NewStepPosition < StepPosition)
	{
		MotorRotation = CCW;
		GPIO_PinWrite(DIR_PIN, CCW);
	}
	else
	{
		MotorRotation = CW;
		GPIO_PinWrite(DIR_PIN, CW);
	}
	MotorRunning = true;	
}

void HeadAxis_StepperMotor::Move(int position, int speed) 
{
	setSpeed(speed);
	Move(position);
}

// NOT IMPLEMENTED!
void HeadAxis_StepperMotor::Move(int position, int speed, int acceleration) 
{	
	// WARNING ! acceleration is not implemented!
	setSpeed(speed);
	Move(position);
}
	

int HeadAxis_StepperMotor::GetCurrentPosition() 
{
	int currentPosition = map(StepPosition,
								MotorCalibration->MinPoint.PointInMotorRotation,MotorCalibration->MaxPoint.PointInMotorRotation,
								MotorCalibration->MinPoint.PointInDegrees,MotorCalibration->MaxPoint.PointInDegrees);
	return currentPosition;
}


byte HeadAxis_StepperMotor::IsMoving() 
{
	return MotorRunning;
}

//NOT IMPLEMENTED
byte HeadAxis_StepperMotor::OnError() 
{
	// TODO - implement HeadAxis_StepperMotor::OnError
	return 0;	
}

void HeadAxis_StepperMotor::setMaxCurrent(int I_mA) 
{
	if(I_mA < 50) return; 
	MotorControlChip.setCurrent(I_mA);
}

void HeadAxis_StepperMotor::setSpeed(int speed) 
{
	if(speed > 100 || speed < 0) return;

	int updateSpeed = map(speed,0,100,2000,400);
	cli();
	TIMER1_R->TIMER_COUNTER = 0;
	TIMER1_R->OUTPUT_COMPARE_A = updateSpeed;
	sei();
}
