#include "main.h"

// ---- Main function (entry point) ---- //
int main(void)
{
	// Board initialization
	boardConfig();
	
	// uart initialization 8N1 115200
	uartConfig( UART_USB, 115200 );

	// Generate callback on uart receive
	uartCallbackSet(UART_USB, UART_RECEIVE, onUartRx, NULL);
	
	// Enable uart interruptions
	uartInterrupt(UART_USB, true);
	
	// Initialization delay
	delay(500);

   // Main loop
   while(1) {
   }

   return 0 ;
}


void onUartRx(void* unused){
	uint8_t uartCharRx = uartRxRead(UART_USB);
	switch(uartCharRx){
		case COMMAND_LED1_TOGGLE:
			gpioWrite(LEDR,!gpioRead(LEDR));
			break;
		case COMMAND_LED2_TOGGLE:
			gpioWrite(LED1,!gpioRead(LED1));
			break;
		case COMMAND_LED3_TOGGLE:
			gpioWrite(LED2,!gpioRead(LED2));
			break;
		case COMMAND_LED4_TOGGLE:
			gpioWrite(LED3,!gpioRead(LED3));
			break;
	}
}
