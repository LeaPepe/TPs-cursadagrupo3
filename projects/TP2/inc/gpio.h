#ifndef _GPIO_H_
#define _GPIO_H_

#include <board.h>


typedef uint8_t bool_t;

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
typedef struct {
	uint8_t scuPort;
	uint8_t scuPin;
	uint8_t gpioPort;
	uint8_t gpioPin;
	uint8_t func;
}gpioPinConfig_t;


// USED GPIOS
typedef enum
{
	LED1,
	LED2,
	LED3,
	LED0_R,
	LED0_G,
	LED0_B,
	TEC1,
	TEC2,
	TEC3,
	TEC4,
} gpioMap_t;




void gpioInit( gpioMap_t pin, gpioInit_t conf );
void gpioWrite( gpioMap_t pin, bool_t value );
bool_t gpioRead( gpioMap_t pin );

#endif
