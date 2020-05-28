
#include "HeadControl.h"


HeadControl::HeadControl(){
    // empty constructor
}

HeadControl::HeadControl(IHeadAxis* pan, IHeadAxis* tilt){    
    PanMotor = pan;
    TiltMotor = tilt;
    RollMotor = 0;
    RollMotorPresent = false;
    CurrentLocation = GetLocationFromMotors();
}
    
HeadControl::HeadControl(IHeadAxis* pan, IHeadAxis* tilt, IHeadAxis* roll){
    PanMotor = pan;
    TiltMotor = tilt;
    RollMotor = roll;
    RollMotorPresent = true;
    CurrentLocation = GetLocationFromMotors();
}

Location HeadControl::getCurrentLocation(){
    return GetLocationFromMotors();
}

void HeadControl::MoveTo(int pan, int tilt){
    GoingToLocation.pan = pan;
    GoingToLocation.tilt = tilt;

    PanMotor->Move(pan);
    TiltMotor->Move(tilt);
}

void HeadControl::MoveTo(Location location){
    MoveTo(location.pan,location.tilt,location.roll);
}

void HeadControl::MoveTo(int pan, int tilt, int roll){   
    GoingToLocation.pan = pan;
    GoingToLocation.tilt = tilt;
    GoingToLocation.roll = roll;

    PanMotor->Move(pan);
    TiltMotor->Move(tilt);

    if(RollMotorPresent){
        RollMotor->Move(roll);
    }
}

Location HeadControl::GetLocationFromMotors(){
    Location currentLocation = {0,0,0};
    currentLocation.pan = PanMotor->GetCurrentPosition();
    currentLocation.tilt = TiltMotor->GetCurrentPosition();
    if(RollMotorPresent){
        currentLocation.roll = RollMotor->GetCurrentPosition();
    }
    return currentLocation;  
}