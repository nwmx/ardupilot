#pragma once

#include <AP_HAL/AP_HAL_Boards.h>

// AP_HIL_ENABLED: enabled on any board that does not minimize features.
// HAL_MINIMIZE_FEATURES is board-specific and may not be defined at all,
// so we use #ifdef to avoid -Werror=undef.
#ifndef AP_HIL_ENABLED
#  ifdef HAL_MINIMIZE_FEATURES
#    define AP_HIL_ENABLED 0
#  else
#    define AP_HIL_ENABLED 1
#  endif
#endif
