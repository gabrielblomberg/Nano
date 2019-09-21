#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <MPU6050.h>

// Accerational data
typedef struct {
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
    int16_t time_stamp;
} AccelerationalData;

class Accelerometer
{
    const int s_magnitude_limit = 10000;

    public:
        Accelerometer();
        ~Accelerometer();

        // Query all accelerational data from the accelerometer including 
        // timestamp
        AccelerationalData Query();

        // Returns the total magnitude measured by the accelerometer
        int Magnitude();

        // Returns the value after which enough acceleration can be deemed not
        // noise
        inline int LowerLimit() { return s_magnitude_limit; }

    private:

        MPU6050 m_mpu;
        int m_magnitude_offset;
};

#endif // ACCELEROMETER_H