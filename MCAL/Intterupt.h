//file guard
#ifndef INTTERUPT_H_
#define INTTERUPT_H_

#define ISR(VECT)   void VECT(void) __attribute__((signal));\
                    void VECT(void)

#define  VECT_INT0  __vector_1
#define  VECT_INT1  __vector_2
#define  VECT_INT2  __vector_3

#define VECT_TIMER2_COMP __vector_4
#define VECT_TIMER2_OVF __vector_5

#define VECT_TIMER0_COMP  __vector_10
#define VECT_TIMER0_OVF  __vector_11
#define VECT_TIMER1_CAPT __vector_6
#define VECT_TIMER1_COMPA __vector_7
#define VECT_TIMER1_COMPB __vector_8
#define VECT_TIMER1_OVF __vector_9


#define ADC_vect    __vector_16

#endif /* INTTERUPT_H_ */