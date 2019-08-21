#ifndef DISPLAY_H
#define DISPLAY_H

#include "defs.hpp"

class LEDMatrix
{
    public:
        LEDMatrix(pin *pins);
        ~LEDMatrix() = default;

        void HexToLED(int integer);
    
    private:
        pin *m_pins;
    
};

void HexToLED(int integer);

#endif // DISPLAY_H