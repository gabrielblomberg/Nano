#include "Display.hpp"

#include <Arduino.h>

const int LED::DEFAULT_PIN_COUNT = 6;

const pin LED::DEFAULT_PINS[LED::DEFAULT_PIN_COUNT] = {
    LED::Pins::p0,
    LED::Pins::p1,
    LED::Pins::p2,
    LED::Pins::p3,
    LED::Pins::p4,
    LED::Pins::p5,
};

LED::Display::Display(const pin *display_pins, const int len)
    : m_display_pins(display_pins)
    , m_pin_count(len)
{
    // Set all pins to output
    for (int i = 0; i < m_pin_count; i++) {
        pinMode(m_display_pins[i], OUTPUT);
    }
}


void LED::Display::SetPin(pin p, int state)
{
    if ((-1 < p) && (p < m_pin_count)) {
        digitalWrite(m_display_pins[p], state);
    }
}

void LED::Display::DisplayInt(int integer) const
{
    // For the ith bit
    for (int i = 0; i < m_pin_count; i++) {
        //shift it to the front of the int and bitwise AND it with 0b00000001, 
        // to remove trailing bits. This is the value encoded as an int of the
        // bit at position i.
        int state = (integer >> i) & 1 ? HIGH : LOW;
        // Set the corresponding pin to this state.
        digitalWrite(m_display_pins[i], state);
    }
}

void LED::Display::TrainIncrement()
{
    // This state sets the first LED on, rather than starting from the second
    // if pin_on - 0 and forwards = true;
    static bool forwards = false;
    static pin pin_on = 1;

    if (forwards) {
        // If the next pin is not out of range, turn the current LED off and the
        // next one on.
        if (pin_on + 1 < m_pin_count) {
            digitalWrite(m_display_pins[pin_on], LOW);
            pin_on++;
            digitalWrite(m_display_pins[pin_on], HIGH);
        }
        // Otherwise set the direction to backwards
        else {
            // If there is a delay between function calls, last led will stay on
            // twice as long when changing directions.
            forwards = false;

            // Run iteration of opposite direction to mitigate
            digitalWrite(m_display_pins[pin_on], LOW);
            pin_on--;
            digitalWrite(m_display_pins[pin_on], HIGH);
        }
    }
    else /* Backwards */ {
        // Analogous to above comments
        if (pin_on - 1 >= 0) {
            digitalWrite(m_display_pins[pin_on], LOW);
            pin_on--;
            digitalWrite(m_display_pins[pin_on], HIGH);
        }
        else {
            forwards = true;
            digitalWrite(m_display_pins[pin_on], LOW);
            pin_on++;
            digitalWrite(m_display_pins[pin_on], HIGH);
        }
    }
}

void LED::Display::DebugFlash(int n, int ms) const
{
    pin debug_pin = m_display_pins[m_pin_count - 1];
    for (int i = 0; i < n; i++) {
        digitalWrite(debug_pin, HIGH);
        delay(ms);
        digitalWrite(debug_pin, LOW);
        delay(ms);
    }
}