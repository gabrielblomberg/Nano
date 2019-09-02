#include "Display.hpp"

#include <Arduino.h>

Display::Display()
{
    for (pin p : m_display_pins) {
        pinMode(p, OUTPUT);
    }
}

void Display::DisplayInt(int integer)
{
    static bool forwards = true;

    if (forwards) {
        for (int i = 0; i < m_display_pin_count; i++) {
            int state = (integer >> i) & 1 ? HIGH : LOW;
            digitalWrite(m_display_pins[i], state);
        }
    }
    else {
        for (int i = m_display_pin_count; i >= 0; i--) {
            int state = (integer >> i) & 1 ? HIGH : LOW;
            digitalWrite(m_display_pins[i], state);
        }
    }

}

void Display::Train()
{
    static int delay_ms = 50;

    // Set the first LED to HIGH
     digitalWrite(m_display_pins[0], HIGH);

    // Set the next LED HIGH and the one before it LOW until last led is HIGH
    for (int i = 1; i < m_display_pin_count; i++) {
        digitalWrite(m_display_pins[i], HIGH);
        digitalWrite(m_display_pins[i - 1], LOW);
        delay(delay_ms);
    }
    
    // Starting from the end, set the led before HIGH and the current LED to LOW
    // until only the first LED is HIGH
    for (int i = m_display_pin_count; i >= 1; i--) {
        digitalWrite(m_display_pins[i - 1], HIGH);
        digitalWrite(m_display_pins[i], LOW);
        delay(delay_ms);
    }

    // Set the last LED to LOW
    digitalWrite(m_display_pins[0], LOW);

    DebugFlash(10, 50);
}

void Display::DebugFlash(int n, int ms) {
    for (int i = 0; i < n; i++) {
        digitalWrite(m_debug_pin, HIGH);
        delay(ms);
        digitalWrite(m_debug_pin, LOW);
        delay(ms);
    }
}
