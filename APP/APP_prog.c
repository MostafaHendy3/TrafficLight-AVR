#include "../LIB/stdTypes.h"
#include "../LIB/errorStates.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/TIMERS/TIMER_Int.h"
#include "../MCAL/TIMERS/TIMER_config.h"
#include "../MCAL/GIE/GIE_Int.h"
#include "../MCAL/EXTI/EXTI_Int.h"

#include "../HAL/Switch/Switch_int.h"
#include "../HAL/Switch/Switch_config.h"

#include "APP_priv.h"
#include "APP_config.h"

u8 Car_Led_State = RED;
u8 PED_BTN_State = NOT_PRESSED;
u8 MODE_Operation = NORMAL_MODE;
static u16 TimerCounts = 0;

extern SW_t Switch_AstrSwitchState[SW_NUM];
extern EXTI_t EXTI_tConfig[3];

ES_t APP_enuInit(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    Switch_enuInit(Switch_AstrSwitchState);
    GIE_voidDisable();
    EXTI_enuInit(EXTI_tConfig);
    EXTI_enuSetCallBack(EXTI_u8INT0, PedestrianMode, NULL);
    /*Car's LEDS D7 D6 D5*/
    DIO_enuSetPinDirection(DIO_u8PORTD, DIO_u8PIN7, DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN7, DIO_u8LOW);
    DIO_enuSetPinDirection(DIO_u8PORTD, DIO_u8PIN6, DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN6, DIO_u8LOW);
    DIO_enuSetPinDirection(DIO_u8PORTD, DIO_u8PIN5, DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN5, DIO_u8LOW);
    /*Pedestrian's LEDS B5 B6 B7*/
    DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN5, DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN5, DIO_u8LOW);
    DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN6, DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN6, DIO_u8LOW);
    DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN7, DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN7, DIO_u8LOW);
    TIMER0_init();
    GIE_voidEnable();

    return Local_enuErrorState;
}
ES_t APP_enuStart(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    TIMER0_callBack(normalModeLIGHT, NULL);
    return Local_enuErrorState;
}

