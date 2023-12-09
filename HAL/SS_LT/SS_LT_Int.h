#ifndef SS_LT_INT_H_
#define SS_LT_INT_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "SS_LT_Config.h"

ES_t SevenSegement_Init(SEVEN_SEGMENT_t * Copy_AstrSS_LTState);
ES_t SevenSegement_enuDisplayNum(u8 Copy_u8SEGIndex,u8 Copy_u8Num);
ES_t SevenSegement_enuEnableCommon(u8 Copy_u8SEGIndex);
ES_t SevenSegement_enuDisableCommon(u8 Copy_u8SEGIndex);
ES_t SevenSegement_enuEnableDot(u8 Copy_u8SEGIndex);
ES_t SevenSegement_enuDisableDot(u8 Copy_u8SEGIndex);
ES_t SevenSegement_enuClear(u8 Copy_u8SEGIndex);

#endif /* SS_LT_INT_H_ */
