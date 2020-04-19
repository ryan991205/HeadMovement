
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
    uint8_t RollMotorPresent;

    Location HomeLocation = {0,0,0};
    Location CurrentLocation = {0,0,0};
    Location GoingToLocation= {0,0,0};

    Location GetLocationFromMotors();

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