        
#include "Communicator.h"        
        
        
Communicator::Communicator()
{

}   
        
Communicator::Communicator(int baud, HeadControl* head)
{
    Head = head;
    Serial.begin(baud);
}


void Communicator::Update()
{
    if(Serial.peek() == -1) {
        return;
    }

    if((Serial.peek() >= GET_POS_COMMAND) && (Serial.peek() <= ALL_MOTORS_COMMAND)){
        int i = 0;
        //cli();
        memset(buffer,115,15);
        buffer[i] = Serial.read();

        while(1) { 
            if(Serial.peek() != -1) {
                i++;
                buffer[i] = Serial.read();

                if(i > 12) {
                    Serial.println("0000");
                    Serial.flush();
                    return; 
                }

                if(buffer[i] == END_Communication){
                   HandleCommand(buffer, i);
                   Serial.flush();
                   //sei();
                   return;
                }
            }
        }
    }
    else{
        Serial.flush();
    } 
}

// SPEED NOT YET IMPLEMENTED !!!!
uint8_t Communicator::HandleCommand(uint8_t* Message, int length)
{
    if(length <1) {
        return ERROR_UndefinedMessageLength; 
    }

    switch (Message[0]){
        case GET_POS_COMMAND: {
            if(Message[1] != END_Communication){
                Serial.write(MESSAGE_INVALID);
                return ERROR_NotReceived_END_CommunicationByte_onRightPosition;
            }

            Location location = Head->getCurrentLocation();
            delay(5);
            Serial.write(GET_POS_COMMAND);
            Serial.write((location.pan + LOCATION_OFFSET_FROM_ZERO));
            Serial.write((location.tilt + LOCATION_OFFSET_FROM_ZERO));
            Serial.write((location.roll + LOCATION_OFFSET_FROM_ZERO));
            Serial.write(END_Communication);
        }break;   

        case ALL_MOTORS_COMMAND:{
            if(Message[5] != END_Communication) {
                Serial.write(MESSAGE_INVALID);
                return ERROR_NotReceived_END_CommunicationByte_onRightPosition;
            }

            int pan     = Message[1] - LOCATION_OFFSET_FROM_ZERO;
            int tilt    = Message[2] - LOCATION_OFFSET_FROM_ZERO;
            int roll    = Message[3] - LOCATION_OFFSET_FROM_ZERO;            
            Head->MoveTo(pan,tilt,roll);
            delay(5);
            Serial.write(MESSAGE_RECEIVED);
        } break;

        case PAN_MOTOR_COMMAND: {
            if(Message[3] != END_Communication) {
                Serial.write(MESSAGE_INVALID);
                return ERROR_NotReceived_END_CommunicationByte_onRightPosition; 
            }

            int location = Message[1]- LOCATION_OFFSET_FROM_ZERO;
            Head->MoveTo(location,IGNORE_MOVEMENT,IGNORE_MOVEMENT);
            delay(5);
            Serial.write(MESSAGE_RECEIVED);
        } break;

        case TILT_MOTOR_COMMAND: {
             if(Message[3] != END_Communication) {
                Serial.write(MESSAGE_INVALID);
                return ERROR_NotReceived_END_CommunicationByte_onRightPosition; 
            }

            int location = Message[1]- LOCATION_OFFSET_FROM_ZERO;
            Head->MoveTo(IGNORE_MOVEMENT,location,IGNORE_MOVEMENT);
            delay(5);
            Serial.write(MESSAGE_RECEIVED);
        }break;

        case ROLL_MOTOR_COMMAND: {
             if(Message[3] != END_Communication) {
                Serial.write(MESSAGE_INVALID);
                return ERROR_NotReceived_END_CommunicationByte_onRightPosition; 
            }

            Head->MoveTo(IGNORE_MOVEMENT,IGNORE_MOVEMENT,(Message[1] - LOCATION_OFFSET_FROM_ZERO));
            delay(5);
            Serial.write(MESSAGE_RECEIVED);
        }break; 
    }
    return ERROR_UNKNOWN_BEGIN_COMMAND;
}