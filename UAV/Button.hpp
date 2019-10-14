#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

// PLEASE put the button on an interuptable pin in the future! And on a digital
// pin.

typedef unsigned char pin;

enum class ButtonPattern {
    SingleLong,
    SingleMedium,
    SingleShort,
    DoubleShort,
    DoubleLong
};

enum class ButtonState {
    Off,
    On
};

// Class for controlling the button functionality. Uses function callback 
// bindings for different button patterns for behaviour. Why do I do this
// to myself.
class Button
{
    static const pin s_default_button_pin = A0;

    // Response times for different button patterns in milliseconds
    static const unsigned long s_SHORT_RESPONSE = 500;
    static const unsigned long s_MEDIUM_RESPONSE = 1000;
    static const unsigned long s_LONG_RESPOSNE = 1500;

    // Minimum time between evaulations
    static const unsigned long s_PRESS_SEPERATION = 300;

    public:

        // Constructor
        Button(pin p = s_default_button_pin);
        
        // Equivalent to an interupt. Call this often to update button states.
        void Check();

        // Returns the button command corresponding with the history of the
        // button presses
        void Evaluate();

        // Binds a function to a given button press type
        void Bind(ButtonPattern pattern, void (*func)(void) );

    private:

        pin m_button_pin;
        ButtonState m_last_state;

        // Times of each press / release event defined by millis()
        unsigned long m_first_press;
        unsigned long m_first_release;
        unsigned long m_second_press;
        unsigned long m_second_release;

        // Resets all press / release times
        void ResetTimes();

        // Button press bindings
        void (*m_single_short_binding)(void);
        void (*m_single_medium_binding)(void);
        void (*m_single_long_binding)(void);
        void (*m_double_short_binding)(void);
        void (*m_double_long_binding)(void);

        // Default binding to dummy callback function
        static inline void DummyCallback() {};
};

#endif // BUTTON_H