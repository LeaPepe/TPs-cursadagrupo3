#include "main.h"

#define TICKRATE_HZ  1000

#define LED0_R    0
#define LED0_G    1
#define LED0_B    2
#define LED1      3
#define LED2      4
#define LED3      5


// Handler para interrupción
static uint32_t tick_ct = 0;
void SysTick_Handler(void){  
	tick_ct += 1;
	if ((tick_ct % 500) == 0) {
		Board_LED_Toggle(LED2);
	}
}


int main(void){

   // Inicialización de la placa con la librería board.h
	Board_Init();
   
   // Configuración de la interrupción SysTick
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

   // Main loop
	while (1) {
		__WFI();
	}
   
   return 0;
}
