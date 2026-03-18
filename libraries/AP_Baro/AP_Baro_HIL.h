/*
  HIL backend barometer
 */
#pragma once

#include <AP_HIL/AP_HIL_config.h>

#if AP_HIL_ENABLED

#include "AP_Baro_Backend.h"

class AP_Baro_HIL : public AP_Baro_Backend
{
public:
    AP_Baro_HIL(AP_Baro &baro);
    void update(void) override;

    // called from HIL_SENSOR dispatch
    void handle_hil(float pressure_hPa, float temperature) override;

private:
    uint8_t instance;
    float sum_pressure;
    float sum_temp;
    uint16_t count;
};

#endif // AP_HIL_ENABLED