/*
    function name: normalModeLIGHT
    function arguments: void
    function return void
    function description: this function is called by the timer0 ISR 
    to control the traffic lights in the normal mode
*/
void normalModeLIGHT()
{
    static u8 Local_u8Flag = 0;
    /*
    Local_u8Flag = 0 increment time
    Local_u8Flag = 1 decrement time
    */
    if (MODE_Operation == NORMAL_MODE)
    {
        if (Local_u8Flag == 0)
        {
            TimerCounts++;
            if (TimerCounts <= 2500){
                // stay 5 sec in green
                Car_Led_State = GREEN;
                CAR_greenLIGHTON();
            }
            else if (TimerCounts % 50 == 0 && TimerCounts > 2500 && TimerCounts <= 5000){
                // blink yellow for 5 sec
                CAR_greenLIGHTOFF();
                Car_Led_State = YELLOW;
                CAR_yellowModeLIGHT();
            }
            else if (TimerCounts > 5000 && TimerCounts < 7500){
                // stay 5 sec in red
                Car_Led_State = RED;
               CAR_redLIGHTON();
            }
            else if (TimerCounts == 7500){
                // reverse counter direction and reset counter to yellow start
                Local_u8Flag = 1;
                TimerCounts = 2500;
                CAR_redLIGHTOFF();
            }
        }
        else if (Local_u8Flag == 1)
        {
            TimerCounts--;
            if (TimerCounts % 50 == 0 && TimerCounts > 0 && TimerCounts <= 2500){
                // blink yellow for 5 sec
               Car_Led_State = YELLOW;
                CAR_yellowModeLIGHT();
            }
            else if (TimerCounts == 0){
                // reverse counter direction and reset counter to greemf start
                CAR_yellowLIGHTOFF();
                Local_u8Flag = 0;
                TimerCounts = 0;
                Car_Led_State = GREEN;
                CAR_greenLIGHTON();
            }
        }
    }
    
}
/*
    function name: PedestrianModeLIGHT
    function arguments: void
    function return void
    function description: this function is called by the timer0 ISR after changed the mode to pedestrian mode in exti ISR
    to control the traffic lights in the pedestrian mode
*/
void PedestrianModeLIGHT(){
    TimerCounts ++;
    if (MODE_Operation == Pedestrian_Mode){
        if (Car_Led_State == RED ){
           if (PED_BTN_State == PRESSED && TimerCounts <= 2500){
                CAR_redLIGHTON();
                PED_greenLIGHTON();
                PED_redLIGHTOFF();
            }else if (PED_BTN_State == PRESSED && TimerCounts %50 == 0 && TimerCounts >2500 && TimerCounts < 5000){
                CAR_redLIGHTOFF();
                PED_greenLIGHTON();
                CAR_yellowModeLIGHT();
                PED_yellowModeLIGHT();
            }else if (PED_BTN_State == PRESSED &&  TimerCounts == 5000){
                CAR_yellowLIGHTOFF();
                CAR_greenLIGHTON();
                PED_greenLIGHTOFF();
                PED_yellowLIGHTOFF();
                PED_redLIGHTON();
                PED_BTN_State = NOT_PRESSED;
                MODE_Operation = NORMAL_MODE;
                TIMER0_callBack(normalModeLIGHT, NULL);
                TimerCounts = 0;
            }
            
        }else if (Car_Led_State == GREEN || Car_Led_State == YELLOW){
            if (PED_BTN_State == PRESSED){
                    if (PED_BTN_State == PRESSED &&  TimerCounts %50 == 0 && TimerCounts <= 2500){
                    CAR_yellowModeLIGHT();
                    PED_yellowModeLIGHT();
                    PED_redLIGHTON();
                }else if (PED_BTN_State == PRESSED && TimerCounts >2500 && TimerCounts < 5000){
                    CAR_greenLIGHTOFF();
                    CAR_yellowLIGHTOFF();
                    CAR_redLIGHTON();
                    PED_redLIGHTOFF();
                    PED_greenLIGHTON();
                }else if (PED_BTN_State == PRESSED && TimerCounts %50 == 0 && TimerCounts >5000 && TimerCounts < 7500){
                    CAR_redLIGHTOFF();
                    PED_greenLIGHTON();
                    CAR_yellowModeLIGHT();
                    PED_yellowModeLIGHT();
                }else if (PED_BTN_State == PRESSED &&  TimerCounts == 7500){
                    CAR_yellowLIGHTOFF();
                    CAR_greenLIGHTON();
                    PED_greenLIGHTOFF();
                    PED_yellowLIGHTOFF();
                    PED_redLIGHTON();
                    PED_BTN_State = NOT_PRESSED;
                    MODE_Operation = NORMAL_MODE;
                    TIMER0_callBack(normalModeLIGHT, NULL);
                    TimerCounts = 0;
                }
            }
        }
    } 
}
/*
    function name: PedestrianMode
    function arguments: void
    function return void
    function description: this function is called by the exti ISR to change the mode to pedestrian mode
*/
void PedestrianMode()
{
    if (MODE_Operation == NORMAL_MODE){
        TIMER0_callBack(PedestrianModeLIGHT, NULL);
        MODE_Operation = Pedestrian_Mode;
        TimerCounts = 0;
        PED_BTN_State = PRESSED;
    }else if (MODE_Operation == Pedestrian_Mode){
    PED_BTN_State = PRESSED;
    }
}

static inline void  CAR_greenLIGHTON()
{
    DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN5, DIO_u8HIGH);
}
static inline void CAR_greenLIGHTOFF()
{
    DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN5, DIO_u8LOW);
}
static inline void CAR_redLIGHTON()
{
    DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN7, DIO_u8HIGH);
}
static inline void CAR_redLIGHTOFF()
{
    DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN7, DIO_u8LOW);
}

static inline void CAR_yellowModeLIGHT()
{
    DIO_enuTogPinValue(DIO_u8PORTD, DIO_u8PIN6);
}
static inline void CAR_yellowLIGHTON()
{
    DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN6, DIO_u8HIGH);
}
static inline void CAR_yellowLIGHTOFF()
{
    DIO_enuSetPinValue(DIO_u8PORTD, DIO_u8PIN6, DIO_u8LOW);
}

static inline void PED_greenLIGHTON(){
    DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN7, DIO_u8HIGH);
}
static inline void PED_greenLIGHTOFF(){
    DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN7, DIO_u8LOW);
}

static inline void PED_redLIGHTON(){
    DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN5, DIO_u8HIGH);
}
void PED_redLIGHTOFF(){
    DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN5, DIO_u8LOW);
}

void PED_yellowModeLIGHT(){
    DIO_enuTogPinValue(DIO_u8PORTB, DIO_u8PIN6);
}
void PED_yellowLIGHTON(){   
    DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN6, DIO_u8HIGH);
}
void PED_yellowLIGHTOFF(){
    DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN6, DIO_u8LOW);
}
