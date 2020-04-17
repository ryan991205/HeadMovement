
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

	TIMER1_R->OUTPUT_COMPARE_A = 1250;	// updatefreq

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
		_delay_us(55);
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
				Serial.println(StepBeginPoint);
			}
			else
			{
				StepEndPoint = StepPosition;
				Serial.println(StepEndPoint);
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

void HeadAxis_StepperMotor::MoveToCenterPoint()
{

}


void HeadAxis_StepperMotor::Calibrate()
{
	MoveToBeginPoint();
	// save shit
	delay(250);
	MoveToEndPoint();
	delay(50);
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
	MotorControlChip.setMicrosteps(32);

	MotorControlChip.start();
	MotorControlChip.setSpeed(100);
	delay(1000);
	

	// TODO - implement initialisation 
}

void HeadAxis_StepperMotor::Move(int position) 
{
	NewStepPosition = map(position,-90,90,StepBeginPoint,StepEndPoint);

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
