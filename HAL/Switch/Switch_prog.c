#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "Switch_priv.h"
#include "Switch_config.h"


ES_t Switch_enuInit(SW_t *Copy_AstrSwitchState)
{
    ES_t Local_enuErrorState = ES_NOK;
    u8 iterator;
    if (Copy_AstrSwitchState != NULL)
    {
        for (iterator = 0; iterator < SW_NUM; iterator++)
        {
            Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSwitchState[iterator].SW_PortID, Copy_AstrSwitchState[iterator].SW_PinID, DIO_u8INPUT);
            Local_enuErrorState = DIO_enuSetPinValue(Copy_AstrSwitchState[iterator].SW_PortID, Copy_AstrSwitchState[iterator].SW_PinID, Copy_AstrSwitchState[iterator].SW_Status);
        }
    }
    else
    {
        Local_enuErrorState = ES_NULL_POINTER;
    }
    return Local_enuErrorState;
}
ES_t Switch_enuGetState(SW_t *Copy_AstrSwitchState, u8 *Copy_pu8SwState)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_AstrSwitchState != NULL && Copy_pu8SwState !=NULL)
    {
        Local_enuErrorState = DIO_enuGetPinValue(Copy_AstrSwitchState->SW_PortID, Copy_AstrSwitchState->SW_PinID, Copy_pu8SwState);       
    }
    else
    {
        Local_enuErrorState = ES_NULL_POINTER;
    }
    return Local_enuErrorState;
}