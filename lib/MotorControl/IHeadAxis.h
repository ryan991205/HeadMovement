#ifndef IHEADAXIS_H
#define IHEADAXIS_H

#define IGNORE_MOVEMENT 125

typedef struct 
{
   int16_t PointInDegrees;
   int32_t PointInMotorRotation;
} Point;

typedef struct 
{		
	Point MinPoint;		 
	Point CenterPoint;  
	Point MaxPoint;		  
} CalibrationSet;


class IHeadAxis 
{
public:
	virtual ~IHeadAxis() {}

	virtual void Move(int position) = 0;

	virtual void Move(int position, int speed) = 0;

	virtual void Move(int position, int speed, int acceleration) = 0;

	virtual int GetCurrentPosition() = 0;

	virtual byte IsMoving() = 0;

	virtual byte OnError() = 0;

	virtual void Update();
};

#endif
