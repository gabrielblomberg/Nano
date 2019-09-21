#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

#define DEBUG true

// Prevent using up memory space from the serial monitor if debugging is set to
// false. Goes from 28% to 13% memory usage !!
#if DEBUG
    #define DEBUG_PRINT(x) Serial.print(x)
    #define DEBUG_PRINTLN(x) Serial.println(x)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
#endif

void InitDebugging();

#endif // DEBUG_H
