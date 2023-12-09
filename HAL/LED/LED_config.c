#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "LED_priv.h"
#include "LED_config.h"


LED_t LED_AstrLEDState[LED_NUM]={
    {DIO_u8PORTA, DIO_u8PIN0,LED_SOURCE,LED_OFF},
    {DIO_u8PORTA, DIO_u8PIN1,LED_SOURCE,LED_OFF},
    {DIO_u8PORTA, DIO_u8PIN2,LED_SOURCE,LED_OFF},
};