#include "Debug.hpp"

#include <Arduino.h>

#if DEBUG

void InitDebugging()
{
    Serial.begin( 9600 );
}

#else

void InitDebugging() {};

#endif
