#include <Arduino>

LEDMatrix::LEDMatrix(pin *pins)
    : m_pins(led_pins)
{
    for (pin p : pins) {
        PinMode(p, OUTPUT);
    }
}

void HexToLED(int integer)
{
    static bool forwards = true;
    static int bits = 5;

    for (int b = 0; b < bits; b++) {
        digitalWrite((integer >> b) & 1));
    }

    if (forwards) { // Get the bits from MSB to LSB
        for (int bit_mask = bits - 1; bit_mask >= 0; bit_mask--) {
            digitalWrite((integer & (1 << bit_mask)) >> bit_mask);
        }
    }
    else { // Get the bits from LSB to MSB
        for (int bit_mask = 0; bit_mask < bits; bit_mask++) {
            digitalWrite((integer & (1 << bit_mask)) >> bit_mask);
        }
    }
}