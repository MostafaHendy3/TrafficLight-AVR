//file gaurd 
#ifndef SWITCH_INT_H_
#define SWITCH_INT_H_
#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"

typedef struct {
    u8 SW_PortID;
    u8 SW_PinID;
    u8 SW_Status;
}SW_t;

//function to initialize the switch
ES_t Switch_enuInit(SW_t * Copy_AstrSwitchState);
ES_t Switch_enuGetState(SW_t *Copy_AstrSwitchState,u8 * Copy_pu8SwState);

#endif /* SWITCH_INT_H_ */