#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#define MINIMUM_MESSAGE_LENGTH 2

#define ERROR_UndefinedMessageLength -1
#define ERROR_NotReceived_END_CommunicationByte_onRightPosition -2
#define ERROR_UNKNOWN_BEGIN_COMMAND -3

#define LOCATION_OFFSET_FROM_ZERO 115


// return variables to pc
#define MESSAGE_RECEIVED    255
#define MESSAGE_INVALID     254

// Begin Byte/ command byte
#define ALL_MOTORS_COMMAND   254    // bytes expected = 4 + end 
#define PAN_MOTOR_COMMAND    253    // bytes expected = 2 + end 
#define TILT_MOTOR_COMMAND   252    // bytes expected = 2 + end 
#define ROLL_MOTOR_COMMAND   251    // bytes expected = 2 + end 
#define GET_POS_COMMAND      250    // bytes expected = 0 + end 

// End Byte / close byte
#define END_Communication   255    // no data after this byte exept of a new beginbyte


#include "HeadControl.h"
class Communicator
{
    private:

        HeadControl* Head;
        uint8_t buffer[16];

        uint8_t HandleCommand(uint8_t* Message, int length);
        int ReceiveCommand(uint8_t* buffer);


    public:
        Communicator();
        Communicator(int baud, HeadControl *head);
        void Update();
};
#endif