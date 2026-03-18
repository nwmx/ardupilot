#pragma once

#include <AP_HIL/AP_HIL_config.h>

#if AP_HIL_ENABLED

#include "AP_Compass.h"
#include "AP_Compass_Backend.h"

class AP_Compass_HIL : public AP_Compass_Backend
{
public:
    using AP_Compass_Backend::AP_Compass_Backend;

    static AP_Compass_Backend *probe();

    // called from HIL_SENSOR dispatch
    void handle_hil(const Vector3f &field) override;

private:
};

#endif // AP_HIL_ENABLED
