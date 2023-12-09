#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

ES_t KEYPAD_Init(void);
ES_t KEYPAD_GetPressedKey(u8 *pu8_key);

#endif /* KEYPAD_INT_H_ */
