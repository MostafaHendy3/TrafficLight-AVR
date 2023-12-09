
#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"
#include "../../MCAL/DIO/DIO_int.h"

#include "LED_config.h"
#include "LED_priv.h"

ES_t LED_enuInit(LED_t *Copy_PAstrLEDState)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_PAstrLEDState != NULL)
    {
        u8 local_Iterator = 0;
        for (local_Iterator = 0; local_Iterator < LED_NUM; local_Iterator++)
        {
            Local_enuErrorState = DIO_enuSetPinValue(Copy_PAstrLEDState[local_Iterator].LED_u8Port, Copy_PAstrLEDState[local_Iterator].LED_u8Pin, Copy_PAstrLEDState[local_Iterator].LED_u8InitStatus);
            if (Copy_PAstrLEDState[local_Iterator].LED_u8Connection == LED_SINK)
            {
                if (Copy_PAstrLEDState[local_Iterator].LED_u8InitStatus == LED_ON)
                {
                    Local_enuErrorState = DIO_enuSetPinValue(Copy_PAstrLEDState[local_Iterator].LED_u8Port, Copy_PAstrLEDState[local_Iterator].LED_u8Pin, DIO_u8LOW);
                }
                else if (Copy_PAstrLEDState[local_Iterator].LED_u8InitStatus == LED_OFF)
                {
                    Local_enuErrorState = DIO_enuSetPinValue(Copy_PAstrLEDState[local_Iterator].LED_u8Port, Copy_PAstrLEDState[local_Iterator].LED_u8Pin, DIO_u8HIGH);
                }
                else
                {
                    Local_enuErrorState = ES_OUT_OF_RANGE;
                }
            }
            else if (Copy_PAstrLEDState[local_Iterator].LED_u8Connection == LED_SOURCE)
            {
                if (Copy_PAstrLEDState[local_Iterator].LED_u8InitStatus == LED_ON)
                {
                    Local_enuErrorState = DIO_enuSetPinValue(Copy_PAstrLEDState[local_Iterator].LED_u8Port, Copy_PAstrLEDState[local_Iterator].LED_u8Pin, DIO_u8HIGH);
                }
                else if (Copy_PAstrLEDState[local_Iterator].LED_u8InitStatus == LED_OFF)
                {
                    Local_enuErrorState = DIO_enuSetPinValue(Copy_PAstrLEDState[local_Iterator].LED_u8Port, Copy_PAstrLEDState[local_Iterator].LED_u8Pin, DIO_u8LOW);
                }
                else
                {
                    Local_enuErrorState = ES_OUT_OF_RANGE;
                }
            }
            else
            {
                Local_enuErrorState = ES_OUT_OF_RANGE;
            }
        }
    }
    else
    {
        Local_enuErrorState = ES_NULL_POINTER;
    }
    return Local_enuErrorState;
}
ES_t LED_enuSetLedOn(LED_t *Copy_PstrLEDID)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_PstrLEDID != NULL)
    {
        if (Copy_PstrLEDID->LED_u8Connection == LED_SINK)
        {
            Local_enuErrorState=DIO_enuSetPinValue(Copy_PstrLEDID->LED_u8Port, Copy_PstrLEDID->LED_u8Pin, DIO_u8LOW);
        }
        else if (Copy_PstrLEDID->LED_u8Connection == LED_SOURCE)
        {
            Local_enuErrorState=DIO_enuSetPinValue(Copy_PstrLEDID->LED_u8Port, Copy_PstrLEDID->LED_u8Pin, DIO_u8HIGH);
        }
        else
        {
            Local_enuErrorState = ES_OUT_OF_RANGE;
        }
    }
    else
    {
        Local_enuErrorState = ES_NULL_POINTER;
    }
    return Local_enuErrorState;
}
ES_t LED_enuSetLedOff(LED_t *Copy_PstrLEDID)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_PstrLEDID != NULL)
    {

        if (Copy_PstrLEDID->LED_u8Connection == LED_SINK)
        {
           Local_enuErrorState= DIO_enuSetPinValue(Copy_PstrLEDID->LED_u8Port, Copy_PstrLEDID->LED_u8Pin, DIO_u8HIGH);
        }
        else if (Copy_PstrLEDID->LED_u8Connection == LED_SOURCE)
        {
           Local_enuErrorState= DIO_enuSetPinValue(Copy_PstrLEDID->LED_u8Port, Copy_PstrLEDID->LED_u8Pin, DIO_u8LOW);
        }
        else
        {
            Local_enuErrorState = ES_OUT_OF_RANGE;
        }
    }
    else
    {
        Local_enuErrorState = ES_NULL_POINTER;
    }
    return Local_enuErrorState;
}
