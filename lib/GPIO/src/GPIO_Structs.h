#ifndef ATMEL328P_H
#define ATMEL328P_H

#include <inttypes.h>

// Copyright(c) Ryan Vrösch 2020
// All rights reserved.
// work in progress

// Hardware Adress periferal structs
typedef struct {								/* GPIO_PORT Structure */
	volatile uint8_t PIN;						// 0x00 offset 
	volatile uint8_t DIR;						// 0x01 offset 
	volatile uint8_t PORT;						// 0x02 offset
} GPIO_T;


typedef struct {
	volatile uint8_t	PIN_CHANGE_CONTROL;		// PCICR (Pin Change Interrupt Flag Register)
	volatile uint8_t	EXTERNAL_INT_A;			// EICRA
	volatile uint8_t	RESERVED;				// NOT USED!
	volatile uint8_t	PIN_CHANGE_0;			// PCMSK0
	volatile uint8_t	PIN_CHANGE_1;			// PCMSK1
	volatile uint8_t	PIN_CHANGE_2;			// PCMSK2
} PIN_INTERRUPTS1_T;

typedef struct {
	volatile uint8_t	PIN_CHANGE_INT_FLAG;	// PCIFR
	volatile uint8_t	EXTERNAL_INT_FLAG;		// EIFR
	volatile uint8_t	EXTERNAL_INT_MASK_R;	// EIMSK
} PIN_INTERRUPTS2_T;


// Hardware Base Adresses
#define GPIO_BASE				(0x03 + 0x20)
#define GPIO_B_BASE				(0x03 + 0x20)	
#define GPIO_C_BASE				(0x06 + 0x20)	
#define GPIO_D_BASE				(0x09 + 0x20)
#define PIN_INTERRUPTS1_BASE			0x68
#define PIN_INTERRUPTS2_BASE	(0x1B + 0x20)

// Pointed Structures to HW adresses
#define GPIO_R				((GPIO_T			*)		GPIO_BASE)				// sets GPIO_T pointer adress to GPIO_BASE
#define PIN_INTERRUPTS1_R	((PIN_INTERRUPTS1_T	*)		PIN_INTERRUPTS1_BASE)	// sets PIN_INTERRUPTS_T pointer adress to PIN_INTERRUPTS1_BASE
#define PIN_INTERRUPTS2_R	((PIN_INTERRUPTS2_T	*)		PIN_INTERRUPTS2_BASE)	// sets PIN_INTERRUPTS_T pointer adress to PIN_INTERRUPTS2_BASE

// ---------------------------------------------------------------------------------------------------------------------------------/
//BitMask Defines
//
/* Define naming
*
*	F	Flag
*	R	Read
*	W 	Write
*	RW 	Read/write
	M	Mask
*/

// GPIO EXTERNAL_INT_MASK_R
#define GPIO_INT1_REQ_ENABLE_M	(1UL << 1)
#define GPIO_INT0_REQ_ENABLE_M	(1UL << 0)

#endif //ATMEL328P_H

