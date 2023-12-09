#ifndef WDT_PRIV_H_
#define WDT_PRIV_H_

#define WDT_SLEEP_16_3ms    0
#define WDT_SLEEP_32_5ms    1
#define WDT_SLEEP_65ms      2
#define WDT_SLEEP_130ms     3
#define WDT_SLEEP_260ms     4
#define WDT_SLEEP_520ms     5
#define WDT_SLEEP_1s        6
#define WDT_SLEEP_2_1s      7


#define WDTCR *((volatile u8*)0x41)
#define WDP0 0
#define WDP1 1
#define WDP2 2
#define WDE 3
#define WDTOE 4

#endif /* WDT_PRIV_H_ */
