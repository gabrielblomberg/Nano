#ifndef DISPLAY_H
#define DISPLAY_H

#include "defs.hpp"

// Pin definitions
#define LED_P0 0
#define LED_P1 1
#define LED_P2 2
#define LED_P3 3
#define LED_P4 4
#define LED_P5 5

class Display
{
    private:

        static const int m_display_pin_count = 5;

        // Array of pins connected to each LED, in order
        int m_display_pins[m_display_pin_count] = {
            LED_P0,
            LED_P1,
            LED_P2,
            LED_P3,
            LED_P4
        };

        int m_debug_pin = LED_P5;

    public:

        Display();

        // Displays a given integer on the first 5 LEDs
        void DisplayInt(int integer);

        // Flashes the LEDs in sequence
        void Train();

        // Flashes the 6th led n times, with ms millisecond delay between each
        // flash
        void DebugFlash(int n, int ms);
    
};

#endif // DISPLAY_H