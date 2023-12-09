//file guard
#ifndef LED_INT_H_
#define LED_INT_H_
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "LED_Config.h"
typedef struct{
    u8 LED_u8Port;
    u8 LED_u8Pin;
    u8 LED_u8Connection;
    u8 LED_u8InitStatus;
}LED_t;

ES_t LED_enuInit(LED_t * Copy_PAstrLEDState);
ES_t LED_enuSetLedOn(LED_t * Copy_PstrLEDID);
ES_t LED_enuSetLedOff(LED_t * Copy_PstrLEDID);


#endif