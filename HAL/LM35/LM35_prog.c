#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../../MCAL/DIO/DIO_Int.h"
#include "../../MCAL/ADC/ADC_int.h"

#include "LM35_priv.h"
#include "LM35_config.h"

ES_t LM35_Init(void){
    ES_t Local_enuErrorState = ES_NOK;
    Local_enuErrorState =ADC_enuEnableADC();
    Local_enuErrorState = ADC_enuInit();
    return Local_enuErrorState;
}
ES_t LM35_GetTemp(u8 *pu8_Temp){
    ES_t Local_enuErrorState = ES_NOK;
    u16 Local_u16ADCResult = 0;
    if (pu8_Temp != NULL)
    {
        Local_enuErrorState = ADC_enuStartConversion_Sync(LM35_u8ADC_CHANNEL_ID, &Local_u16ADCResult);
        *pu8_Temp = (Local_u16ADCResult * 500) / 1024;
    }
    else
    {
        Local_enuErrorState = ES_NULL_POINTER;
    }
    return Local_enuErrorState;
}