#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"
#include "GIE_priv.h"

ES_t GIE_voidEnable(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    SREG |= (1 << 7);
    Local_enuErrorState = ES_OK;
    return Local_enuErrorState;
}
ES_t GIE_voidDisable(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    SREG &= ~(1 << 7);
    Local_enuErrorState = ES_OK;
    return Local_enuErrorState;
}