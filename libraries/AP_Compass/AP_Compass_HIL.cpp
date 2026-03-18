#include <AP_HAL/AP_HAL.h>
#include "AP_Compass_HIL.h"

#if AP_HIL_ENABLED

AP_Compass_Backend *AP_Compass_HIL::probe()
{
    auto devid = AP_HAL::Device::make_bus_id(AP_HAL::Device::BUS_TYPE_UNKNOWN, 0, 4, 0);
    auto *ret = NEW_NOTHROW AP_Compass_HIL();
    if (ret == nullptr) {
        return nullptr;
    }
    if (!ret->register_compass(devid)) {
        delete ret;
        return nullptr;
    }
    return ret;
}

void AP_Compass_HIL::handle_hil(const Vector3f &field)
{
    Vector3f f = field;
    accumulate_sample(f);
}

#endif // AP_HIL_ENABLED
