#ifndef EXTI_INT_H_
#define EXTI_INT_H_

typedef struct{
    u8 EXTI_u8state;
    u8 EXTI_u8senseMode;
}EXTI_t;


#define EXTI_u8INT0 0
#define EXTI_u8INT1 1
#define EXTI_u8INT2 2

#define EXTI_u8FALLING_EDGE 0
#define EXTI_u8RISING_EDGE 1
#define EXTI_u8ON_CHANGE 2
#define EXTI_u8LOW_LEVEL 3

ES_t EXTI_enuInit(EXTI_t * Copy_pstrEXTI);
ES_t EXTI_enuEnableINT(u8 Copy_u8EXTI_INDEX);
ES_t EXTI_enuDisableINT(u8 Copy_u8EXTI_INDEX);
ES_t EXTI_enuSetSenseMode(u8 Copy_u8EXTI_INDEX, u8 Copy_u8SenseMode);
ES_t EXTI_enuSetCallBack(u8 Copy_u8EXTI_INDEX, void * Copy_pvCallBackFunc, void * Copy_pvCallBackArg);






#endif /* EXTI_INT_H_ */
