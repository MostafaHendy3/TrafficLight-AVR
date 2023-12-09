// libraries
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"
// MCAL
#include "../../MCAL/DIO/DIO_int.h"
// HAL
#include "LCD_priv.h"
#include "LCD_config.h"
#include <util/delay.h>

ES_t LCD_enuInit(void)
{
    ES_t Local_enuErrorState = ES_NOK;

    DIO_enuSetPinDirection(RS_PORT, RS_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinDirection(RW_PORT, RW_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinDirection(E_PORT, E_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinDirection(D4_PORT, D4_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinDirection(D5_PORT, D5_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinDirection(D6_PORT, D6_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinDirection(D7_PORT, D7_PIN, DIO_u8OUTPUT);
    _delay_ms(35);
#if LCD_MODE == EightBitMode
    DIO_enuSetPinDirection(D0_PORT, D0_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinDirection(D1_PORT, D1_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinDirection(D2_PORT, D2_PIN, DIO_u8OUTPUT);
    DIO_enuSetPinDirection(D3_PORT, D3_PIN, DIO_u8OUTPUT);

    // function set
    LCD_invidSendCommand(0x38);

#elif LCD_MODE == FourBitMode
    LCD_invidSendCommand(0x28);

#else
#error "Wrong LCD_MODE"
#endif
    _delay_ms(1);
    LCD_invidSendCommand(ON_OFF);
    _delay_ms(1);
    LCD_invidSendCommand(CLEAR);
    _delay_ms(2);
    LCD_invidSendCommand(EntrySetMode);

    return Local_enuErrorState;
}

ES_t LCD_enuDisplayChar(u8 Copy_u8Data)
{
    ES_t Local_enuErrorState = ES_NOK;

    DIO_enuSetPinValue(RS_PORT, RS_PIN, DIO_u8HIGH);
    LCD_Latch(Copy_u8Data);
    return Local_enuErrorState;
}

ES_t LCD_enuDisplayIntegerNumber(s32 Copy_s32Num)
{
    ES_t Local_enuErrorState =ES_NOK;
    u8 buffer[10];
    u8 size =0;
    DIO_enuSetPinValue(RS_PORT, RS_PIN, DIO_u8HIGH);
    while(Copy_s32Num!=0){
        buffer[size]=Copy_s32Num%10;
        size++;
        Copy_s32Num/=10;
    }
    for(int i =size-1;i>=0;i--){
        LCD_Latch(buffer[i]+'0');
    }
    return Local_enuErrorState;
}

ES_t LCD_enuSendCommand(u8 Copy_u8Command)
{
    ES_t Local_enuErrorState = ES_NOK;
    DIO_enuSetPinValue(RS_PORT, RS_PIN, DIO_u8LOW);
    LCD_Latch(Copy_u8Command);

    return Local_enuErrorState;
}

static inline void LCD_invidSendCommand(u8 Copy_u8Command)
{
    // set E to low
    // set RS to Command
    DIO_enuSetPinValue(RS_PORT, RS_PIN, DIO_u8LOW);
    // set RW to write
    DIO_enuSetPinValue(RW_PORT, RW_PIN, DIO_u8LOW);
    DIO_enuSetPinValue(E_PORT, E_PIN, DIO_u8LOW);

    // write command
    DIO_enuSetPinValue(D0_PORT, D0_PIN, (Copy_u8Command >> 0) & 1);
    DIO_enuSetPinValue(D1_PORT, D1_PIN, (Copy_u8Command >> 1) & 1);
    DIO_enuSetPinValue(D2_PORT, D2_PIN, (Copy_u8Command >> 2) & 1);
    DIO_enuSetPinValue(D3_PORT, D3_PIN, (Copy_u8Command >> 3) & 1);
    DIO_enuSetPinValue(D4_PORT, D4_PIN, (Copy_u8Command >> 4) & 1);
    DIO_enuSetPinValue(D5_PORT, D5_PIN, (Copy_u8Command >> 5) & 1);
    DIO_enuSetPinValue(D6_PORT, D6_PIN, (Copy_u8Command >> 6) & 1);
    DIO_enuSetPinValue(D7_PORT, D7_PIN, (Copy_u8Command >> 7) & 1);
    // set E to high
    DIO_enuSetPinValue(E_PORT, E_PIN, DIO_u8HIGH);
    _delay_ms(10);
    // set E to low
    DIO_enuSetPinValue(E_PORT, E_PIN, DIO_u8LOW);
}

static void LCD_Latch(u8 Copy_u8Data)
{
    // set RS to Command
    DIO_enuSetPinValue(RW_PORT, RW_PIN, DIO_u8LOW);
    // set RW to write
    DIO_enuSetPinValue(E_PORT, E_PIN, DIO_u8LOW);
    // write command
    DIO_enuSetPinValue(D4_PORT, D4_PIN, (Copy_u8Data >> 4) & 1);
    DIO_enuSetPinValue(D5_PORT, D5_PIN, (Copy_u8Data >> 5) & 1);
    DIO_enuSetPinValue(D6_PORT, D6_PIN, (Copy_u8Data >> 6) & 1);
    DIO_enuSetPinValue(D7_PORT, D7_PIN, (Copy_u8Data >> 7) & 1);
#if LCD_MODE == EightBitMode

    DIO_enuSetPinValue(D0_PORT, D0_PIN, (Copy_u8Data >> 0) & 1);
    DIO_enuSetPinValue(D1_PORT, D1_PIN, (Copy_u8Data >> 1) & 1);
    DIO_enuSetPinValue(D2_PORT, D2_PIN, (Copy_u8Data >> 2) & 1);
    DIO_enuSetPinValue(D3_PORT, D3_PIN, (Copy_u8Data >> 3) & 1);
#elif LCD_MODE == FourBitMode

#else
#error "Wrong LCD_MODE"
#endif
    // set E to high
    DIO_enuSetPinValue(E_PORT, E_PIN, DIO_u8HIGH);
    _delay_ms(10);
    // set E to low
    DIO_enuSetPinValue(E_PORT, E_PIN, DIO_u8LOW);
    _delay_ms(10);
}

ES_t LCD_enuClear(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    LCD_invidSendCommand(CLEAR);
    return Local_enuErrorState;
}
ES_t LCD_enuGoHome(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    LCD_invidSendCommand(HOME_Command);
    return Local_enuErrorState;
}
