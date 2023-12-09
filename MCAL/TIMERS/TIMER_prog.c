#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../../MCAL/TIMERS/TIMER_priv.h"
#include "../../MCAL/TIMERS/TIMER_config.h"

#include "../Intterupt.h"

static void (*TIMER0_callBackPtr)() = NULL;
static void (*TIMER1_callBackPtr)() = NULL;
static void (*ICU_callBackPtr)() = NULL;

static void *TIMER0_callBackParameter = NULL;
static void *TIMER1_callBackParameter = NULL;
static void *ICU_callBackParameter = NULL;


static u32 gNum_OVF = 0;
static u32 gPreload = 0;

ES_t TIMER0_init(void)
{
    ES_t local_errorstate = ES_NOK;
    // choose mode
#if TIMER0_COMPARE_OUTPUT_MODE == NORMAL_PORT_OPERATION
    TCCR0 &= ~(1 << TCCR0_COM00);
    TCCR0 &= ~(1 << TCCR0_COM01);
#endif

#if TIMER0_WAVEFORM_GENERATION_MODE == NORMAL
    TCCR0 &= ~(1 << TCCR0_WGM00);
    TCCR0 &= ~(1 << TCCR0_WGM01);
#elif TIMER0_WAVEFORM_GENERATION_MODE == PWM_PHASE_CORRECT
    TCCR0 &= ~(1 << TCCR0_WGM01);
    TCCR0 |= (1 << TCCR0_WGM00);
#if TIMER0_COMPARE_OUTPUT_MODE == NON_INVERTING_SET_ON_COMP
    TCCR0 &= ~(1 << TCCR0_COM00);
    TCCR0 |= (1 << TCCR0_COM01);
#elif TIMER0_COMPARE_OUTPUT_MODE == INVERTING_CLR_ON_COMP
    TCCR0 |= (1 << TCCR0_COM00);
    TCCR0 &= ~(1 << TCCR0_COM01);
#endif
#elif TIMER0_WAVEFORM_GENERATION_MODE == CTC
    TCCR0 |= (1 << TCCR0_WGM01);
    TCCR0 &= ~(1 << TCCR0_WGM00);

#if TIMER0_COMPARE_OUTPUT_MODE == TOGGLE_OC0_ON_COMPARE_MATCH
    // CTC MODE
    TCCR0 |= (1 << TCCR0_COM00);
    TCCR0 &= ~(1 << TCCR0_COM01);
#elif TIMER0_COMPARE_OUTPUT_MODE == CLEAR_OC0_ON_COMPARE_MATCH
    // CTC MODE
    TCCR0 &= ~(1 << TCCR0_COM00);
    TCCR0 |= (1 << TCCR0_COM01);
#elif TIMER0_COMPARE_OUTPUT_MODE == SET_OC0_ON_COMPARE_MATCH
    // CTC MODE
    TCCR0 |= (1 << TCCR0_COM00);
    TCCR0 |= (1 << TCCR0_COM01);
#endif
#elif TIMER0_WAVEFORM_GENERATION_MODE == FAST_PWM
    TCCR0 |= (1 << TCCR0_WGM00);
    TCCR0 |= (1 << TCCR0_WGM01);
#if TIMER0_COMPARE_OUTPUT_MODE == NON_INVERTING_CLR_ON_COMP
    TCCR0 |= (1 << TCCR0_COM01);
    TCCR0 &= ~(1 << TCCR0_COM00);
#elif TIMER0_COMPARE_OUTPUT_MODE == INVERTING_SET_ON_COMP
    TCCR0 |= (1 << TCCR0_COM00);
    TCCR0 |= (1 << TCCR0_COM01);
#endif
#endif

#if TIMER0_INTERRUPT_ENABLE == OCIE0
    TIMSK |= (1 << OCIE0);
#elif TIMER0_INTERRUPT_ENABLE == TOIE0
    TIMSK |= (1 << TOIE0);
#elif TIMER0_INTERRUPT_ENABLE == NO_INTERRUTP
    TIMSK &= ~(1 << OCIE0);
    TIMSK &= ~(1 << TOIE0);
#endif

/*Set prescaler*/
#if TIMER0_PRESCALER == NO_CLOCK_SOURCE
    TCCR0 &= ~(1 << TCCR0_CS00);
    TCCR0 &= ~(1 << TCCR0_CS01);
    TCCR0 &= ~(1 << TCCR0_CS02);
#elif TIMER0_PRESCALER == NO_PRESCALING
    TCCR0 |= (1 << TCCR0_CS00);
    TCCR0 &= ~(1 << TCCR0_CS01);
    TCCR0 &= ~(1 << TCCR0_CS02);
#elif TIMER0_PRESCALER == PRESCALER_8
    TCCR0 &= ~(1 << TCCR0_CS00);
    TCCR0 |= (1 << TCCR0_CS01);
    TCCR0 &= ~(1 << TCCR0_CS02);
#elif TIMER0_PRESCALER == PRESCALER_64
    TCCR0 |= (1 << TCCR0_CS00);
    TCCR0 |= (1 << TCCR0_CS01);
    TCCR0 &= ~(1 << TCCR0_CS02);
#elif TIMER0_PRESCALER == PRESCALER_256
    TCCR0 &= ~(1 << TCCR0_CS00);
    TCCR0 &= ~(1 << TCCR0_CS01);
    TCCR0 |= (1 << TCCR0_CS02);
#elif TIMER0_PRESCALER == PRESCALER_1024
    TCCR0 |= (1 << TCCR0_CS00);
    TCCR0 &= ~(1 << TCCR0_CS01);
    TCCR0 |= (1 << TCCR0_CS02);
#elif TIMER0_PRESCALER == EXTERNAL_CLOCK_SOURCE_FALLING_EDGE
    TCCR0 &= ~(1 << TCCR0_CS00);
    TCCR0 |= (1 << TCCR0_CS01);
    TCCR0 |= (1 << TCCR0_CS02);
#elif TIMER0_PRESCALER == EXTERNAL_CLOCK_SOURCE_RISING_EDGE
    TCCR0 |= (1 << TCCR0_CS00);
    TCCR0 |= (1 << TCCR0_CS01);
    TCCR0 |= (1 << TCCR0_CS02);
#endif

    return local_errorstate;
}
ES_t TIMER1_init(void)
{
    ES_t local_errorstate = ES_NOK;
#ifdef TIMER1_enable
    // waveform generation mode
    #if TIMER1_WAVEFORM_GENERATION_MODE == NORMAL_MODE
        TCCR1A &= ~(1 << TCCR1A_WGM10);
        TCCR1A &= ~(1 << TCCR1A_WGM11);
        TCCR1B &= ~(1 << TCCR1B_WGM12);
        TCCR1B &= ~(1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == PWM_PHASE_CORRECT_8BIT
        TCCR1A &= ~(1 << TCCR1A_WGM10);
        TCCR1A &= ~(1 << TCCR1A_WGM11);
        TCCR1B &= ~(1 << TCCR1B_WGM12);
        TCCR1B |= (1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == PWM_PHASE_CORRECT_9BIT
        TCCR1A &= ~(1 << TCCR1A_WGM10);
        TCCR1A &= ~(1 << TCCR1A_WGM11);
        TCCR1B |= (1 << TCCR1B_WGM12);
        TCCR1B &= ~(1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == PWM_PHASE_CORRECT_10BIT
        TCCR1A &= ~(1 << TCCR1A_WGM10);
        TCCR1A &= ~(1 << TCCR1A_WGM11);
        TCCR1B |= (1 << TCCR1B_WGM12);
        TCCR1B |= (1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == CTC_OCR1A
        TCCR1A &= ~(1 << TCCR1A_WGM10);
        TCCR1A |= (1 << TCCR1A_WGM11);
        TCCR1B &= ~(1 << TCCR1B_WGM12);
        TCCR1B &= ~(1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == FAST_PWM_8BIT
        TCCR1A |= (1 << TCCR1A_WGM10);
        TCCR1A &= ~(1 << TCCR1A_WGM11);
        TCCR1B &= ~(1 << TCCR1B_WGM12);
        TCCR1B |= (1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == FAST_PWM_9BIT
        TCCR1A |= (1 << TCCR1A_WGM10);
        TCCR1A &= ~(1 << TCCR1A_WGM11);
        TCCR1B |= (1 << TCCR1B_WGM12);
        TCCR1B &= ~(1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == FAST_PWM_10BIT
        TCCR1A |= (1 << TCCR1A_WGM10);
        TCCR1A &= ~(1 << TCCR1A_WGM11);
        TCCR1B |= (1 << TCCR1B_WGM12);
        TCCR1B |= (1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == PWM_PHASE_FREQ_CORRECT_ICR1
        TCCR1A &= ~(1 << TCCR1A_WGM10);
        TCCR1A |= (1 << TCCR1A_WGM11);
        TCCR1B &= ~(1 << TCCR1B_WGM12);
        TCCR1B |= (1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == PWM_PHASE_FREQ_CORRECT_OCR1A
        TCCR1A &= ~(1 << TCCR1A_WGM10);
        TCCR1A |= (1 << TCCR1A_WGM11);
        TCCR1B |= (1 << TCCR1B_WGM12);
        TCCR1B &= ~(1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == PWM_PHASE_CORRECT_ICR1
        TCCR1A |= (1 << TCCR1A_WGM10);
        TCCR1A |= (1 << TCCR1A_WGM11);
        TCCR1B &= ~(1 << TCCR1B_WGM12);
        TCCR1B |= (1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == PWM_PHASE_CORRECT_OCR1A
        TCCR1A |= (1 << TCCR1A_WGM10);
        TCCR1A |= (1 << TCCR1A_WGM11);
        TCCR1B |= (1 << TCCR1B_WGM12);
        TCCR1B &= ~(1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == CTC_ICR1
        TCCR1A |= (1 << TCCR1A_WGM10);
        TCCR1A |= (1 << TCCR1A_WGM11);
        TCCR1B &= ~(1 << TCCR1B_WGM12);
        TCCR1B |= (1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == FAST_PWM_ICR1
        TCCR1A |= (1 << TCCR1A_WGM10);
        TCCR1A |= (1 << TCCR1A_WGM11);
        TCCR1B |= (1 << TCCR1B_WGM12);
        TCCR1B |= (1 << TCCR1B_WGM13);
    #elif TIMER1_WAVEFORM_GENERATION_MODE == FAST_PWM_OCR1A
        TCCR1A |= (1 << TCCR1A_WGM10);
        TCCR1A |= (1 << TCCR1A_WGM11);
        TCCR1B |= (1 << TCCR1B_WGM12);
        TCCR1B |= (1 << TCCR1B_WGM13);
    #endif

    // choose channel A mode

#ifdef Channel_A
    #if TIMER1_COMPARE_OUTPUT_MODE == NORMAL_PORT_OPERATION
        TCCR1A &= ~(1 << TCCR1A_COM1A0);
        TCCR1A &= ~(1 << TCCR1A_COM1A1);
    #elif TIMER1_COMPARE_OUTPUT_MODE == TOGGLE_OC1A_ON_COMPARE_MATCH
        TCCR1A |= (1 << TCCR1A_COM1A0);
        TCCR1A &= ~(1 << TCCR1A_COM1A1);
    #elif TIMER1_COMPARE_OUTPUT_MODE == CLEAR_OC1A_ON_COMPARE_MATCH
        TCCR1A &= ~(1 << TCCR1A_COM1A0);
        TCCR1A |= (1 << TCCR1A_COM1A1);
    #elif TIMER1_COMPARE_OUTPUT_MODE == SET_OC1A_ON_COMPARE_MATCH
        TCCR1A |= (1 << TCCR1A_COM1A0);
        TCCR1A |= (1 << TCCR1A_COM1A1);
    #endif
#endif
#ifdef Channel_B
    #if TIMER1_COMPARE_OUTPUT_MODE == NORMAL_PORT_OPERATION
        TCCR1A &= ~(1 << TCCR1A_COM1B0);
        TCCR1A &= ~(1 << TCCR1A_COM1B1);
    #elif TIMER1_COMPARE_OUTPUT_MODE == TOGGLE_OC1A_ON_COMPARE_MATCH
        TCCR1A |= (1 << TCCR1A_COM1B0);
        TCCR1A &= ~(1 << TCCR1A_COM1B1);
    #elif TIMER1_COMPARE_OUTPUT_MODE == CLEAR_OC1A_ON_COMPARE_MATCH
        TCCR1A &= ~(1 << TCCR1A_COM1B0);
        TCCR1A |= (1 << TCCR1A_COM1B1);
    #elif TIMER1_COMPARE_OUTPUT_MODE == SET_OC1A_ON_COMPARE_MATCH
        TCCR1A |= (1 << TCCR1A_COM1B0);
        TCCR1A |= (1 << TCCR1A_COM1B1);
    #endif
#endif
//duty cycle 50% timer1
// prescaler
#if TIMER1_PRESCALER == NO_CLOCK_SOURCE
    TCCR1B &= ~(1 << TCCR1B_CS10);
    TCCR1B &= ~(1 << TCCR1B_CS11);
    TCCR1B &= ~(1 << TCCR1B_CS12);
#elif TIMER1_PRESCALER == NO_PRESCALING
    TCCR1B |= (1 << TCCR1B_CS10);
    TCCR1B &= ~(1 << TCCR1B_CS11);
    TCCR1B &= ~(1 << TCCR1B_CS12);
#elif TIMER1_PRESCALER == PRESCALER_8
    TCCR1B &= ~(1 << TCCR1B_CS10);
    TCCR1B |= (1 << TCCR1B_CS11);
    TCCR1B &= ~(1 << TCCR1B_CS12);
#elif TIMER1_PRESCALER == PRESCALER_64
    TCCR1B |= (1 << TCCR1B_CS10);
    TCCR1B |= (1 << TCCR1B_CS11);
    TCCR1B &= ~(1 << TCCR1B_CS12);
#elif TIMER1_PRESCALER == PRESCALER_256
    TCCR1B &= ~(1 << TCCR1B_CS10);
    TCCR1B &= ~(1 << TCCR1B_CS11);
    TCCR1B |= (1 << TCCR1B_CS12);
#elif TIMER1_PRESCALER == PRESCALER_1024
    TCCR1B |= (1 << TCCR1B_CS10);
    TCCR1B &= ~(1 << TCCR1B_CS11);
    TCCR1B |= (1 << TCCR1B_CS12);
#elif TIMER1_PRESCALER == EXTERNAL_CLOCK_SOURCE_FALLING_EDGE
    TCCR1B &= ~(1 << TCCR1B_CS10);
    TCCR1B |= (1 << TCCR1B_CS11);
    TCCR1B |= (1 << TCCR1B_CS12);
#elif TIMER1_PRESCALER == EXTERNAL_CLOCK_SOURCE_RISING_EDGE
    TCCR1B |= (1 << TCCR1B_CS10);
    TCCR1B |= (1 << TCCR1B_CS11);
    TCCR1B |= (1 << TCCR1B_CS12);
#endif
#endif
    return local_errorstate;
}

ES_t TIMER0_enuSetSyncDelay(u32 Copy_u8Time)
{
    ES_t local_errorstate = ES_NOK;
    TIMSK &= ~(1 << TOIE0);
    f32 overflowTime = (256.0 * (f32)TIMER0_PRESCALER) / (f32)F_CPU;
    f32 NumOVF = Copy_u8Time / overflowTime;
    if (NumOVF - (u32)NumOVF != 0.0)
    {
        u32 NumOVF_int = (u32)NumOVF + 1;
        NumOVF = NumOVF - (u32)NumOVF;
        u8 preload = 256 * (1 - NumOVF);
        TCNT0 = preload;
        while (NumOVF_int > 0)
        {
            while (((TIFR >> TOV0) & 1) == 0);
            TIFR |= (1 << TOV0);
            NumOVF_int--;
        }
    }
    else
    {
        u32 NumOVF_int = (u32)NumOVF;
        while (NumOVF_int > 0)
        {
            while (((TIFR >> TOV0) & 1) == 0)
                ;
            TIFR |= (1 << TOV0);
        }
    }

    return local_errorstate;
}
ES_t TIMER0_enuSetASyncDelay(u32 Copy_u8Time, void (*func)(void), void *Copy_pvidParameter)
{
    ES_t local_errorstate = ES_NOK;
    if (func != NULL)
    {
        TIMER0_callBackPtr = func;
        TIMER0_callBackParameter = Copy_pvidParameter;
        local_errorstate = ES_OK;
    }
    else
    {
        local_errorstate = ES_NULL_POINTER;
    }
    f32 overflowTime = (256.0 * TIMER0_PRESCALER) / F_CPU;
    f32 NumOVF = Copy_u8Time / overflowTime;
    if (NumOVF - (u32)NumOVF != 0.0)
    {
        u32 NumOVF_int = (u32)NumOVF + 1;
        NumOVF = NumOVF - (u32)NumOVF;
        u8 preload = 256 * (1 - NumOVF);
        gNum_OVF = NumOVF_int;
        gPreload = preload;
        TCNT0 = preload;
    }
    else
    {
        gNum_OVF = (u32)NumOVF;
    }
    TIMSK |= (1 << TOIE0);
    return local_errorstate;
}
ES_t TIMER0_callBack(void (*func)(void), void *Copy_pvidParameter)
{

    ES_t local_errorstate = ES_NOK;
    if (func != NULL)
    {
        TIMER0_callBackPtr = func;
        TIMER0_callBackParameter = Copy_pvidParameter;
        local_errorstate = ES_OK;
    }
    else
    {
        local_errorstate = ES_NULL_POINTER;
    }
    return local_errorstate;
}
ES_t TIMER1_callBack(void (*func)(void), void *Copy_pvidParameter)
{

    ES_t local_errorstate = ES_NOK;
    if (func != NULL)
    {
        TIMER1_callBackPtr = func;
        TIMER1_callBackParameter = Copy_pvidParameter;
        local_errorstate = ES_OK;
    }
    else
    {
        local_errorstate = ES_NULL_POINTER;
    }
    return local_errorstate;
}
ES_t TIMER0_GeneratePWM(u8 Copy_u8DutyCycle)
{
    ES_t local_errorstate = ES_NOK;
    u8 local_u8CompareValue = 0;
#if TIMER0_WAVEFORM_GENERATION_MODE == FAST_PWM
#if TIMER0_COMPARE_OUTPUT_MODE == NON_INVERTING_CLR_ON_COMP
    local_u8CompareValue = (Copy_u8DutyCycle * 256) / 100;
#elif TIMER0_COMPARE_OUTPUT_MODE == INVERTING_SET_ON_COMP
    local_u8CompareValue = 256 - ((Copy_u8DutyCycle * 256) / 100);
#endif
#elif TIMER0_WAVEFORM_GENERATION_MODE == PWM_PHASE_CORRECT
#if TIMER0_COMPARE_OUTPUT_MODE == NON_INVERTING_SET_ON_COMP
    local_u8CompareValue = (Copy_u8DutyCycle * 256) / 100;
#elif TIMER0_COMPARE_OUTPUT_MODE == INVERTING_CLR_ON_COMP
    local_u8CompareValue = 256 - ((Copy_u8DutyCycle * 256) / 100);
#endif
#endif
    TIMER0_vidSetCompareValue(local_u8CompareValue);
    local_errorstate = ES_OK;
    return local_errorstate;
}

ES_t TIMER1_SetTimerValue(u16 Copy_u16Value)
{
    ES_t local_errorstate = ES_NOK;
    TCNT1 = Copy_u16Value;
    local_errorstate = ES_OK;
    return local_errorstate;
}
ES_t TIMER1_GetTimerValue(u16 *Copy_pu16Value)
{
    ES_t local_errorstate = ES_NOK;
    if (Copy_pu16Value != NULL)
    {
        *Copy_pu16Value = TCNT1;
        local_errorstate = ES_OK;
    }
    else
    {
        local_errorstate = ES_NULL_POINTER;
    }
    return local_errorstate;
}

ES_t ICU_Init(){
    ES_t localerrorState = ES_NOK;
    /*Set Trigger to rising edge intially*/    
    TCCR1B |= (1<<TCCR1B_ICES1);
    /*Enable ICU Interrupt*/
    TIMSK |= (1<<TICIE1);
    return localerrorState;
}
ES_t ICU_enuSetEdge(u8 Copy_u8Edge){
    ES_t localerrorState = ES_NOK;
if(Copy_u8Edge <= Falling_edge ){
    if(Copy_u8Edge == Rising_edge){
        TCCR1B |= (1<<TCCR1B_ICES1);
    }else if(Copy_u8Edge == Falling_edge){
        TCCR1B &= ~(1<<TCCR1B_ICES1);
    }
}else{
    localerrorState = ES_OUT_OF_RANGE;
}
    return localerrorState;
}
ES_t ICU_enuEnableINT(){
    ES_t localerrorState = ES_NOK;

    /*Enable ICU Interrupt*/
    TIMSK |= (1<<TICIE1);
    localerrorState = ES_OK;

    return localerrorState;
}
ES_t ICU_enuDisableINT(){
    ES_t localerrorState = ES_NOK;

    /*Enable ICU Interrupt*/
    TIMSK &= ~(1<<TICIE1);
    localerrorState = ES_OK;

    return localerrorState;
}
ES_t ICU_enuSetCallBack(void (*func)(void), void *Copy_pvidParameter ){
    ES_t local_errorstate = ES_NOK;
    if (func != NULL)
    {
        ICU_callBackPtr = func;
        ICU_callBackParameter = Copy_pvidParameter;
        local_errorstate = ES_OK;
    }
    else
    {
        local_errorstate = ES_NULL_POINTER;
    }
    return local_errorstate;
}

ES_t ICU_enuReadInputCapture(u16 * Copy_pu16Value){
    ES_t local_errorstate =ES_NOK;
    if(Copy_pu16Value != NULL){
        *Copy_pu16Value =ICR1;
        local_errorstate =ES_OK;
    }else{
        local_errorstate = ES_NULL_POINTER;
    }
    return local_errorstate;
}

static inline void TIMER0_vidSetCounterValue(u8 Copy_u8Value)
{
    TCNT0 = Copy_u8Value;
}

static inline void TIMER0_vidSetCompareValue(u8 Copy_u8Value)
{
    OCR0 = Copy_u8Value;
}

ISR(VECT_TIMER0_COMP)
{
    if (TIMER0_callBackPtr != NULL)
    {
        TIMER0_callBackPtr(TIMER0_callBackParameter);
    }
}

ISR(VECT_TIMER0_OVF)
{
    if (TIMER0_callBackPtr != NULL)
    {
        // static u8 flag =0;
        // static u32 counts = 0;
        // counts++;
        // if (counts == gNum_OVF)
        // {
        //     TCNT0 = gPreload;
        //     counts = 0;
        //     flag =1;
        // }else if(counts != 0 && counts < gNum_OVF && counts %50 ==0 && flag !=1){
        //    TIMER0_callBackPtr(TIMER0_callBackParameter);
        // }
        TIMER0_callBackPtr(TIMER0_callBackParameter);
    }
}
ISR(VECT_TIMER1_CAPT){
     if (ICU_callBackPtr != NULL)
    {
        ICU_callBackPtr(ICU_callBackParameter);
    }
}
ISR(VECT_TIMER1_COMPA){

}
ISR(VECT_TIMER1_COMPB){

}
ISR(VECT_TIMER1_OVF){
    
}