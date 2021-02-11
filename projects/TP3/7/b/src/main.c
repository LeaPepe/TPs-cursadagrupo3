#include "main.h"

//global variables
tec_t tec1,tec2,tec3,tec4;


// tick hook update callback function
void onTickUpdate(){
	tecUpdate(&tec1);
	tecUpdate(&tec2);
	tecUpdate(&tec3);
	tecUpdate(&tec4);
}

// ---- Main function (entry point) ---- //
int main(void)
{
	// Board initialization
	boardConfig();
	
	// Tick rate configuration 50ms
	tickConfig(50);

	// Initialize tecs
	tecInit(&tec1, TEC1, "TEC 1");
	tecInit(&tec2, TEC2, "TEC 2");
	tecInit(&tec3, TEC3, "TEC 3");
	tecInit(&tec4, TEC4, "TEC 4");

	// Generate callback on tick update
   tickCallbackSet( onTickUpdate, NULL );


	// uart initialization 8N1 115200
	uartConfig( UART_USB, 115200 );
	uartConfig( UART_232, 115200 );

	// Generate callback on uart receive
	uartCallbackSet(UART_USB, UART_RECEIVE, onRxUsb, NULL);
	
	// Generate callback on uart receive
	uartCallbackSet(UART_232, UART_RECEIVE, onRx232, NULL);
	
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
void onRx232(void* unused){
	uint8_t uartCharRx = uartRxRead(UART_232);
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

// uart callback on receive
void onRxUsb(void* unused)
{
	uint8_t c = uartRead(UART_USB);
	uartWrite(UART_232,c);
}


// Initializes buttons structure
void tecInit(tec_t* t, gpioMap_t ID, char* name){
	t->st = TEC_OFF;
	t->ID = ID;
	t->name = name;
}


// buttons update function (state machine)
// Buttons states are inverted
void tecUpdate(tec_t* t){
	switch(t->st){
		case TEC_OFF:
			if(gpioRead(t->ID) == LOW)
				t->st = TEC_RISING;
			break;

		case TEC_ON:
			if(gpioRead(t->ID) == HIGH)
				t->st = TEC_FALLING;
			break;

		case TEC_RISING:
			if(gpioRead(t->ID) == LOW){
				t->st = TEC_ON;
				onTecRaised(t);
			} else
				t->st = TEC_OFF;
			break;

		case TEC_FALLING:
			if(gpioRead(t->ID) == HIGH){
				t->st = TEC_OFF;
				onTecFalled(t);
			} else
				t->st = TEC_ON;
			break;
	}
}


void onTecRaised(tec_t* t){
	uartWriteString( UART_USB, "Tecla apretada: " );
	uartWriteString( UART_USB, t->name );
	uartWriteString( UART_USB, "\r\n" );
}

void onTecFalled(tec_t* t){
	uartWriteString( UART_USB, "Tecla liberada: " );
	uartWriteString( UART_USB, t->name );
	uartWriteString( UART_USB, "\r\n" );
}
