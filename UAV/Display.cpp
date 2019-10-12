#include "Display.hpp"

#include <Arduino.h>

const int LED_DEFAULT_PIN_COUNT = 6;

const pin LED_DEFAULT_PINS[LED_DEFAULT_PIN_COUNT] = {
    LEDPins::p0,
    LEDPins::p1,
    LEDPins::p2,
    LEDPins::p3,
    LEDPins::p4,
    LEDPins::p5,
};

Display::Display(const pin *display_pins, const int len)
    : m_display_pins(display_pins)
    , m_pin_count(len)
{
    // Set all pins to output
    for (int i = 0; i < m_pin_count; i++) {
        pinMode(m_display_pins[i], OUTPUT);
    }
}


void Display::SetPin(pin p, int state) const
{
    if ((-1 < p) && (p < m_pin_count)) {
        digitalWrite(m_display_pins[p], state);
    }
}

void Display::SetAll(int state) const
{
    for (int i = 0; i < m_pin_count; i++) {
        digitalWrite(m_display_pins[i], (state ? HIGH : LOW));
    }
}

void Display::DisplayInt(int integer) const
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

void Display::FlashLast() const
{
    static const int iterations = 10;
    static int count = iterations;
    static bool state = false;

    if (count == 0) {
        digitalWrite(m_display_pins[m_pin_count - 1], (state ? HIGH : LOW) );
        state = !state;
        count = iterations;
    }
    else {
        count--;
    }
}

void Display::TrainIncrement() const
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

void Display::OddFlash() const
{
    static bool display_odd_pins = false;
    for (int i = 0; i < m_pin_count; i++) {
        digitalWrite(m_display_pins[i], 
            (i % 2 == (display_odd_pins ? 1 : 0)
             ? HIGH : LOW)
        );
    }
    display_odd_pins = !display_odd_pins;
}