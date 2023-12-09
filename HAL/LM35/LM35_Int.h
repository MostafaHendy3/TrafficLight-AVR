#ifndef LM35_INT_H_
#define LM35_INT_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"
#include "../../MCAL/ADC/ADC_int.h"

ES_t LM35_Init(void);
ES_t LM35_GetTemp(u8 *pu8_Temp);

#endif /* LM35_INT_H_ */
