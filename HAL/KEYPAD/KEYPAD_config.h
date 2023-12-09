#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define KEYPAD_ROWS_NUM		4
#define KEYPAD_COLS_NUM		4

#define KEYPAD_PORT		DIO_u8PORTD

#define KEYPAD_COL_PIN0		DIO_u8PIN0
#define KEYPAD_COL_PIN1		DIO_u8PIN1
#define KEYPAD_COL_PIN2		DIO_u8PIN2
#define KEYPAD_COL_PIN3		DIO_u8PIN3

#define KEYPAD_ROW_PIN0		DIO_u8PIN4
#define KEYPAD_ROW_PIN1		DIO_u8PIN5
#define KEYPAD_ROW_PIN2		DIO_u8PIN6
#define KEYPAD_ROW_PIN3		DIO_u8PIN7

#define KEYPAD_NO_PRESSED_KEY		0xFF
#define KPD_ARY_VAL    {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}}

#endif /* KEYPAD_CONFIG_H_ */
