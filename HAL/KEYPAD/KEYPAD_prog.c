#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../../MCAL/DIO/DIO_Int.h"

#include "KEYPAD_config.h"
#include "KEYPAD_priv.h"


ES_t KEYPAD_Init(void){
    ES_t Local_u8ErrorState = ES_NOK;
    DIO_enuSetPinDirection(KEYPAD_PORT,KEYPAD_ROW_PIN0,DIO_u8INPUT);
    DIO_enuSetPinDirection(KEYPAD_PORT,KEYPAD_ROW_PIN1,DIO_u8INPUT);
    DIO_enuSetPinDirection(KEYPAD_PORT,KEYPAD_ROW_PIN2,DIO_u8INPUT);
    DIO_enuSetPinDirection(KEYPAD_PORT,KEYPAD_ROW_PIN3,DIO_u8INPUT);
    DIO_enuSetPinDirection(KEYPAD_PORT,KEYPAD_COL_PIN0,DIO_u8OUTPUT);
    DIO_enuSetPinDirection(KEYPAD_PORT,KEYPAD_COL_PIN1,DIO_u8OUTPUT);
    DIO_enuSetPinDirection(KEYPAD_PORT,KEYPAD_COL_PIN2,DIO_u8OUTPUT);
    DIO_enuSetPinDirection(KEYPAD_PORT,KEYPAD_COL_PIN3,DIO_u8OUTPUT);

    DIO_enuSetPinValue(KEYPAD_PORT,KEYPAD_ROW_PIN0,DIO_u8HIGH);
    DIO_enuSetPinValue(KEYPAD_PORT,KEYPAD_ROW_PIN1,DIO_u8HIGH);
    DIO_enuSetPinValue(KEYPAD_PORT,KEYPAD_ROW_PIN2,DIO_u8HIGH);
    DIO_enuSetPinValue(KEYPAD_PORT,KEYPAD_ROW_PIN3,DIO_u8HIGH);

    DIO_enuSetPinValue(KEYPAD_PORT,KEYPAD_COL_PIN0,DIO_u8HIGH);
    DIO_enuSetPinValue(KEYPAD_PORT,KEYPAD_COL_PIN1,DIO_u8HIGH);
    DIO_enuSetPinValue(KEYPAD_PORT,KEYPAD_COL_PIN2,DIO_u8HIGH);
    DIO_enuSetPinValue(KEYPAD_PORT,KEYPAD_COL_PIN3,DIO_u8HIGH);

    return Local_u8ErrorState;
}
ES_t KEYPAD_GetPressedKey(u8 *pu8_key){
    ES_t Local_u8ErrorState = ES_NOK;

    static u8 local_u8PressedKey,local_iterator_raw,local_iterator_col,local_u8PinState;
    local_u8PressedKey = KEYPAD_NO_PRESSED_KEY;
    static u8 local_Au8ColArray[KEYPAD_COLS_NUM] ={
        KEYPAD_COL_PIN0,
        KEYPAD_COL_PIN1,
        KEYPAD_COL_PIN2,
        KEYPAD_COL_PIN3
    };
    static u8 local_Au8RawArray[KEYPAD_ROWS_NUM] ={
        KEYPAD_ROW_PIN0,
        KEYPAD_ROW_PIN1,
        KEYPAD_ROW_PIN2,
        KEYPAD_ROW_PIN3
    };
    static u8 local_Au8KPD_ARY[KEYPAD_ROWS_NUM][KEYPAD_COLS_NUM] = KPD_ARY_VAL;

    for(local_iterator_col=0;local_iterator_col<KEYPAD_COLS_NUM;local_iterator_col++){
        /*Activate Column*/
        
        DIO_enuSetPinValue(KEYPAD_PORT, local_Au8ColArray[local_iterator_col],DIO_u8LOW);
        for(local_iterator_raw=0;local_iterator_raw<KEYPAD_ROWS_NUM;local_iterator_raw++){
            DIO_enuGetPinValue(KEYPAD_PORT,local_Au8RawArray[local_iterator_raw],&local_u8PinState);
            if(DIO_u8LOW == local_u8PinState){
                while (local_u8PinState == DIO_u8LOW)
                {               
                    DIO_enuGetPinValue(KEYPAD_PORT,local_Au8RawArray[local_iterator_raw],&local_u8PinState);
                }
                *pu8_key = local_Au8KPD_ARY[local_iterator_raw][local_iterator_col];
                Local_u8ErrorState =ES_OK;
                return Local_u8ErrorState;
            }
            else{
                local_u8PressedKey = KEYPAD_NO_PRESSED_KEY;
            }
        }
        /*Deactivate Column*/
        DIO_enuSetPinValue(KEYPAD_PORT,local_Au8ColArray[local_iterator_col],DIO_u8HIGH);
    }
    *pu8_key = local_u8PressedKey;

    return Local_u8ErrorState;   
}
