#ifndef APP_PRIV_H_
#define APP_PRIV_H_

#define RED 0
#define YELLOW 1
#define GREEN 2

#define PRESSED 1
#define NOT_PRESSED 0

#define NORMAL_MODE 0
#define Pedestrian_Mode 1

void normalModeLIGHT();
void PedestrianModeLIGHT();
void PedestrianMode();

static inline void CAR_greenLIGHTON();
static inline void CAR_greenLIGHTOFF();

static inline void CAR_redLIGHTON();
static inline void CAR_redLIGHTOFF();

static inline void CAR_yellowModeLIGHT();
static inline void CAR_yellowLIGHTON();
static inline void CAR_yellowLIGHTOFF();

static inline void PED_greenLIGHTON();
static inline void PED_greenLIGHTOFF();

static inline void PED_redLIGHTON();
static inline void PED_redLIGHTOFF();

static inline void PED_yellowModeLIGHT();
static inline void PED_yellowLIGHTON();
static inline void PED_yellowLIGHTOFF();



#endif /* APP_PRIV_H_ */
