
#ifndef HEADCONTROL_H
#define HEADCONTROL_H

#include "Arduino.h"
#include "IHeadAxis.h"

typedef struct {	
	 uint16_t pan;					
	 uint16_t tilt;
     uint16_t roll;					
} Location;


class HeadControl{

    private:

    IHeadAxis* PanMotor;
    IHeadAxis* TiltMotor;
    IHeadAxis* RollMotor;

    Location HomeLocation;
    Location CurrentLocation;
    Location GoingToLocation;

    public:

    HeadControl();
    HeadControl(IHeadAxis* pan, IHeadAxis* tilt);
    HeadControl(IHeadAxis* pan, IHeadAxis* tilt, IHeadAxis* roll);

    void MoveTo(int pan, int tilt);
    void MoveTo(int pan, int tilt, int roll);
    void MoveTo(Location location);

    Location getCurrentLocation();

    void setHome(Location location)
    {
       HomeLocation = location;
    }

    Location getHome()
    {
        return HomeLocation;
    }
 

    
 



};


#endif