#include "main.h"

#define DECIMAL 10
char* itoa(int value, char* result, int base);



// ---- Main function (entry point) ---- //
int main(void)
{
	// Board initialization
	boardConfig();
	// uart initialization 8N1 115200
	uartConfig( UART_USB, 115200 );
	
	// ADC
	adcConfig( ADC_ENABLE ); 
	

	// Variables Init
	uint16_t value;
	static char uartBuffer[10];

	// Init Delay
	delay(500);

   // Main loop
   while(1) {
	   
		// Read value
		uint16_t value = adcRead( CH1 );

		// Int value to string
		itoa( value, uartBuffer, DECIMAL );
		
		// Send to uart
		uartWriteString( UART_USB, "ADC CH1 value: " );
		uartWriteString( UART_USB, uartBuffer );
		uartWriteString( UART_USB, ". Max sample value: 1024 \r\n" );
		
		// Waiting time
		delay(1000);
   }

   return 0 ;
}



/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.

 */
char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}
