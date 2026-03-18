#include "AP_Baro_HIL.h"

#if AP_HIL_ENABLED

AP_Baro_HIL::AP_Baro_HIL(AP_Baro &baro) :
    AP_Baro_Backend(baro)
{
    instance = _frontend.register_sensor();
    set_bus_id(instance, AP_HAL::Device::make_bus_id(AP_HAL::Device::BUS_TYPE_UNKNOWN, 0, 3, 0));
}

void AP_Baro_HIL::update(void)
{
    if (count) {
        WITH_SEMAPHORE(_sem);
        // pressure is in Pa for _copy_to_frontend, HIL_SENSOR sends hPa
        _copy_to_frontend(instance, sum_pressure / count * 100.0f, sum_temp / count);
        sum_pressure = sum_temp = 0;
        count = 0;
    }
}

void AP_Baro_HIL::handle_hil(float pressure_hPa, float temperature)
{
    WITH_SEMAPHORE(_sem);
    sum_pressure += pressure_hPa;
    sum_temp += temperature;
    count++;
}

#endif // AP_HIL_ENABLED
