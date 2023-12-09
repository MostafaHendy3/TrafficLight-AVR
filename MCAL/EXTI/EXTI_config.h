#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

typedef struct{
    u8 EXTI_u8state;
    u8 EXTI_u8senseMode;
}EXTI_t;


#define EXTI_INT0 0
#define EXTI_INT1 1
#define EXTI_INT2 2

#endif /* EXTI_CONFIG_H_ */
