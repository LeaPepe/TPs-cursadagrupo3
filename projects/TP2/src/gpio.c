#include "gpio.h"


// Example gpioInit(LED1, GPIO_OUTPUT)
void gpioInit( gpioMap_t pin, gpioInit_t conf )
{

	uint16_t scuMode;
	uint8_t gpioMode;

	switch(conf)
	{
	case GPIO_O:
		// NO PULLUP PULDOWN, ENABLE INPUT BUFFER, DISABLE INPUT GLITCH FILTER
		scuMode = SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
		// OUTPUT
		gpioMode = GPIO_OUTPUT;
		break;
	case GPIO_I:
		// NO PULLUP PULDOWN, ENABLE INPUT BUFFER, DISABLE INPUT GLITCH FILTER
		scuMode = SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
		// INPUT
		gpioMode = GPIO_INPUT;
		break;
	case GPIO_I_PULLUP:
		// PULLU, ENABLE INPUT BUFFER, DISABLE INPUT GLITCH FILTER
		scuMode = SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
		// INPUT
		gpioMode = GPIO_INPUT;
		break;
	case GPIO_I_PULLDOWN:
		//PULDOWN, ENABLE INPUT BUFFER, DISABLE INPUT GLITCH FILTER
		scuMode = SCU_MODE_PULLDOWN | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
		// INPUT
		gpioMode = GPIO_INPUT;
		break;
	case GPIO_I_REPEATER:
		//PULDOWN, ENABLE INPUT BUFFER, DISABLE INPUT GLITCH FILTER
		scuMode = SCU_MODE_REPEATER | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
		// INPUT
		gpioMode = GPIO_INPUT;
		break;
	}
	// SCU CONFIGURATION
	Chip_SCU_PinMux(gpioConfig[pin].scuPort,
									gpioConfig[pin].scuPin,
									scuMode,
									gpioConfig[pin].func);
	// GPIO CONFIGURATION
	Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioConfig[pin].gpioPort, ( 1 << gpioConfig[pin].gpioPin ), gpioMode );
}


void gpioWrite( gpioMap_t pin, bool_t value )
{
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpioConfig[pin].gpioPort, gpioConfig[pin].gpioPin, value);
}
void gpioRead( gpioMap_t pin )
{
	return (bool_t)Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, gpioConfig[pin].gpioPort, gpioConfig[pin].gpioPin);
}
