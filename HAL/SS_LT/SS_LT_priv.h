#ifndef SS_LT_PRIV_H_
#define SS_LT_PRIV_H_
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#define COMMON_CATHODE 0
#define COMMON_ANODE 1

#define NOT_CONNECTED 0
#define CONNECTED 1
static u8 Seg_Au8NumberDisplay[] ={
        0b00111111,
        0b00000110,
        0b01011011,
        0b01001111,
        0b01100110,
        0b01101101,
        0b01111101,
        0b00000111,
        0b01111111,
        0b01101111
};

#endif /* SS_LT_PRIV_H_ */
