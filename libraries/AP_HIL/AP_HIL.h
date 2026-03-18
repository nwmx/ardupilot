#pragma once

#include "AP_HIL_config.h"

#if AP_HIL_ENABLED

#include <AP_HAL/AP_HAL.h>
#include <AP_Math/AP_Math.h>

/*
  AP_HIL: shared state for Hardware-in-the-Loop simulation.

  Receives data from HIL_SENSOR (MAVLink ID 107) via GCS_MAVLink_Plane
  and makes it available to sensor backends (IMU, Baro, Compass, Airspeed).

  GPS data is handled separately via GPS_INPUT (ID 232) by the existing
  AP_GPS_MAV backend — no HIL involvement needed there.
*/
class AP_HIL {
public:
    // HIL sensor data received from HIL_SENSOR message
    struct sensor_data_t {
        Vector3f accel;          // m/s²  body frame, ArduPilot convention (X-fwd, Y-right, Z-down)
        Vector3f gyro;           // rad/s body frame
        Vector3f mag;            // Gauss body frame
        float abs_pressure;      // hPa
        float diff_pressure;     // hPa
        float pressure_alt;      // m
        float temperature;       // °C
        uint32_t fields_updated; // bitmask from HIL_SENSOR message
        uint32_t time_usec;      // timestamp from message (usec)
        bool updated;            // set true when new data arrives, cleared by consumer
    };

    // Singleton accessor
    static AP_HIL *get_singleton() { return _singleton; }

    AP_HIL();

    // called by Plane during init to set mode from HIL_MODE parameter
    void set_enabled(bool en) { _enabled = en; }
    bool enabled() const { return _enabled; }

    sensor_data_t sensor;

private:
    static AP_HIL *_singleton;
    bool _enabled;
};

namespace AP {
    AP_HIL *hil();
}

#endif // AP_HIL_ENABLED
