
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "SS_LT_config.h"



SEVEN_SEGMENT_t SS_LT_AstrConfig[SEG_NUM]={
    {
        SS_LT_APORT:DIO_u8PORTB,
        SS_LT_APIN:DIO_u8PIN0,
        SS_LT_BPORT:DIO_u8PORTB,
        SS_LT_BPIN:DIO_u8PIN1,
        SS_LT_CPORT:DIO_u8PORTB,
        SS_LT_CPIN:DIO_u8PIN2,
        SS_LT_DPORT:DIO_u8PORTB,
        SS_LT_DPIN:DIO_u8PIN3,
        SS_LT_EPORT:DIO_u8PORTB,
        SS_LT_EPIN:DIO_u8PIN4,
        SS_LT_FPORT:DIO_u8PORTB,
        SS_LT_FPIN:DIO_u8PIN5,
        SS_LT_GPORT:DIO_u8PORTB,
        SS_LT_GPIN:DIO_u8PIN6,
        SS_LT_DOTPORT:DIO_u8PORTB,
        SS_LT_DOT:DIO_u8PIN7,
        SS_LT_COMPORT:DIO_u8PORTD,
        SS_LT_COM:DIO_u8PIN4,
    },{
        SS_LT_APORT:DIO_u8PORTB,
        SS_LT_APIN:DIO_u8PIN0,
        SS_LT_BPORT:DIO_u8PORTB,
        SS_LT_BPIN:DIO_u8PIN1,
        SS_LT_CPORT:DIO_u8PORTB,
        SS_LT_CPIN:DIO_u8PIN2,
        SS_LT_DPORT:DIO_u8PORTB,
        SS_LT_DPIN:DIO_u8PIN3,
        SS_LT_EPORT:DIO_u8PORTB,
        SS_LT_EPIN:DIO_u8PIN4,
        SS_LT_FPORT:DIO_u8PORTB,
        SS_LT_FPIN:DIO_u8PIN5,
        SS_LT_GPORT:DIO_u8PORTB,
        SS_LT_GPIN:DIO_u8PIN6,
        SS_LT_DOTPORT:DIO_u8PORTB,
        SS_LT_DOT:DIO_u8PIN7,
        SS_LT_COMPORT:DIO_u8PORTD,
        SS_LT_COM:DIO_u8PIN1,
    }
};