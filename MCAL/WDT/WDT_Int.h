#ifndef WDT_INT_H_
#define WDT_INT_H_

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#define WDT_SLEEP_16_3ms    0
#define WDT_SLEEP_32_5ms    1
#define WDT_SLEEP_65ms      2
#define WDT_SLEEP_130ms     3
#define WDT_SLEEP_260ms     4
#define WDT_SLEEP_520ms     5
#define WDT_SLEEP_1s        6
#define WDT_SLEEP_2_1s      7

ES_t WDT_Enable();
ES_t WDT_Disable();
ES_t WDT_Sleep(u8 Copy_u8Time);
#endif /* WDT_INT_H_ */
