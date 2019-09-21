#ifndef DISPLAY_H
#define DISPLAY_H

typedef unsigned char pin;

namespace LED {

    // Related but non-class variables should be put in the same namespace
    enum Pins {
        p0 = 2,
        p1 = 3,
        p2 = 4,
        p3 = 5,
        p4 = 6,
        p5 = 7
    };

    extern const int DEFAULT_PIN_COUNT;
    extern const pin DEFAULT_PINS[];

    // Class for displaying patterns on the FDR LEDs. Assumes the LED pins are in
    // sequence. Default pins descrived in the LedPin enumeration above.
    class Display
    {
        public:

            Display(
                const pin *display_pins = DEFAULT_PINS,
                const int len = DEFAULT_PIN_COUNT
            );

            // Set a given pin to HIGH or LOW
            void SetPin(pin p, int state);
            
            // Sets all pins to HIGH or LOW
            void SetAll(int state);

            // Displays an integer in binary format on the 5 display pins (excluding
            // the debug pin)
            void DisplayInt(int integer) const;

            // Flashes the last LED continuously in a non-blocking in the scope
            // it is called in
            void FlashLast() const;

            // Upon multiple calls, causes a light to bounce back and forth on the 
            // display pins. Maintains data on current pin turned on.
            void TrainIncrement();

            // Flashes odd pins and even pins incrementally
            void OddFlash();

        private:
            const pin *m_display_pins;
            const int m_pin_count;

    };

}

#endif // DISPLAY_H
