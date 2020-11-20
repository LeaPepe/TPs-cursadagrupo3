#ifndef __MAIN_H__
#define __MAIN_H__

#define ADDRESS(base,offset)  *((volatile unsigned int *)((volatile unsigned int)base + (volatile unsigned int)offset))

#define SCU_BASE                    0x40086000
#define SCU_LED0_R_OFFSET           0x100

#define GPIO_BASE                   0x400F4000
#define GPIO_LED0_R_OFFSET          0x2014
#define GPIO_LED0_R_WRITE_OFFSET    0x2214


#endif