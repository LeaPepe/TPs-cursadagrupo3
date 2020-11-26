#include <gpio_18xx_43xx.h>
#include <scu_18xx_43xx.h>
#include <chip_lpc43xx.h>

//typedef uint8_t bool_t;

#ifndef HIGH
#define HIGH   1
#endif
#ifndef LOW
#define LOW    0
#endif

#ifndef FALSE
#define FALSE  0
#endif
#ifndef TRUE
#define TRUE   (!FALSE)
#endif


#define SCU_BASE_ADDR

#define GPIO_BASE_ADDR 0x40086000

// GPIO MODES
typedef enum
{
   GPIO_I,
   GPIO_O,
   GPIO_I_PULLUP,
   GPIO_I_PULLDOWN,
   GPIO_I_REPEATER,
} gpioInit_t;

// GPIO SCU AND PINPORT CONFIG
typedef struct gpioPinConfig_t {
	uint8_t scuPort;
	uint8_t scuPin;
	uint8_t gpioPort;
	uint8_t gpioPin;
	uint8_t func;
};


// USED GPIOS
typedef enum
{
	LED_1,
	LED_2,
	LED_3,
	LED_0_R,
	LED_0_G,
	LED_0_B,
	TEC_1,
	TEC_2,
	TEC_3,
	TEC_4,
} gpioMap_t;

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
		{1,6,1,9,0}, // TEC_4		P1_6 	-> GPIO1[9]		FUNC0
		};

void gpioInit( gpioMap_t pin, gpioInit_t conf );
void gpioWrite( gpioMap_t pin, bool_t value );
void gpioRead( gpioMap_t pin );
