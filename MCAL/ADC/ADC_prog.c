#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "ADC_config.h"
#include "ADC_priv.h"

#include "../Intterupt.h"

static void (*ADC_pfunISRFunction)(void *) = NULL;
static void *ADC_pvidISRParameter = NULL;
static u8 *ADC_Reading = NULL;
u8 ADC_State = IDLE;

// chain conversion
static u8 index = 0;
static u8 enableChainConversion = 0;
static u8 ADC_chainSize =0;
static ADC_chain_t * ADC_Pchain = NULL;



ES_t ADC_enuInit(void)
{

        ES_t Local_enuErrorState = ES_NOK;
#if ADC_REF_VOLTAGE == AVCC
        ADMUX |= (1 << REFS0);
        ADMUX &= ~(1 << REFS1);
#elif ADC_REF_VOLTAGE == AREF
        ADMUX &= ~(1 << REFS0);
        ADMUX &= ~(1 << REFS1);
#elif ADC_REF_VOLTAGE == INTERNAL
        ADMUX |= (1 << REFS0);
        ADMUX |= (1 << REFS1);
#else
#error "ADC Error ref voltage"
#endif

#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
        ADMUX &= ~(1 << ADLAR);
#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
        ADMUX |= (1 << ADLAR);
#else
#error "ADC Error Adjusment"
#endif

#if ADC_PRESCALER == DIVISION_FACTOR_2
        ADCSRA |= (1 << ADPS0);
        ADCSRA &= ~(1 << ADPS1);
        ADCSRA &= ~(1 << ADPS2);
#elif ADC_PRESCALER == DIVISION_FACTOR_4
        ADCSRA &= ~(1 << ADPS0);
        ADCSRA |= (1 << ADPS1);
        ADCSRA &= ~(1 << ADPS2);
#elif ADC_PRESCALER == DIVISION_FACTOR_8
        ADCSRA |= (1 << ADPS0);
        ADCSRA |= (1 << ADPS1);
        ADCSRA &= ~(1 << ADPS2);
#elif ADC_PRESCALER == DIVISION_FACTOR_16
        ADCSRA &= ~(1 << ADPS0);
        ADCSRA &= ~(1 << ADPS1);
        ADCSRA |= (1 << ADPS2);
#elif ADC_PRESCALER == DIVISION_FACTOR_32
        ADCSRA |= (1 << ADPS0);
        ADCSRA &= ~(1 << ADPS1);
        ADCSRA |= (1 << ADPS2);
#elif ADC_PRESCALER == DIVISION_FACTOR_64
        ADCSRA &= ~(1 << ADPS0);
        ADCSRA |= (1 << ADPS1);
        ADCSRA |= (1 << ADPS2);
#elif ADC_PRESCALER == DIVISION_FACTOR_128
        ADCSRA |= (1 << ADPS0);
        ADCSRA |= (1 << ADPS1);
        ADCSRA |= (1 << ADPS2);
#else
#error "ADC Error preScaler"
#endif

        return Local_enuErrorState;
}
ES_t ADC_enuStartConversion_Sync(u8 Copy_u8Channel, u16 *Result)
{
        ES_t Local_enuErrorState = ES_NOK;
        if (ADC_State == IDLE)
        {
                ADC_State = BUSY;
                u32 local_counter = 0;
                if (Copy_u8Channel > 7)
                {
                        Local_enuErrorState = ES_OUT_OF_RANGE;
                }
                else
                {
                        ADMUX &= ~0x1F;
                        ADMUX |= Copy_u8Channel;
                        Local_enuErrorState = ES_OK;
                }
                // start Conversion
                ADCSRA |= (1 << ADSC);
                // polling System
                while (((ADCSRA >> ADIF) == 0) && local_counter != ADC_TIMEOUT)
                {
                        local_counter++;
                }
                if (local_counter == ADC_TIMEOUT)
                {
                        Local_enuErrorState = ES_NOK;
                }
                else
                {
                        // clear conversion complete flag
                        ADCSRA |= (1 << ADIF);
// read VALUE
#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
                        *Result = ADCL;
                        *Result |= ((u16)ADCH << 8);
#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
                        *Result = (ADCL >> 6);
                        *Result |= ((u16)ADCH << 2);
#endif
                        ADC_State = IDLE;
                }
        }
        else
        {
                Local_enuErrorState = ES_BUSY;
        }
        return Local_enuErrorState;
}
ES_t ADC_enuStartConversion_ASync(u8 Copy_u8Channel, u8 *Reading, void (*Copy_pfunCallBack)(void *), void *Copy_pvidParameter)
{
        ES_t Local_enuErrorState = ES_NOK;
        if (ADC_State == IDLE)
        {
                if (Copy_u8Channel > 7)
                {
                        Local_enuErrorState = ES_OUT_OF_RANGE;
                }
                else if (Copy_pfunCallBack == NULL)
                {
                        Local_enuErrorState = ES_NULL_POINTER;
                }
                else
                {
                        ADC_State = BUSY;
                        ADC_Reading = Reading;
                        ADC_pfunISRFunction = Copy_pfunCallBack;
                        ADC_pvidISRParameter = Copy_pvidParameter;
                        // select channel
                        ADMUX &= ~0x1F;
                        ADMUX |= Copy_u8Channel;
                        // start Conversion
                        ADCSRA |= (1 << ADSC);
                        // enable interrupt
                        ADCSRA |= (1 << ADIE);
                        // set callback function
                        Local_enuErrorState = ES_OK;
                }
        }
        else
        {
                Local_enuErrorState = ES_BUSY;
        }
        return Local_enuErrorState;
}
ES_t ADC_enuStartChainConversion(ADC_chain_t (*ADC_chain)[4], u8 size, void (*Copy_pfunCallBack)(void *), void *Copy_pvidParameter)
{
        ES_t Local_enuErrorState = ES_NOK;
        if (ADC_State == IDLE)
        {
                ADC_State = BUSY;
                enableChainConversion = 1;
                if (Copy_pfunCallBack == NULL)
                {
                        Local_enuErrorState = ES_NULL_POINTER;
                }
                if (ADC_chain[0]->u8ADC_ChannelID > 7)
                {
                        Local_enuErrorState = ES_OUT_OF_RANGE;
                }
                else
                {
                        ADC_pfunISRFunction = Copy_pfunCallBack;
                        ADC_pvidISRParameter = Copy_pvidParameter;
                        ADC_chainSize = size;
                        ADC_Pchain = ADC_chain[0];
                        ADMUX &= ~0x1F;
                        ADMUX |= ADC_chain[0]->u8ADC_ChannelID;
                        ADCSRA |= (1 << ADSC);
                        ADCSRA |= (1 << ADIE);
                }
        }
        return Local_enuErrorState;
}

