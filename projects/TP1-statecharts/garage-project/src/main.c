#include "main.h"


// overridable tick flag
volatile bool SysTick_Time_Flag = false;

// State machine global statechart
static Garage statechart;

// Timer ticks
TimerTicks ticks[NOF_TIMERS];



// state machine user-defined external functions (action)
void garageIface_opSetMotorSt(const Garage* handle, const sc_boolean state){
	Board_LED_Set(LED3, state);
}
void garageIface_opSetMotorDir(const Garage* handle, const sc_boolean dir){
	Board_LED_Set(LED2, dir);
}
void garageIface_opSetLight(const Garage* handle, const sc_boolean State){
	Board_LED_Set(LED1, State);
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
void garage_setTimer( Garage* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic )
{
	SetNewTimerTick(ticks, NOF_TIMERS, evid, time_ms, periodic);
}

// Unset time services for state machine
void garage_unsetTimer( Garage* handle, const sc_eventid evid )
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
	garage_init( &statechart );
	garage_enter( &statechart );

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
					garage_raiseTimeEvent( &statechart, ticks[i].evid );

					// Mark as atached
					MarkAsAttEvent( ticks, NOF_TIMERS, ticks[i].evid );
				}
			}

			// Get button statuses
			BUTTON_Status = Buttons_GetStatus_();


			// If pressed buttons
			if (BUTTON_Status != 0)
				// Raise the pressed event with the status
				garageIface_raise_evTecPressed(&statechart, BUTTON_Status);
			else
				// Else raise not pressed event
				garageIface_raise_evTecNotPressed(&statechart);

			// Run state machine cycle
			garage_runCycle(&statechart);
		}
	}
} // Main end

