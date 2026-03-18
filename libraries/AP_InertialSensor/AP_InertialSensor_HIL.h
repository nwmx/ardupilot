#pragma once

#include <AP_HIL/AP_HIL_config.h>

#if AP_HIL_ENABLED

#include "AP_InertialSensor.h"
#include "AP_InertialSensor_Backend.h"

class AP_InertialSensor_HIL : public AP_InertialSensor_Backend
{
public:
    AP_InertialSensor_HIL(AP_InertialSensor &imu);

    bool update() override;
    void start() override;
    void accumulate() override {}

    // called from GCS_MAVLink_Plane when HIL_SENSOR is received
    void handle_hil(const Vector3f &accel, const Vector3f &gyro, float temperature) override;

private:
    bool started;
};

#endif // AP_HIL_ENABLED
