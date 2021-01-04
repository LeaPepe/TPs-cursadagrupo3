#include "main.h"

#include "sapi.h"


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
	
	//
	uartConfig( UART_USB, 115200 );
	// Tick callback function configurations. Functions and parameters

	// Initialize tecs
	tecInit(&tec1, TEC1, "TEC 1");
	tecInit(&tec2, TEC2, "TEC 2");
	tecInit(&tec3, TEC3, "TEC 3");
	tecInit(&tec4, TEC4, "TEC 4");

	// Generate callbackon tick update
   tickCallbackSet( onTickUpdate, NULL );

   // Initialization delay
   delay(500);

   // Main loop
   while(1) {
   }

   return 0 ;
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

	switch(t->ID){
		case TEC1:
			gpioWrite(LEDR,HIGH);
			break;
		case TEC2:
			gpioWrite(LED1,HIGH);
			break;
		case TEC3:
			gpioWrite(LED2,HIGH);
			break;
		case TEC4:
			gpioWrite(LED3,HIGH);
			break;
	}
}

void onTecFalled(tec_t* t){
	uartWriteString( UART_USB, "Tecla liberada: " );
	uartWriteString( UART_USB, t->name );
	uartWriteString( UART_USB, "\r\n" );

	switch(t->ID){
		case TEC1:
			gpioWrite(LEDR,LOW);
			break;
		case TEC2:
			gpioWrite(LED1,LOW);
			break;
		case TEC3:
			gpioWrite(LED2,LOW);
			break;
		case TEC4:
			gpioWrite(LED3,LOW);
			break;
		}
}