ES_t ADC_enuStartConversion(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA |= (1 << ADSC);
        return Local_enuErrorState;
}
ES_t ADC_enuPollingSystem(void)
{
        // wait on flag and clear it if it's high
        // clear flag by writing one to flag
        ES_t Local_enuErrorState = ES_NOK;
        while ((ADCSRA >> ADIF) == 0)
                ;
        ADCSRA |= (1 << ADIF);
        return Local_enuErrorState;
}
ES_t ADC_enuReadHighValue(u8 *Copy_pu8Value)
{
        ES_t Local_enuErrorState = ES_NOK;

#if ADC_ADJUSTMENT == LEFT_ADJUSTMENT
        *Copy_pu8Value = ADCH;
#elif ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
        // Right shifting ADCL
        *Copy_pu8Value = (ADCL >> 2);
        // or with ADCH left shifted
        *Copy_pu8Value |= (ADCH << 6);

#endif
        return Local_enuErrorState;
}
ES_t ADC_enuRead(u16 *Copy_pu16Value)
{
        ES_t Local_enuErrorState = ES_NOK;
#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
        *Copy_pu16Value = ADCL;
        *Copy_pu16Value |= ((u16)ADCH << 8);
#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
        *Copy_pu16Value = (ADCL >> 6);
        *Copy_pu16Value |= (ADCH << 2);
#endif
        return Local_enuErrorState;
}
ES_t ADC_enuCallBack(void (*copy_pfunAppFun)(void *), void *copy_pvidAppParameter)
{
        ES_t Local_enuErrorState = ES_NOK;
        if (copy_pfunAppFun != NULL)
        {
                ADC_pfunISRFunction = copy_pfunAppFun;
                ADC_pvidISRParameter = copy_pvidAppParameter;
        }
        else
        {
                Local_enuErrorState = ES_NULL_POINTER;
        }
        return Local_enuErrorState;
}
ES_t ADC_enuEnableADC(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA |= (1 << ADEN);
        return Local_enuErrorState;
}
ES_t ADC_enuDisableADC(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA &= ~(1 << ADEN);
        return Local_enuErrorState;
}
ES_t ADC_enuEnableInterruptMode(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA |= (1 << ADIE);
        return Local_enuErrorState;
}
ES_t ADC_enuDisableInterruptMode(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA &= ~(1 << ADIE);
        return Local_enuErrorState;
}
ES_t ADC_enuSelectChannel(u8 copy_u8channelID)
{
        ES_t Local_enuErrorState = ES_NOK;
        if (copy_u8channelID > 7)
        {
                Local_enuErrorState = ES_OUT_OF_RANGE;
        }
        else
        {
                ADMUX &= ~0x1F;
                ADMUX |= copy_u8channelID;
                Local_enuErrorState = ES_OK;
        }

        return Local_enuErrorState;
}
ES_t ADC_enuEnableTriggeringMode(u8 copy_u8TriggerSource)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA |= (1 << ADATE);
        switch (copy_u8TriggerSource)
        {
        case FREE_RUNNING_MODE:
                SFIOR &= ~(1 << ADTS0);
                SFIOR &= ~(1 << ADTS1);
                SFIOR &= ~(1 << ADTS2);
                break;
        case ANALOG_COMPARATOR:
                SFIOR |= (1 << ADTS0);
                SFIOR &= ~(1 << ADTS1);
                SFIOR &= ~(1 << ADTS2);
                break;
        case EXTERNAL_INTERRUPT_REQUEST_0:
                SFIOR &= ~(1 << ADTS0);
                SFIOR |= (1 << ADTS1);
                SFIOR &= ~(1 << ADTS2);
                break;
        case TIMER_COUNTER0_COMPARE_MATCH:
                SFIOR |= (1 << ADTS0);
                SFIOR |= (1 << ADTS1);
                SFIOR &= ~(1 << ADTS2);
                break;
        case TIMER_COUNTER0_OVERFLOW:
                SFIOR &= ~(1 << ADTS0);
                SFIOR &= ~(1 << ADTS1);
                SFIOR |= (1 << ADTS2);
                break;
        case TIMER_COUNTER1_COMPARE_MATCH_B:
                SFIOR |= (1 << ADTS0);
                SFIOR &= ~(1 << ADTS1);
                SFIOR |= (1 << ADTS2);
                break;
        case TIMER_COUNTER1_OVERFLOW:
                SFIOR &= ~(1 << ADTS0);
                SFIOR |= (1 << ADTS1);
                SFIOR |= (1 << ADTS2);
                break;
        case TIMER_COUNTER1_CAPTURE_EVENT:
                SFIOR |= (1 << ADTS0);
                SFIOR |= (1 << ADTS1);
                SFIOR |= (1 << ADTS2);
                break;
        default:
                Local_enuErrorState = ES_OUT_OF_RANGE;
                break;
        }
        return Local_enuErrorState;
}
ES_t ADC_enuDisableTriggeringMode(void)
{
        ES_t Local_enuErrorState = ES_NOK;
        ADCSRA &= ~(1 << ADATE);
        return Local_enuErrorState;
}

ISR(ADC_vect)
{
        if (enableChainConversion == 1)
        {
                if (index < ADC_chainSize)
                {
                        *ADC_Pchain[index].arr_result = ADCH;
                        index++;
                        if(ADC_Pchain[index].u8ADC_ChannelID <8){
                                ADMUX &= ~0x1F;
                                ADMUX |= ADC_Pchain[index].u8ADC_ChannelID;
                                ADCSRA |= (1 << ADSC);
                        }
                }
                else if (index == ADC_chainSize)
                {
                        if (ADC_pfunISRFunction != NULL)
                        {
                                ADC_pfunISRFunction(ADC_pvidISRParameter);
                                // clear flag
                                ADCSRA |= (1 << ADIF);
                                ADC_State = IDLE;
                                index = 0;
                                enableChainConversion = 0;
                        }
                }
        }
        else
        {
                if (ADC_pfunISRFunction != NULL)
                {
                        *ADC_Reading = ADCH;
                        ADC_pfunISRFunction(ADC_pvidISRParameter);
                        // clear flag
                        ADCSRA |= (1 << ADIF);
                        ADC_State = IDLE;
                }
        }
}