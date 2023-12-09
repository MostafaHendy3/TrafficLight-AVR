#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "EXTI_priv.h"
#include "EXTI_config.h"

EXTI_t EXTI_tConfig[3] = {
    {EXTI_u8ENABLED, EXTI_u8RISING_EDGE},
    {EXTI_u8DISABLED, EXTI_u8RISING_EDGE},
    {EXTI_u8DISABLED, EXTI_u8FALLING_EDGE}
};