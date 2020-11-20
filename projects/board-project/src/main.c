#include "main.h"

void tecInit(){
	//Configurate SCU
	ADDR(SCU_BASE_ADDR,TEC0_SCU_ADDR) = TEC0_CONFIG;
	//Configurate as input
	ADDR(GPIO_BASE_ADDR,TEC0_GPIO_CONFIG_ADDR) |= TEC0_GPIO_CONFIG_DATA;
}

void ledInit(){
	//Configurate SCU
	ADDR(SCU_BASE_ADDR,LED1_SCU_ADDR) = LED1_CONFIG;
	//Configurate as input
	ADDR(GPIO_BASE_ADDR,LED1_GPIO_CONFIG_ADDR) |= LED1_GPIO_CONFIG_DATA;
}

bool isTecPressed(){
	// get bit status
}

void ledSet(bool state){
	// set bit status
}

int main(void){
	
	tecInit();
	ledInit();
   
   while(1){
		if(isTecPressed())
			ledSet(true);
		else
			ledSet(false);
   }
   
   return 0;   
}

