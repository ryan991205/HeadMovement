#ifndef IHEADAXIS_H
#define IHEADAXIS_H


class IHeadAxis {


public:
	virtual ~IHeadAxis() {}
	
	virtual void Init() = 0;

	virtual void Move(int position) = 0;

	virtual void Move(int position, int speed) = 0;

	virtual void Move(int position, int speed, int acceleration) = 0;

	virtual int GetCurrentPosition() = 0;

	virtual byte IsMoving() = 0;

	virtual byte OnError() = 0;
};

#endif
