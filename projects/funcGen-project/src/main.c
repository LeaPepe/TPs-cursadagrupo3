#include "main.h"


// overridable tick flag
volatile bool SysTick_Time_Flag = false;

// State machine global statechart
static FuncGen statechart;

// Timer ticks
TimerTicks ticks[NOF_TIMERS];

// state machine user-defined external functions (action)
void funcGenIface_opAddV(const FuncGen* handle){
	Board_LED_Set(LED3, !Board_LED_Test(LED3)); // swap state
}
void funcGenIface_opSubV(const FuncGen* handle){
	Board_LED_Set(LED2, !Board_LED_Test(LED2)); // swap state
}
void funcGenIface_opAddF(const FuncGen* handle){
	Board_LED_Set(LED3, !Board_LED_Test(LED3)); // swap state
}
void funcGenIface_opSubF(const FuncGen* handle){
	Board_LED_Set(LED2, !Board_LED_Test(LED2)); // swap state
}
void funcGenIface_opSetForm(const FuncGen* handle, const sc_integer form){
	switch(form){
	    case OPT_SQR:
	    	Board_LED_Set(LED0_R, TRUE);
	    	Board_LED_Set(LED0_G, FALSE);
	    	Board_LED_Set(LED0_B, FALSE);
	      break;
	    case OPT_SIN:
	    	Board_LED_Set(LED0_R, FALSE);
	    	Board_LED_Set(LED0_G, TRUE);
	    	Board_LED_Set(LED0_B, FALSE);
	      break;
	    case OPT_TRI:
	    	Board_LED_Set(LED0_R, FALSE);
			Board_LED_Set(LED0_G, FALSE);
			Board_LED_Set(LED0_B, TRUE);
	    default:
	    	break;
	      // default statements
	}
}

void funcGenIface_opSetMode(const FuncGen* handle, const sc_boolean mode){
	Board_LED_Set(LED1, mode);
}

// Scan for all buttons
uint32_t Buttons_GetStatus_(void) {
	uint8_t ret = false;
	uint32_t idx;

	for (idx = 0; idx < 4; ++idx) {
		if (Board_TEC_GetStatus(BOARD_TEC_1 + idx) == 0)
			ret |= 1 << idx;
	}
	return ret;
}

// Set time services for state machine
void funcGen_setTimer( FuncGen* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic )
{
	SetNewTimerTick(ticks, NOF_TIMERS, evid, time_ms, periodic);
}

// Unset time services for state machine
void funcGen_unsetTimer( FuncGen* handle, const sc_eventid evid )
{
	UnsetTimerTick( ticks, NOF_TIMERS, evid );
}

// Set the flag from interruption (every 1ms)
void SysTick_Handler(void){
	SysTick_Time_Flag = true;
}

// Main
int main(void)
{
	uint32_t i;

	// Button status
	uint32_t BUTTON_Status;

	// Generic Initialization
	Board_Init();

	// Init Ticks counter => TICKRATE_MS
	SysTick_Config(SystemCoreClock / TICKRATE_MS);

	// Init Timer Ticks
	InitTimerTicks( ticks, NOF_TIMERS );

	// Statechart Initialization
	funcGen_init( &statechart );
	funcGen_enter( &statechart );

	// Main while
	while (1) {
		// Wait for interruption
		__WFI();

		// If interruption because timer
		if (SysTick_Time_Flag == true) {

			// reset flag
			SysTick_Time_Flag = false;

			// Update timers
			UpdateTimers( ticks, NOF_TIMERS );

			// Scan all timers
			for (i = 0; i < NOF_TIMERS; i++) {

				// If pending events
				if (IsPendEvent( ticks, NOF_TIMERS, ticks[i].evid ) == true) {

					// Raise event
					funcGen_raiseTimeEvent( &statechart, ticks[i].evid );

					// Mark as atached
					MarkAsAttEvent( ticks, NOF_TIMERS, ticks[i].evid );
				}
			}

			// Get button statuses
			BUTTON_Status = Buttons_GetStatus_();


			// If pressed buttons
			if (BUTTON_Status != 0)
				// Raise the pressed event with the status
				funcGenIface_raise_evTecPressed(&statechart, BUTTON_Status);
			else
				// Else raise not pressed event
				funcGenIface_raise_evTecNotPressed(&statechart);

			// Run state machine cycle
			funcGen_runCycle(&statechart);
		}
	}
} // Main end

