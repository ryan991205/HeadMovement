#include <Arduino.h>
#include "GPIO.h"


// blink example

GPIO LED1	= { .DIR = OUTPUT,	.PORT = PORT_B, .PIN =  5}; // pin 13  on arduino (LED)
GPIO LED2;

void setup() 
{
  // call init when struct is filled 
   GPIO_InitPinFromStruct(&LED1);

   // call init with pin/port settings
   GPIO_InitPin(&LED2, OUTPUT,PORT_B,4); //  pin 12  on arduino (LED)
}



void loop() 
{
  delay(1000);
  GPIO_PinWrite(&LED1,HIGH);
  delay(1000);
  GPIO_PinWrite(&LED1,LOW);
}