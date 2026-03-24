#include <AP_HAL/AP_HAL.h>
#include "AP_InertialSensor_HIL.h"

#if AP_HIL_ENABLED

const extern AP_HAL::HAL& hal;

// HIL IMU update rate — matches the expected HIL_SENSOR send rate
#define HIL_IMU_RATE_HZ 200

AP_InertialSensor_HIL::AP_InertialSensor_HIL(AP_InertialSensor &imu) :
    AP_InertialSensor_Backend(imu),
    started(false),
    hil_data_received(false)
{
}

void AP_InertialSensor_HIL::handle_hil(const Vector3f &accel, const Vector3f &gyro, float temperature)
{
    if (!started) {
        return;
    }

    hil_data_received = true;

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
    if (!started) {
        return false;
    }

    // Before the first HIL_SENSOR arrives (e.g. during boot), push synthetic
    // samples so the scheduler and EKF don't panic waiting for IMU data.
    // Once real HIL data is flowing, handle_hil() provides all samples.
    if (!hil_data_received) {
        const Vector3f synthetic_accel(0.0f, 0.0f, -GRAVITY_MSS);
        const Vector3f synthetic_gyro(0.0f, 0.0f, 0.0f);
        _notify_new_accel_raw_sample(accel_instance, synthetic_accel, AP_HAL::micros64());
        _notify_new_gyro_sensor_rate_sample(gyro_instance, synthetic_gyro);
        _notify_new_gyro_raw_sample(gyro_instance, synthetic_gyro, AP_HAL::micros64());
    }

    update_accel(accel_instance);
    update_gyro(gyro_instance);
    return true;
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
