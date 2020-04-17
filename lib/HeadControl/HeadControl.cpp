
#include "HeadControl.h"


HeadControl::HeadControl()
{

}

HeadControl::HeadControl(IHeadAxis* pan, IHeadAxis* tilt)
{

}
    
HeadControl::HeadControl(IHeadAxis* pan, IHeadAxis* tilt, IHeadAxis* roll)
{

}

void HeadControl::MoveTo(int pan, int tilt)
{
   // MoveTo({pan,tilt,0});
}
void HeadControl::MoveTo(int pan, int tilt, int roll)
{

    //MoveTo({pan,tilt,roll});

}
void HeadControl::MoveTo(Location location)
{

}
