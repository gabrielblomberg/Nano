#include "Accelerometer.hpp"

#include <Arduino.h>
#include "Debug.hpp"

Accelerometer::Accelerometer()
    : m_mpu(MPU6050())
    , m_magnitude_offset(0)
{
    m_mpu.initialize();
    if (!m_mpu.testConnection()) {
        DEBUG_PRINTLN("Accelerometer connection failed.");
    }
    else {
        DEBUG_PRINTLN("Accelerometer connected!");
    }

    // Set the range of the accelerometer to max
    m_mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
    m_mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);

    // Allow time for the accelerometer to start before querying
    delay(50);
    m_magnitude_offset = Magnitude();
}

Accelerometer::~Accelerometer() {}

AccelerationalData Accelerometer::Query()
{
    static int accel_scale = FS_16_ACCEL_SCALAR;
    static int gyro_scale = FS_2000_GYRO_SCALAR;

    int16_t ax, ay, az, gx, gy, gz;

    // Get accelerational data from accelerometer
    m_mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // Scale down axial and gyroscopic acceleration to Gs
    AccelerationalData data = {
        (float)ax / accel_scale,
        (float)ay / accel_scale,
        (float)az / accel_scale,
        (float)gx / gyro_scale,
        (float)gy / gyro_scale,
        (float)gz / gyro_scale,
    };

    // Get the timestamp from internal clock
    data.time_stamp = millis()/1000;

    return data;
}

float Accelerometer::Magnitude()
{
    AccelerationalData data = Query();
    float mag = sqrt( pow(data.ax, 2) + pow(data.ay, 2) + pow(data.az, 2));
    return  mag - m_magnitude_offset;
}

void Accelerometer::Calibrate()
{
    DEBUG_PRINTLN("Calibrating...");

    m_mpu.CalibrateAccel(100);
    m_mpu.CalibrateGyro(100);

    AccelerationalData data = Query();
    m_magnitude_offset = sqrt(
        pow(data.ax, 2) + pow(data.ay, 2) + pow(data.az, 2)
    );

    DEBUG_PRINTLN();
    DEBUG_PRINT("Calibrated! New magnitude offset is ");
    DEBUG_PRINTLN(m_magnitude_offset);
}