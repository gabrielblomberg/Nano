#include "Debug.hpp"

#if DEBUG

void InitDebugging()
{
    Serial.begin( 9600 );
}

#else

void InitDebugging() {};

#endif
