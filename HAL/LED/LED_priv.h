
#ifndef LED_PRIV_H_
#define LED_PRIV_H_

#define LED_SINK 0
#define LED_SOURCE 1

#define LED_OFF 0
#define LED_ON 1
typedef struct{
    u8 LED_u8Port;
    u8 LED_u8Pin;
    u8 LED_u8Connection;
    u8 LED_u8InitStatus;
}LED_t;

#endif /* LED_PRIV_H_ */