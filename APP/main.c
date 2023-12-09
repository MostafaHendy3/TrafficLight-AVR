#include "../LIB/stdTypes.h"
#include "../LIB/errorStates.h"
#include "../MCAL\GIE\GIE_Int.h"
#include "../MCAL/GIE/GIE_priv.h"
#include "../MCAL/WDT/WDT_Int.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_Int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TIMERS/TIMER_Int.h"
#include "../MCAL/TIMERS/TIMER_config.h"

#include "../App/APP_Int.h"
#include "../MCAL/Intterupt.h"


int main()
{
    APP_enuInit();
    APP_enuStart();
    while(1);
    return 0;
    
}