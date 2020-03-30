#ifndef GPIO_H
#define GPIO_H

/*! \file GPIO.h
	\brief GPIO Control for the Atmel328P microcontroller
	Can control all IO using standard read/write function.

	AUTHOR		: Ryan Vrosch
	DATE		: 03-03-2020
	DATE HMV	: 30-03-2020
	VER			: V1.0.1_HMV
*/

// WARNING V1.0.1_HMV LINKER/INCLUDE ERROR
// 
// when importing the #include <GPIO> is not linked to the project
// you can do this by selecting the project, Press F4 and edit:
//	extra flags:
//  -I"c:\mypath\includes\GPIO" -I"c:\mypath\includes\GPIO"  
// edit this to the path of the GPIO project file

#include <Arduino.h>

typedef struct {		/* GPIO Structure */
	uint8_t DIR;		// 
	uint8_t PORT;		//
	uint8_t PIN;		//  
} GPIO;


#ifdef __cplusplus
extern "C" {
#endif

// GPIO EXTERNAL_INT_MASK_R
#define GPIO_INT1_REQ_ENABLE_M	(1UL << 1)
#define GPIO_INT0_REQ_ENABLE_M	(1UL << 0)



#ifndef ARDUINO

// Logic levels
#define	LOW					0
#define HIGH				1

// Port Directions
#define INPUT				0
#define OUTPUT				1
#define INPUT_PULLUP		2
#endif



// Ports 
#define PORT_B				0		// Port B is an 8-bit bi-directional I/O port with internal pull-up resistors.		Port B has better driving capabilities than the other ports. */
#define PORT_C				1		// Port C is an 8-bit bi-directional I/O port with internal pull-up resistors.		Only bits 6 and 7 are present on the product pinout.
#define PORT_D				2		// Port D is an 8-bit bi-directional I/O port with internal pull-up resistors.

// Interrupt types on INT0 and INT1
#define LOWLEVEL			0
#define ANY_CHANGE			1
#define FALLING_EDGE		2
#define RISING_EDGE			3

// Initialisation GPIO
void	GPIO_InitPin(GPIO *data, uint8_t _dataDirection, uint8_t _port, uint8_t _pin);
void	GPIO_InitPinFromStruct(const GPIO *data);

// Standard GPIO functions
void	GPIO_InitPort(uint8_t _port, uint8_t _portVal, uint8_t _directionVal, uint8_t _pinVal);
uint8_t	GPIO_PinRead(const GPIO *data);
void	GPIO_PinWrite( GPIO *data, uint8_t level);
uint8_t GPIO_PortRead(uint8_t _port);
void	GPIO_PortWrite(uint8_t portValue, uint8_t _port);
uint8_t GPIO_getArduinoPin(const GPIO* data); // V1.0.1_HMV only


// Interrupt control for level INT pins
void	GPIO_InitInterrupt(GPIO *data, uint8_t _triggerType);
void	GPIO_EnableInterrupt(GPIO *data);
void	GPIO_DisableInterrupt(GPIO *data);

 
#ifdef __cplusplus
} // extern "C"
#endif
#endif