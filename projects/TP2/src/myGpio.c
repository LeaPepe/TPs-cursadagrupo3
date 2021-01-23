#include "myGpio.h"


const gpioPinConfig_t gpioConfig[] = {
	// { scuPort, scuPin, gpioPort, gpioPin, func}
		{2,10,0,14,0}, // LED_1		P2_10 	-> GPIO0[14] 	FUNC0
		{2,11,1,11,0}, // LED_2		P2_11 	-> GPIO1[11] 	FUNC0
		{2,12,1,12,0}, // LED_3		P2_12 	-> GPIO1[12] 	FUNC0
		{2,0,5,0,4}, // LED_0_R		P2_0 	-> GPIO5[0] 	FUNC4
		{2,1,5,1,4}, // LED_0_G		P2_1 	-> GPIO5[1]		FUNC4
		{2,2,5,2,4}, // LED_0_B		P2_2 	-> GPIO5[2]		FUNC4
		{1,0,0,4,0}, // TEC_1		P1_0 	-> GPIO0[4]		FUNC0
		{1,1,0,8,0}, // TEC_2		P1_1 	-> GPIO0[8]		FUNC0
		{1,2,0,9,0}, // TEC_3		P1_2 	-> GPIO0[9]		FUNC0
		{1,6,1,9,0} // TEC_4		P1_6 	-> GPIO1[9]		FUNC0
		};


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
		gpioMode = GPIO_O;
		break;
	case GPIO_I:
		// NO PULLUP PULDOWN, ENABLE INPUT BUFFER, DISABLE INPUT GLITCH FILTER
		scuMode = SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
		// INPUT
		gpioMode = GPIO_I;
		break;
	case GPIO_I_PULLUP:
		// PULLU, ENABLE INPUT BUFFER, DISABLE INPUT GLITCH FILTER
		scuMode = SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
		// INPUT
		gpioMode = GPIO_I;
		break;
	case GPIO_I_PULLDOWN:
		//PULDOWN, ENABLE INPUT BUFFER, DISABLE INPUT GLITCH FILTER
		scuMode = SCU_MODE_PULLDOWN | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
		// INPUT
		gpioMode = GPIO_I;
		break;
	case GPIO_I_REPEATER:
		//PULDOWN, ENABLE INPUT BUFFER, DISABLE INPUT GLITCH FILTER
		scuMode = SCU_MODE_REPEATER | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
		// INPUT
		gpioMode = GPIO_I;
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
bool_t gpioRead( gpioMap_t pin )
{
	return (bool_t)Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, gpioConfig[pin].gpioPort, gpioConfig[pin].gpioPin);
}
