#include "AP_Airspeed_HIL.h"

#if AP_HIL_ENABLED

#include <AP_HIL/AP_HIL.h>

bool AP_Airspeed_HIL::get_differential_pressure(float &pressure)
{
    const auto *hil = AP::hil();
    if (hil == nullptr) {
        return false;
    }
    // HIL_SENSOR sends diff_pressure in hPa, ArduPilot expects Pa
    pressure = hil->sensor.diff_pressure * 100.0f;
    return true;
}

bool AP_Airspeed_HIL::get_temperature(float &temperature)
{
    const auto *hil = AP::hil();
    if (hil == nullptr) {
        return false;
    }
    temperature = hil->sensor.temperature;
    return true;
}

#endif // AP_HIL_ENABLED
