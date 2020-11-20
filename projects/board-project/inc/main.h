#ifndef __MAIN_H__
#define __MAIN_H__


//datasheet important addresses
#define SCU_BASE_ADDR	0x40086000
#define GPIO_BASE_ADDR	0x400F4000

#define SCU_FUNC0	0x0
#define SCU_FUNC1	0x1
#define SCU_FUNC2	0x2
#define SCU_FUNC3	0x3
#define SCU_FUNC4	0x4
#define SCU_FUNC5	0x5
#define SCU_FUNC6	0x6

#define PULLUP_ENABLE	0x0 << 4
#define PULLUP_DISABLE	0x1 << 4

#define INPUT_ENABLE	0x1 << 6 // EZI
#define INPUT_DISABLE	0x0 << 6

//EDU-CIAA pins used


//TEC0:	pin 38	P1_0		 
#define TEC0_SCU_ADDR	0x080
// As Output pullup. GPIO0[4] is FUNC0 offset 0x4
#define TEC0_CONFIG		(FUNC0 | PULLUP_ENABLE | INPUT_ENABLE)
#define TEC0_GPIO_CONFIG_ADDR	0x4
#define TEC0_GPIO_CONFIG_DATA	0x0

//LED1:	pin 104	P2_10
#define LED1_SCU_ADDR	0x128
// As Input pullup. GPIO0[14] is FUNC0 offset 
#define LED1_CONFIG			(FUNC0 | PULLUP_ENABLE)
#define LED1_GPIO_CONFIG_ADDR	0x14
#define LED1_GPIO_CONFIG_DATA	0x1


#define ADDR(X,Y)	*(X+Y)
#define ADDRESS(base,offset)  *((volatile unsigned int *)((volatile unsigned int)base + (volatile unsigned int)offset))




#endif
