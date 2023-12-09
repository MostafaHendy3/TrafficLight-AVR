
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "SS_LT_priv.h"
#include "SS_LT_config.h"

extern SEVEN_SEGMENT_t SS_LT_AstrConfig[SEG_NUM];

ES_t SevenSegement_Init(SEVEN_SEGMENT_t *Copy_AstrSS_LTState)
{
    ES_t Local_enuErrorState = ES_NOK;

    if (Copy_AstrSS_LTState != NULL)
    {
        u8 local_u8LoopCounter = 0;
        for (local_u8LoopCounter = 0; local_u8LoopCounter < SEG_NUM; local_u8LoopCounter++)
        {
            Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_APORT, Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_APIN, DIO_u8OUTPUT);
            Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_BPORT, Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_BPIN, DIO_u8OUTPUT);
            Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_CPORT, Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_CPIN, DIO_u8OUTPUT);
            Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_DPORT, Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_DPIN, DIO_u8OUTPUT);
            Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_EPORT, Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_EPIN, DIO_u8OUTPUT);
            Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_FPORT, Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_FPIN, DIO_u8OUTPUT);
            Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_GPORT, Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_GPIN, DIO_u8OUTPUT);

            if (Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_COMPORT != NOT_CONNECTED && Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_COM != NOT_CONNECTED)
            {
                Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_COMPORT, Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_COM, DIO_u8OUTPUT);
            }
            if (Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_DOTPORT != NOT_CONNECTED && Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_DOT != NOT_CONNECTED)
            {
                Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_DOTPORT, Copy_AstrSS_LTState[local_u8LoopCounter].SS_LT_DOT, DIO_u8OUTPUT);
            }
        }
    }
    return Local_enuErrorState;
}
ES_t SevenSegement_enuDisplayNum(u8 Copy_u8SEGIndex, u8 Copy_u8Num)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_u8Num < 10 && Copy_u8SEGIndex < SEG_NUM)
    {
        if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_CATHODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_APORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_APIN, (Seg_Au8NumberDisplay[Copy_u8Num] >> 0) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_BPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_BPIN, (Seg_Au8NumberDisplay[Copy_u8Num] >> 1) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_CPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_CPIN, (Seg_Au8NumberDisplay[Copy_u8Num] >> 2) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DPIN, (Seg_Au8NumberDisplay[Copy_u8Num] >> 3) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_EPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_EPIN, (Seg_Au8NumberDisplay[Copy_u8Num] >> 4) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_FPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_FPIN, (Seg_Au8NumberDisplay[Copy_u8Num] >> 5) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_GPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_GPIN, (Seg_Au8NumberDisplay[Copy_u8Num] >> 6) & 1);
        }
        else if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_ANODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_APORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_APIN, !(Seg_Au8NumberDisplay[Copy_u8Num] >> 0) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_BPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_BPIN, !(Seg_Au8NumberDisplay[Copy_u8Num] >> 1) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_CPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_CPIN, !(Seg_Au8NumberDisplay[Copy_u8Num] >> 2) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DPIN, !(Seg_Au8NumberDisplay[Copy_u8Num] >> 3) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_EPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_EPIN, !(Seg_Au8NumberDisplay[Copy_u8Num] >> 4) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_FPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_FPIN, !(Seg_Au8NumberDisplay[Copy_u8Num] >> 5) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_GPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_GPIN, !(Seg_Au8NumberDisplay[Copy_u8Num] >> 6) & 1);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOTPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT, !(Seg_Au8NumberDisplay[Copy_u8Num] >> 7) & 1);
        }
        else
        {
            Local_enuErrorState = ES_ERROR_TYPE;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorState;
}
ES_t SevenSegement_enuEnableCommon(u8 Copy_u8SEGIndex)
{
    ES_t Local_enuErrorState = ES_NOK;

    if (Copy_u8SEGIndex < SEG_NUM && SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_COM != NOT_CONNECTED)
    {
        if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_CATHODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_COMPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_COM, DIO_u8HIGH);
        }
        else if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_ANODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_COMPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_COM, DIO_u8LOW);
        }
        else
        {
            Local_enuErrorState = ES_ERROR_TYPE;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }

    return Local_enuErrorState;
}
ES_t SevenSegement_enuDisableCommon(u8 Copy_u8SEGIndex)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_u8SEGIndex < SEG_NUM && SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_COM != NOT_CONNECTED)
    {
        if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_CATHODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_COMPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_COM, DIO_u8LOW);
        }
        else if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_ANODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_COMPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_COM, DIO_u8HIGH);
        }
        else
        {
            Local_enuErrorState = ES_ERROR_TYPE;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }

    return Local_enuErrorState;
}
ES_t SevenSegement_enuEnableDot(u8 Copy_u8SEGIndex)
{
    ES_t Local_enuErrorState = ES_NOK;

    if (Copy_u8SEGIndex < SEG_NUM && SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT != NOT_CONNECTED)
    {
        if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_CATHODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOTPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT, DIO_u8HIGH);
        }
        else if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_ANODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOTPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT, DIO_u8LOW);
        }
        else
        {
            Local_enuErrorState = ES_ERROR_TYPE;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }

    return Local_enuErrorState;
}
ES_t SevenSegement_enuDisableDot(u8 Copy_u8SEGIndex)
{
    ES_t Local_enuErrorState = ES_NOK;

    if (Copy_u8SEGIndex < SEG_NUM && SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT != NOT_CONNECTED)
    {
        if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_CATHODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOTPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT, DIO_u8LOW);
        }
        else if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_ANODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOTPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT, DIO_u8HIGH);
        }
        else
        {
            Local_enuErrorState = ES_ERROR_TYPE;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }

    return Local_enuErrorState;
}
ES_t SevenSegement_enuClear(u8 Copy_u8SEGIndex)
{
    ES_t Local_enuErrorState = ES_NOK;
    if (Copy_u8SEGIndex < SEG_NUM)
    {
        if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_CATHODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_APORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_APIN, DIO_u8LOW);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_BPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_BPIN, DIO_u8LOW);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_CPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_CPIN, DIO_u8LOW);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DPIN, DIO_u8LOW);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_EPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_EPIN, DIO_u8LOW);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_FPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_FPIN, DIO_u8LOW);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_GPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_GPIN, DIO_u8LOW);
            if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT != NOT_CONNECTED)
            {
                Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOTPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT, DIO_u8LOW);
            }
        }
        else if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_TYPE == COMMON_ANODE)
        {
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_APORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_APIN, DIO_u8HIGH);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_BPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_BPIN, DIO_u8HIGH);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_CPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_CPIN, DIO_u8HIGH);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DPIN, DIO_u8HIGH);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_EPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_EPIN, DIO_u8HIGH);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_FPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_FPIN, DIO_u8HIGH);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_GPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_GPIN, DIO_u8HIGH);
            Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOTPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT, DIO_u8HIGH);
            if (SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT != NOT_CONNECTED)
            {
                Local_enuErrorState = DIO_enuSetPinValue(SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOTPORT, SS_LT_AstrConfig[Copy_u8SEGIndex].SS_LT_DOT, DIO_u8HIGH);
            }
        }
        else
        {
            Local_enuErrorState = ES_ERROR_TYPE;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }

    return Local_enuErrorState;
}
