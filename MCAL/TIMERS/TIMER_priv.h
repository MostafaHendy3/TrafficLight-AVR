#ifndef TIMER_PRIV_H_
#define TIMER_PRIV_H_

#define TCCR0 *((volatile u8 *)0x53)

#define TCCR0_WGM00 6 // waveform generation mode bit 0
#define TCCR0_WGM01 3 // waveform generation mode bit 1
#define TCCR0_CS00 0  // prescaler bit 0
#define TCCR0_CS01 1  // prescaler bit 1
#define TCCR0_CS02 2  // prescaler bit 2
#define TCCR0_COM00 4 // compare output mode bit 0
#define TCCR0_COM01 5 // compare output mode bit 1
#define TCCR0_FOC0 7  // force output compare
#define TCNT0 *((volatile u8 *)0x52)
#define TIMSK *((volatile u8 *)0x59)
#define TICIE1 5
#define OCIE1A 4
#define OCIE1B 3
#define TOIE1 2
#define OCIE0 1 // output compare interrupt enable
#define TOIE0 0 // overflow interrupt enable

#define NO_INTERRUTP 6
#define TIFR *((volatile u8 *)0x58)
#define OCF0 1 // output compare flag
#define TOV0 0 // overflow flag

#define OCR0 *((volatile u8 *)0x5C)

//timer1 
#define TCCR1A *((volatile u8 *)0x4F)
#define TCCR1B *((volatile u8 *)0x4E)


#define NORMAL 0
#define PWM_PHASE_CORRECT 1
#define CTC 2
#define FAST_PWM 3


#define NORMAL_PORT_OPERATION 0
#define TOGGLE_OC0_ON_COMPARE_MATCH 1
#define CLEAR_OC0_ON_COMPARE_MATCH 2
#define  SET_OC0_ON_COMPARE_MATCH 3

#define  NON_INVERTING_CLR_ON_COMP 0
#define  INVERTING_SET_ON_COMP 1


#define TOGGLE_OC1A_ON_COMPARE_MATCH 0
#define CLEAR_OC1A_ON_COMPARE_MATCH 1
#define SET_OC1A_ON_COMPARE_MATCH 2


#define TOGGLE_OC1B_ON_COMPARE_MATCH 0
#define CLEAR_OC1B_ON_COMPARE_MATCH 1
#define SET_OC1B_ON_COMPARE_MATCH 2

//prescaler

#define NO_CLOCK_SOURCE 0
#define NO_PRESCALING   1
#define PRESCALER_8     8
#define PRESCALER_64    64
#define PRESCALER_256   256
#define PRESCALER_1024  1024
#define EXTERNAL_CLOCK_SOURCE_FALLING_EDGE 6
#define  EXTERNAL_CLOCK_SOURCE_RISING_EDGE 7


//waveform generation mode Timer 1 
#define NORMAL_MODE 0
#define PWM_PHASE_CORRECT_8BIT 1 
#define PWM_PHASE_CORRECT_9BIT 2
#define PWM_PHASE_CORRECT_10BIT 3
#define CTC_OCR1A 4
#define FAST_PWM_8BIT 5
#define FAST_PWM_9BIT 6
#define FAST_PWM_10BIT 7
#define PWM_PHASE_FREQ_CORRECT_ICR1 8
#define PWM_PHASE_FREQ_CORRECT_OCR1A 9
#define PWM_PHASE_CORRECT_ICR1 10
#define PWM_PHASE_CORRECT_OCR1A 11
#define CTC_ICR1 12
#define FAST_PWM_ICR1 13
#define FAST_PWM_OCR1A 14

#define TCCR1A_COM1A0 6
#define TCCR1A_COM1A1 7
#define TCCR1A_COM1B0 4
#define TCCR1A_COM1B1 5
#define TCCR1A_FOC1A 3
#define TCCR1A_FOC1B 2
#define TCCR1A_WGM10 0
#define TCCR1A_WGM11 1
#define TCCR1B_WGM12 3
#define TCCR1B_WGM13 4
#define TCCR1B_CS10 0
#define TCCR1B_CS11 1
#define TCCR1B_CS12 2
#define TCCR1B_ICNC1 7
#define TCCR1B_ICES1 6
#define TCCR1  *((volatile u8 *)0x4E)
#define TCNT1H *((volatile u8 *)0x4D)
#define TCNT1L *((volatile u8 *)0x4C)
#define TCNT1  *((volatile u16 *)0x4C)
#define OCR1AH *((volatile u8 *)0x4B)
#define OCR1AL *((volatile u8 *)0x4A)
#define OCR1A  *((volatile u16 *)0x4A)
#define OCR1BH *((volatile u8 *)0x49)
#define OCR1BL *((volatile u8 *)0x48)
#define OCR1B  *((volatile u16 *)0x48)
#define ICR1H  *((volatile u8 *)0x47)
#define ICR1L  *((volatile u8 *)0x46)
#define ICR1   *((volatile u16 *)0x46)
#define Rising_edge 0
#define Falling_edge 1

#define DISCONNECTED 0
#define CONNECTED 1


static inline void TIMER0_vidSetCompareValue(u8 Copy_u8Value);
static inline void TIMER0_vidSetCounterValue(u8 Copy_u8Value);


#endif /* TIMER_PRIV_H_ */
