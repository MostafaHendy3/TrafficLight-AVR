#ifndef ADC_INT_H_
#define ADC_INT_H_

typedef struct 
{
    u8 u8ADC_ChannelID;
    u8 * arr_result;
}ADC_chain_t;


ES_t ADC_enuInit(void); 
ES_t ADC_enuStartConversion(void);
ES_t ADC_enuStartConversion_Sync(u8 Copy_u8Channel,u16 * Result);
ES_t ADC_enuStartConversion_ASync(u8 Copy_u8Channel,u8 * Reading,void (*Copy_pfunCallBack)(void *), void *Copy_pvidParameter);
ES_t ADC_enuStartChainConversion(ADC_chain_t (*)[4], u8 size, void (*Copy_pfunCallBack)(void *), void *Copy_pvidParameter);

ES_t ADC_enuPollingSystem(void);
ES_t ADC_enuReadHighValue(u8 * Copy_pu8Value);
ES_t ADC_enuRead(u16 * Copy_pu16Value);
ES_t ADC_enuCallBack(void (*copy_pfunAppFun)(void *),void *copy_pvidAppParameter);
ES_t ADC_enuEnableADC(void);
ES_t ADC_enuDisableADC(void);
ES_t ADC_enuEnableInterruptMode(void);
ES_t ADC_enuDisableInterruptMode(void);
ES_t ADC_enuSelectChannel(u8 copy_u8channelID);
ES_t ADC_enuEnableTriggeringMode(u8 copy_u8TriggerSource);
ES_t ADC_enuDisableTriggeringMode(void);

#define FREE_RUNNING_MODE 0
#define ANALOG_COMPARATOR 1
#define EXTERNAL_INTERRUPT_REQUEST_0 2
#define TIMER_COUNTER0_COMPARE_MATCH 3
#define TIMER_COUNTER0_OVERFLOW 4
#define TIMER_COUNTER1_COMPARE_MATCH_B 5
#define TIMER_COUNTER1_OVERFLOW 6
#define TIMER_COUNTER1_CAPTURE_EVENT 7

#endif /* ADC_INT_H_ */
