#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

// Reference: https://github.com/ElectronicCats/mpu6050
#include <MPU6050.h>

// Scalars for converting axial and gyroscopic acceleration output to Gs when
// the maximum scale is set to 16 Gs for axial acceleration and 2000 degrees
// per second on the gyroscope
#define FS_16_ACCEL_SCALAR 16384
#define FS_2000_GYRO_SCALAR 131

// Accerational data
typedef struct {
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float time_stamp;
} AccelerationalData;

class Accelerometer
{
    // Selected experimentally, limit before at which a large acceleration is
    // detected
    static constexpr float s_magnitude_limit = 0.15;

    public:
        Accelerometer();
        ~Accelerometer();

        // Query all accelerational data in Gs from the accelerometer including 
        // timestamp
        AccelerationalData Query();

        // Returns the total magnitude measured by the accelerometer
        float Magnitude();

        // Returns the value after which enough acceleration can be deemed not
        // due to noise
        inline float LowerLimit() { return s_magnitude_limit; }


        // Calibrates the accelerometer and gyroscope. Ensure the device is
        // placed on a flat plane with the z axis point upwards.
        void Calibrate();

    private:

        MPU6050 m_mpu;
        float m_magnitude_offset;
};

#endif // ACCELEROMETER_H