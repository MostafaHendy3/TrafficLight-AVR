

#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"
#include "../../MCAL/DIO/DIO_int.h"

#include "Switch_config.h"
#include "Switch_priv.h"

SW_t Switch_AstrSwitchState[SW_NUM]={
    {DIO_u8PORTD, DIO_u8PIN3, DIO_u8FLOAT},
    {DIO_u8PORTD, DIO_u8PIN0, DIO_u8FLOAT},
    {DIO_u8PORTD, DIO_u8PIN1, DIO_u8FLOAT},
};
