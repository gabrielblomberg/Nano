#include "Button.hpp"

#include <Arduino.h>
#include "Debug.hpp"

Button::Button(pin p)
    : m_button_pin(p)
    , m_last_state(ButtonState::Off)
    , m_single_short_binding(&DummyCallback)
    , m_single_medium_binding(&DummyCallback)
    , m_single_long_binding(&DummyCallback)
    , m_double_short_binding(&DummyCallback)
    , m_double_long_binding(&DummyCallback) 
{
}

void Button::Bind(ButtonPattern pattern, void (*func)(void) )
{
    switch (pattern)
    {
    case ButtonPattern::SingleShort  : m_single_short_binding  = func; break;
    case ButtonPattern::SingleMedium : m_single_medium_binding = func; break;
    case ButtonPattern::SingleLong   : m_single_long_binding   = func; break;
    case ButtonPattern::DoubleShort  : m_double_short_binding  = func; break;
    case ButtonPattern::DoubleLong   : m_double_long_binding   = func; break;
    default : break;
    }
}

void Button::Check()
{
    static int analog_limit = 1000;
    ButtonState state = analogRead(m_button_pin) < analog_limit
                      ? ButtonState::On : ButtonState::Off;

    if (state == m_last_state) {
        return;
    }

    if (state == ButtonState::On) { // Rising edge
        if (m_first_press == 0) { // of first press
            DEBUG_PRINTLN("First Rising Edge");
            m_first_press = millis();
        }
        else { // of second press
            DEBUG_PRINTLN("Second Rising Edge");
            m_second_press = millis();
        }
    }
    else { // Falling edge
        if (m_first_release == 0) { // of first release
            DEBUG_PRINTLN("First Falling Edge");
            m_first_release = millis();
        }
        else { // of second release
            DEBUG_PRINTLN("Second Falling Edge");
            m_second_release = millis();
        }
    }

    DEBUG_PRINT("First Press: ");  DEBUG_PRINTLN(m_first_press);
    DEBUG_PRINT("First Release: ");  DEBUG_PRINTLN(m_first_release);
    DEBUG_PRINT("Second Press: ");  DEBUG_PRINTLN(m_second_press);
    DEBUG_PRINT("Second Release: ");  DEBUG_PRINTLN(m_second_release);
    m_last_state = state;

}

void Button::Evaluate()
{
    unsigned long first_duration, second_duration;
    bool timed_out;

    if (m_first_press == 0) {
        return; // No command
    }
    else if (m_first_release == 0) {
        return; // First press being held down
    }

    timed_out = millis() - m_first_release > s_PRESS_SEPERATION;

    // If timed out and only first button pressed
    if (timed_out) {
        if (m_second_press == 0) {

            // Must be a single press
            first_duration = m_first_release - m_first_press;
            ResetTimes();

            if (first_duration < s_SHORT_RESPONSE) { // It was a short Press
                m_single_short_binding();
                return;
            }
            else if (first_duration < s_MEDIUM_RESPONSE) { // It was a medium press
                m_single_medium_binding();
                return;
            }
            else { // It was a long press
                m_single_long_binding();
                return;
            }
        }
    }

    // If a second press has occured
    if (m_second_press > 0) {
        if (m_second_release > 0) {

            // Calculate second duration
            first_duration = m_first_release - m_first_press;
            second_duration = m_second_release - m_second_press;
            ResetTimes();

            if (first_duration < s_SHORT_RESPONSE) { // It was a short double press
                m_double_short_binding();
                return;
            }
            else { // It was a long double press
                m_double_long_binding();
            }
        }
    }

}

void Button::ResetTimes()
{
    m_first_press= 0;
    m_first_release = 0;
    m_second_press = 0;
    m_second_release = 0; 
}