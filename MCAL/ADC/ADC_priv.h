#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

#define ADCH    *((volatile u8 *)0x25)
#define ADCL    *((volatile u8 *)0x24)
#define ADCSRA      *((u8 *)0x26)
#define ADMUX       *((u8 *)0x27)
#define SFIOR       *((u8 *)0x50)

#define IDLE 0
#define BUSY 1

#define FREE_RUNNING_MODE 0
#define ANALOG_COMPARATOR 1
#define EXTERNAL_INTERRUPT_REQUEST_0 2
#define TIMER_COUNTER0_COMPARE_MATCH 3
#define TIMER_COUNTER0_OVERFLOW 4
#define TIMER_COUNTER1_COMPARE_MATCH_B 5
#define TIMER_COUNTER1_OVERFLOW 6
#define TIMER_COUNTER1_CAPTURE_EVENT 7

#define ADTS0       5
#define ADTS1       6
#define ADTS2       7

#define RIGHT_ADJUSTMENT 0
#define LEFT_ADJUSTMENT  1

#define Single_Ended_Input 0
#define Differential_Input 1

#define AREF       2
#define AVCC       1
#define INTERNAL   3

#define DIVISION_FACTOR_2   1
#define DIVISION_FACTOR_4   2
#define DIVISION_FACTOR_8   3
#define DIVISION_FACTOR_16  4
#define DIVISION_FACTOR_32  5
#define DIVISION_FACTOR_64  6
#define DIVISION_FACTOR_128 7
// ADCSRA
#define ADEN       7
#define ADSC       6
#define ADATE      5
#define ADIF       4
#define ADIE       3
#define ADPS0      0
#define ADPS1      1
#define ADPS2      2
// ADMUX
#define REFS0      6
#define REFS1      7
#define ADLAR      5
#define MUX0       0
#define MUX1       1
#define MUX2       2
#define MUX3       3
#define MUX4       4
//channel selection
#define ADC0       0
#define ADC1       1
#define ADC2       2
#define ADC3       3
#define ADC4       4
#define ADC5       5
#define ADC6       6
#define ADC7       7

typedef struct 
{
    u8 u8ADC_ChannelID;
    u8 * arr_result;
}ADC_chain_t;

#endif /* ADC_PRIV_H_ */
