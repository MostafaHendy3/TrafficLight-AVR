#ifndef SS_LT_CONFIG_H_
#define SS_LT_CONFIG_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#define SEG_NUM 2

typedef struct {
    u8 SS_LT_APORT;
    u8 SS_LT_APIN;
    u8 SS_LT_BPORT;
    u8 SS_LT_BPIN;
    u8 SS_LT_CPORT;
    u8 SS_LT_CPIN;
    u8 SS_LT_DPORT;
    u8 SS_LT_DPIN;
    u8 SS_LT_EPORT;
    u8 SS_LT_EPIN;
    u8 SS_LT_FPORT;
    u8 SS_LT_FPIN;
    u8 SS_LT_GPORT;
    u8 SS_LT_GPIN;
    u8 SS_LT_COM;
    u8 SS_LT_COMPORT;
    u8 SS_LT_DOT;
    u8 SS_LT_DOTPORT;
    u8 SS_LT_TYPE;
}SEVEN_SEGMENT_t;

#endif /* SS_LT_CONFIG_H_ */
