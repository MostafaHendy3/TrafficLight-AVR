#ifndef TIMER_INT_H_
#define TIMER_INT_H_

#define Rising_edge 0
#define Falling_edge 1

ES_t TIMER0_init(void);
ES_t TIMER0_enuSetPreload(u8 Copy_u8Value);
ES_t TIMER0_enuSetASyncDelay(u32 Copy_u8Time,void (*func)(void),void *Copy_pvidParameter);
ES_t TIMER0_enuSetSyncDelay(u32 Copy_u8Time); 
ES_t TIMER0_GeneratePWM(u8 Copy_u8DutyCycle);
ES_t TIMER0_setCompareValue(u8 Copy_u8Value);
ES_t TIMER0_callBack(void (*func)(void),void *Copy_pvidParameter);

ES_t TIMER1_init(void);
ES_t TIMER1_GetTimerValue(u16 *Copy_pu16Value);
ES_t TIMER1_SetTimerValue(u16 Copy_u16Value);
ES_t TIMER1_callBack(void (*func)(void), void *Copy_pvidParameter);


ES_t ICU_Init();
ES_t ICU_enuSetEdge(u8 Copy_u8Edge);
ES_t ICU_enuEnableINT();
ES_t ICU_enuDisableINT();
ES_t ICU_enuReadInputCapture(u16 * Copy_pu16Value);
ES_t ICU_enuSetCallBack(void (*func)(void), void *Copy_pvidParameter);

#endif /* TIMER_INT_H_ */
