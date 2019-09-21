#include "Accelerometer.hpp"

#include <Arduino.h>
#include "Debug.hpp"

Accelerometer::Accelerometer()
    : m_mpu(MPU6050())
    , m_magnitude_offset(0)
{
    m_mpu.initialize();
    if (!m_mpu.testConnection()) {
        DEBUG_PRINT("Failed to connected to accelerometer");
    }
    else {
        DEBUG_PRINT("Successfully connected to accelerometer");
    }
    delay(50);
    m_magnitude_offset = Magnitude();
}

Accelerometer::~Accelerometer() {}

AccelerationalData Accelerometer::Query()
{
    AccelerationalData data;

    // Get accelerational data from accelerometer
    m_mpu.getMotion6(
        &data.ax, &data.ay, &data.az,
        &data.gx, &data.gy, &data.gz
    );

    // Get the timestamp from internal clock
    data.time_stamp = millis()/1000;

    return data;
}

int Accelerometer::Magnitude()
{
    AccelerationalData data = Query();
    int mag = sqrt( pow(data.ax, 2) + pow(data.ay, 2) + pow(data.az, 2));
    return  mag - m_magnitude_offset;
}