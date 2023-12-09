#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "WDT_Int.h"
#include "WDT_priv.h"

ES_t WDT_Enable(void){
    ES_t Local_enuErrorState = ES_NOK;
    WDTCR |= (1<<WDE);
    Local_enuErrorState = ES_OK;
    return Local_enuErrorState;
}
ES_t WDT_Disable(void){
    ES_t Local_enuErrorState = ES_NOK;
    WDTCR = 0b00011000;
    WDTCR = 0b00000000;
    Local_enuErrorState = ES_OK;
    return Local_enuErrorState;
}
ES_t WDT_Sleep(u8 Copy_u8Time){
    ES_t Local_enuErrorState = ES_NOK;
    WDTCR &= 0b11111000;
    WDTCR |= Copy_u8Time;
    Local_enuErrorState = ES_OK;
    return Local_enuErrorState;
}