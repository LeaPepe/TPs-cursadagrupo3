#include <sapi.h>

 typedef enum commandsEnum {
	COMMAND_LEDR_INC = 'q', // increment
	COMMAND_LEDR_MID = 'a', // set to half duty cycle
	COMMAND_LEDR_DEC = 'z', // decrement
	COMMAND_LEDG_INC = 'w',
	COMMAND_LEDG_MID = 's',
	COMMAND_LEDG_DEC = 'x',
	COMMAND_LEDB_INC = 'e',
	COMMAND_LEDB_MID = 'd',
	COMMAND_LEDB_DEC = 'c'
} commands_t;


void onUartRx(void* unused);
