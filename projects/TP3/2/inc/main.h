#include "sapi.h"


typedef enum{
   TEC_ON,
   TEC_OFF,
   TEC_FALLING,
   TEC_RISING
} tecState_t;

typedef struct {
	gpioMap_t ID;
	tecState_t st;
	char* name;
}tec_t;

void tecInit(tec_t* t, gpioMap_t ID, char* name);

void onTickUpdate();

void tecUpdate(tec_t* t);

void onTecRaised(tec_t* t);

void onTecFalled(tec_t* t);
