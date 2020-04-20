#ifndef TIMER_H
#define TIMER_H

// copyright Ryan vrösch 2020 all rights reserved 

#include "Arduino.h"

#define CPU_Clock 16000000

typedef struct {								/* no implementation yet */
	volatile uint8_t CR_A;					
	volatile uint8_t CR_B;					
} TIMER_8BIT_T;

typedef struct {								/* 16 bit timer Structure (TIMER1) */
	volatile uint8_t	CR_A;					// 0x00 offset (0x80) TCCR1A
	volatile uint8_t	CR_B;					// 0x01 offset (0x81) TCCR1B
	volatile uint8_t	CR_C;					// 0x02 offset (0x82) TCCR1C
	volatile uint8_t	RESERVED;				// 0x03 offset  
	volatile uint16_t	TIMER_COUNTER;			// 0x04	offset (0x84) TCNT1L
	volatile uint16_t	INPUT_CAPTURE;			// 0x06 offset (0x86) ICR1L
	volatile uint16_t	OUTPUT_COMPARE_A;		// 0x08	offset (0x88) OCR1AL
	volatile uint16_t	OUTPUT_COMPARE_B;		// 0x0A	offset (0x8A) OCR1BL
} TIMER_16BIT_T;

typedef struct {
	volatile uint8_t	TIMER_0;				// TIMSK0
	volatile uint8_t	TIMER_1;				// TIMSK1
	volatile uint8_t	TIMER_2;				// TIMSK2
} TIMER_INTERRUPTS_T;


#define TIMER1_BASE                         0x80
#define TIMER_INTERRUPTS_BASE			    0x6E

#define TIMER1_R			((TIMER_16BIT_T		*)		TIMER1_BASE)			// sets TIMER1 (16b timer) to adress of TIMER_16BIT_BASE
#define TIMER_INTERRUPTS_R	((TIMER_INTERRUPTS_T*)		TIMER_INTERRUPTS_BASE)	// sets TIMER_INTERRUPTS_T pointer adress to TIMER_INTERRUPTS_BASE

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

// TIMER1_CONTROL (Control Register (CR) A B & C)
#define TIMER1_CRA_COM1A1_M		(1UL << 7)							// COM1A1 (COM1A1:0: Compare Output Mode for Channel A)
#define TIMER1_CRA_COM1A0_M		(1UL << 6)							// COM1A0 (COM1A1:0: Compare Output Mode for Channel A)
#define TIMER1_CRA_COM1B1_M		(1UL << 5)							// COM1B1 (COM1B1:0: Compare Output Mode for Channel B)
#define TIMER1_CRA_COM1B0_M		(1UL << 4)							// COM1B0 (COM1B1:0: Compare Output Mode for Channel B)
#define TIMER1_CRA_WGM11_M		(1UL << 1)							// WGM11 (WGM11:0: Waveform Generation Mode)	
#define TIMER1_CRA_WGM10_M		(1UL << 0)							// WGM10 (WGM11:0: Waveform Generation Mode)

#define TIMER1_CRB_ICNC1_M		(1UL << 7)							// ICNC1 (Input Capture Noise Canceler)
#define TIMER1_CRB_ICES1_M		(1UL << 6)							// ICES1 (Input Capture Edge Select)
#define TIMER1_CRB_WGM13_M		(1UL << 4)							// WGM13 (WGM11:0: Waveform Generation Mode)
#define TIMER1_CRB_WGM12_M		(1UL << 3)							// WGM12(WGM11:0: Waveform Generation Mode)
#define TIMER1_CRB_CS_M			(1UL << 2 | 1UL << 1 | 1UL << 0 )	// (CS12:0: Clock Select)

#define TIMER1_CRC_FOC1A_M		(1UL << 7)							// FOC1A (Force Output Compare for Channel A)
#define TIMER1_CRC_FOC1B_M		(1UL << 6)							// FOC1B (Force Output Compare for Channel A)

// TIMER INTERRUPTS
#define TIMER1_INT_INPUTCAPTURE_ENABLE			(1UL << 5) // ICIE1 (Timer/Counter1, Input Capture Interrupt Enable)
#define TIMER_INT_COMPARE_B_ENABLE_M			(1UL << 2) // OCIE0B (Timer/Counter Output Compare Match B Interrupt Enable)
#define TIMER_INT_COMPARE_A_ENABLE_M			(1UL << 1) // OCIE0A (Timer/Counter0 Output Compare Match A Interrupt Enable)
#define TIMER_INT_OVERFLOW_ENABLE_M				(1UL << 0) // TOIE0	(Timer/Counter0 Overflow Interrupt Enable)

// TIMER1_CRB_CS_M selectable modes
#define CS_No_Clock								0x00
#define CS_No_Prescale_1						0x01
#define CS_Prescale_8							0x02
#define CS_Prescale_64							0x03
#define CS_Prescale_254							0x04
#define CS_Prescale_1024						0x05
#define CS_Prescale_EXT_clock_T1_FallingEdge	0x06
#define CS_Prescale_EXT_clock_T1_RisingEdge		0x07

// TIMER INTERRUPTS
#define TIMER1_INT_INPUTCAPTURE_ENABLE			(1UL << 5) // ICIE1 (Timer/Counter1, Input Capture Interrupt Enable)
#define TIMER_INT_COMPARE_B_ENABLE_M			(1UL << 2) // OCIE0B (Timer/Counter Output Compare Match B Interrupt Enable)
#define TIMER_INT_COMPARE_A_ENABLE_M			(1UL << 1) // OCIE0A (Timer/Counter0 Output Compare Match A Interrupt Enable)
#define TIMER_INT_OVERFLOW_ENABLE_M				(1UL << 0) // TOIE0	(Timer/Counter0 Overflow Interrupt Enable)



#endif
