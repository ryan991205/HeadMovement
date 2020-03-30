
#include "GPIO.h"
#include "GPIO_Structs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief	Initialize GPIO block and set GPIO direction for a single GPIO pin .
 * @param   data			: GPIO struct (will store data of pin).
 * @param	_port			: GPIO Port number where pin is located! B=0 C=1 D=2.
 * @param	_pin			: GPIO pin to set 0-7.
 * @param	_dataDirection	: INPUT - OUTPUT - INPUT_PULLUP.
 * @warning Input must not be in use by other instance. valid input is required.
 *		    If invalid Input data will be written to random Hardware adresses!
 */
void GPIO_InitPin(GPIO *data, uint8_t _dataDirection, uint8_t _port, uint8_t _pin)
{
	data->DIR = _dataDirection;
	data->PORT = _port;
	data->PIN = _pin;

	GPIO_InitPinFromStruct(data);
}

/**
 * @brief	Initialize GPIO block and set GPIO direction for a single GPIO pin .
 * @param   data				: GPIO struct (will store data of pin).
 *				_port			: GIO Port number where pin is located! B=0 C=1 D=2.
 *				_pin			: GPIO pin to set 0-7.
 * 				_dataDirection	: INPUT - OUTPUT - INPUT_PULLUP.
 * @warning Input must not be in use by other instance. valid input is required.
 *		    If invalid Input data will be written to random Hardware adresses!
 */
void GPIO_InitPinFromStruct(const GPIO * data)
{
	if (data->DIR == OUTPUT) {
		GPIO_R[data->PORT].DIR |= (1UL << data->PIN);
	}
	else if (data->DIR == INPUT) {
		GPIO_R[data->PORT].DIR &= ~(1UL << data->PIN);
	}
	else if (data->DIR == INPUT_PULLUP) {
		GPIO_R[data->PORT].DIR &= ~(1UL << data->PIN);
		GPIO_R[data->PORT].PORT |= (1UL << data->PIN);
	}
}


/**
 * @brief	Initialize GPIO block and set GPIO direction for a whole PORT.
 * @param	_port				: GPIO Port number where pin is located! B=0 C=1 D=2.
 * @param	_portVal			: value of portregister.
  * @param	_dataDirectionVal	: value of the datadirection.
 * @param	_pinVal				: value of all pins on the port.
 * @warning valid input is required. If invalid Input data will be written to random Hardware adresses!
			NOTE ALL DATA FROM PORT WELL BE OVERWRITTEN! DONT USE IN COMBINATION WITH PIN_INIT.
 */
void GPIO_InitPort(uint8_t _port, uint8_t _portVal, uint8_t _directionVal, uint8_t _pinVal)
{
	GPIO_R[_port].PORT = _portVal;
	GPIO_R[_port].DIR = _directionVal;
	GPIO_R[_port].PIN = _pinVal;
}

// @brief Reads the output of a gpio pin and returns a maskset of the GPIO register.
// @example reading pin 2 that is high would return (00000100) ! note that that would read as 4.
uint8_t	GPIO_PinRead(const GPIO *data)
{
	return GPIO_R[data->PORT].PIN & (1UL << data->PIN);
}

// @brief	Sets output of GPIO 'pin' to level (0/LOW or >1/HIGH ).
void GPIO_PinWrite(GPIO *data, uint8_t level)
{
	if (level == LOW)
	{
		GPIO_R[data->PORT].PORT &= ~(1UL << data->PIN);
	}
	else
	{
		GPIO_R[data->PORT].PORT |= (1UL << data->PIN);
	}	
}

// @brief Reads the output of all the pins on specified port.
uint8_t GPIO_PortRead(uint8_t _port)
{
	return GPIO_R[_port].PIN;
}

// @brief	sets all pins of a specified port to portValue
// @warning OVERWRITES ALL PINS ON A PORT! dont use when manual pinWrite is used on port.
void	GPIO_PortWrite(uint8_t portValue, uint8_t _port)
{
	GPIO_R[_port].PORT = portValue;
}

// @brief	gets the number that corresponds to Arduino pins
uint8_t GPIO_getArduinoPin(const GPIO* data)
{
	if (data->PORT == PORT_D)
	{
		return data->PIN;
	}
	else if (data->PORT == PORT_C)
	{
		return (14 + data->PIN);
	}
	else if (data->PORT == PORT_B)
	{
		return (8 + data->PIN);
	}
	return 255;
}

// @brief Initialise the interupt with a defined triggertype for int 0 or 1 specified by *data.
void GPIO_InitInterrupt(GPIO *data, uint8_t _triggerType)
{
	if (data->PIN == 2)			{ PIN_INTERRUPTS1_R->EXTERNAL_INT_A |= _triggerType << 0; }
	else if (data->PIN == 3)	{ PIN_INTERRUPTS1_R->EXTERNAL_INT_A |= (_triggerType << 2); }
}

// @brief	Can enable INT0 or INT1 on PORTD if *data is correct.
void GPIO_EnableInterrupt(GPIO *data)
{
	if (data->PORT != PORT_D) return;

	if (data->PIN == 2)			{ PIN_INTERRUPTS2_R->EXTERNAL_INT_MASK_R |= GPIO_INT0_REQ_ENABLE_M; }
	else if (data->PIN == 3)	{ PIN_INTERRUPTS2_R->EXTERNAL_INT_MASK_R |= GPIO_INT1_REQ_ENABLE_M; }
}

// @brief	Can disable INT0 or INT1 on PORTD if *data port is correct.
void GPIO_DisableInterrupt(GPIO *data)
{
	if (data->PORT != PORT_D) return;

	if (data->PIN == 2)			{ PIN_INTERRUPTS2_R->EXTERNAL_INT_MASK_R &= ~GPIO_INT0_REQ_ENABLE_M; }
	else if (data->PIN == 3)	{ PIN_INTERRUPTS2_R->EXTERNAL_INT_MASK_R &= ~GPIO_INT1_REQ_ENABLE_M; }
}

#ifdef __cplusplus
}
#endif