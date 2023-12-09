#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

#define EightBitMode 0
#define FourBitMode  1

#define ON_OFF 0x0f
#define CLEAR  0x01
#define EntrySetMode 0x06
#define HOME_Command 0x02

static inline void LCD_invidSendCommand(u8 Copy_u8Command);
static  void LCD_Latch(u8 Copy_u8Data);
#endif /* LCD_PRIV_H_ */
