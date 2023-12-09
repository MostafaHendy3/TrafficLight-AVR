#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_

#define EXTI_u8ENABLED  1
#define EXTI_u8DISABLED 0

#define EXTI_u8RISING_EDGE  1
#define EXTI_u8FALLING_EDGE 0
#define EXTI_u8ON_CHANGE    2
#define EXTI_u8LOW_LEVEL    3

#define EXTI_INT0 0
#define EXTI_INT1 1
#define EXTI_INT2 2

#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
#define ISC2 6

#define MCUCR *((volatile u8*)0x55)
#define MCUCSR *((volatile u8*)0x54)
#define GICR *((volatile u8*)0x5B)
#define GIFR *((volatile u8*)0x5A)


#endif /* EXTI_PRIV_H_ */
