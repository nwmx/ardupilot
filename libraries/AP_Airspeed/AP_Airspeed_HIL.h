/*
  HIL airspeed backend — reads differential pressure from AP_HIL singleton
 */
#pragma once

#include <AP_HIL/AP_HIL_config.h>

#if AP_HIL_ENABLED

#include "AP_Airspeed_Backend.h"

class AP_Airspeed_HIL : public AP_Airspeed_Backend
{
public:
    using AP_Airspeed_Backend::AP_Airspeed_Backend;

    bool init(void) override { return true; }

    // return the current differential_pressure in Pascal
    bool get_differential_pressure(float &pressure) override;

    // return temperature in degrees C
    bool get_temperature(float &temperature) override;
};

#endif // AP_HIL_ENABLED
