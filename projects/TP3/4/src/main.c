#include "main.h"

// ---- Main function (entry point) ---- //
int main(void)
{
	// Board initialization
	boardConfig();
	
	// rgb pwm initialization
	rgbConfig (RGB_1, LEDR, LEDG, LEDB);

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


// uart callback on receive
void onUartRx(void* unused){
	uint8_t uartCharRx = uartRxRead(UART_USB);
	switch(uartCharRx){
		case COMMAND_LEDR_INC:
			rgbWriteRaw(RGB_1, rgbReadDutyRed(RGB_1) +1, rgbReadDutyGreen(RGB_1), rgbReadDutyBlue(RGB_1));
			break;
		case COMMAND_LEDR_MID:
			rgbWriteRaw(RGB_1, 12, rgbReadDutyGreen(RGB_1), rgbReadDutyBlue(RGB_1));
			break;
		case COMMAND_LEDR_DEC:
			rgbWriteRaw(RGB_1, rgbReadDutyRed(RGB_1) -1, rgbReadDutyGreen(RGB_1), rgbReadDutyBlue(RGB_1));
			break;
		case COMMAND_LEDG_INC:
			rgbWriteRaw(RGB_1, rgbReadDutyRed(RGB_1), rgbReadDutyGreen(RGB_1) + 1, rgbReadDutyBlue(RGB_1));
			break;
		case COMMAND_LEDG_MID:
			rgbWriteRaw(RGB_1, rgbReadDutyRed(RGB_1), 12, rgbReadDutyBlue(RGB_1));
			break;
		case COMMAND_LEDG_DEC:
			rgbWriteRaw(RGB_1, rgbReadDutyRed(RGB_1), rgbReadDutyGreen(RGB_1)-1, rgbReadDutyBlue(RGB_1));
			break;
		case COMMAND_LEDB_INC:
			rgbWriteRaw(RGB_1, rgbReadDutyRed(RGB_1), rgbReadDutyGreen(RGB_1), rgbReadDutyBlue(RGB_1)+1);
			break;
		case COMMAND_LEDB_MID:
			rgbWriteRaw(RGB_1, rgbReadDutyRed(RGB_1), rgbReadDutyGreen(RGB_1), 12);
			break;
		case COMMAND_LEDB_DEC:
			rgbWriteRaw(RGB_1, rgbReadDutyRed(RGB_1), rgbReadDutyGreen(RGB_1), rgbReadDutyBlue(RGB_1)-1);
			break;

	}
}
