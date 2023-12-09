//file guard
#ifndef SWITCH_Priv_H_
#define SWITCH_Priv_H_

#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"

typedef struct {
    u8 SW_PortID;
    u8 SW_PinID;
    u8 SW_Status;
}SW_t;


#endif
