#ifndef DISPLAY_H
#define DISPLAY_H

typedef unsigned char pin;

// Pins attached to LEDs on the FDR
enum LEDPins {
    p0 = 2,
    p1 = 3,
    p2 = 4,
    p3 = 5,
    p4 = 6,
    p5 = 7
};

extern const int LED_DEFAULT_PIN_COUNT;
extern const pin LED_DEFAULT_PINS[];

// Class for displaying patterns on the FDR LEDs. Assumes the LED pins are
// in sequence. Default pins described in the LedPin enumeration above.
class Display
{
    public:

        Display(
            const pin *display_pins = LED_DEFAULT_PINS,
            const int len = LED_DEFAULT_PIN_COUNT
        );

        // Set a given pin to HIGH or LOW
        void SetPin(pin p, int state) const;
        
        // Sets all pins to HIGH or LOW
        void SetAll(int state) const;

        // Displays an integer in binary format on the display pins
        void DisplayInt(int integer) const;

        // Flashes the last LED continuously in a non-blocking way in the
        // scope it is called in
        void FlashLast() const;

        // Upon multiple calls, causes a light to bounce back and forth on
        // the display pins. Maintains data on current pin turned on.
        void TrainIncrement() const;

        // Flashes odd pins and even pins incrementally
        void OddFlash() const;

    private:
        const pin *m_display_pins;
        const int m_pin_count;

};


#endif // DISPLAY_H
