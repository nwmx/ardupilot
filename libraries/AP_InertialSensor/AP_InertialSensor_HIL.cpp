#include <AP_HAL/AP_HAL.h>
#include "AP_InertialSensor_HIL.h"

#if AP_HIL_ENABLED

const extern AP_HAL::HAL& hal;

// HIL IMU update rate — matches the expected HIL_SENSOR send rate
#define HIL_IMU_RATE_HZ 200

AP_InertialSensor_HIL::AP_InertialSensor_HIL(AP_InertialSensor &imu) :
    AP_InertialSensor_Backend(imu)
{
}

void AP_InertialSensor_HIL::handle_hil(const Vector3f &accel, const Vector3f &gyro, float temperature)
{
    if (!started) {
        return;
    }

    Vector3f a = accel;
    Vector3f g = gyro;

    _rotate_and_correct_accel(accel_instance, a);
    _notify_new_accel_raw_sample(accel_instance, a, AP_HAL::micros64());

    _publish_temperature(accel_instance, temperature);

    _notify_new_gyro_sensor_rate_sample(gyro_instance, g);
    _rotate_and_correct_gyro(gyro_instance, g);
    _notify_new_gyro_raw_sample(gyro_instance, g, AP_HAL::micros64());
}

bool AP_InertialSensor_HIL::update()
{
    if (started) {
        update_accel(accel_instance);
        update_gyro(gyro_instance);
    }
    return started;
}

void AP_InertialSensor_HIL::start()
{
    // BUS_TYPE_UNKNOWN with unique dev_id for HIL
    if (_imu.register_gyro(gyro_instance, HIL_IMU_RATE_HZ,
                           AP_HAL::Device::make_bus_id(AP_HAL::Device::BUS_TYPE_UNKNOWN, 0, 1, DEVTYPE_INS_HIL)) &&
        _imu.register_accel(accel_instance, HIL_IMU_RATE_HZ,
                            AP_HAL::Device::make_bus_id(AP_HAL::Device::BUS_TYPE_UNKNOWN, 0, 2, DEVTYPE_INS_HIL))) {
        started = true;
    }
}

#endif // AP_HIL_ENABLED
