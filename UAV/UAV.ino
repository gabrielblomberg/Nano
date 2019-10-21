#include <Arduino.h>

#include "Debug.hpp"
#include <Arduino.h>

#include "Debug.hpp"
#include "Display.hpp"
#include "Accelerometer.hpp"
#include "Transceiver.hpp"
#include "Button.hpp"

Accelerometer *accelerometer = nullptr;
Transceiver *transceiver = nullptr;
Display *display = nullptr;
Button *button = nullptr;

bool restart;
unsigned long flight_begin;
unsigned long flight_end;

void setup()
{
    // Ensure values are initialised correctly
    restart = false;
    flight_begin = 0;
    flight_end = 0;

    // Initalises the serial connection and debug macros depending on whether
    // debugging is enabled in Debug.hpp
    InitDebugging();

    // Heap allocation because *Arduino* oOoOOoO
    // These are effectively static and don't need to be deleted.
    display = new Display();
    accelerometer = new Accelerometer();
    transceiver = new Transceiver();
    button = new Button();

    // Bind each button press type to it's corresponding action in the lambda
    // function. These should be as fast as possible so as not to hold up
    // processing.
    button->Bind(ButtonPattern::SingleShort, [](){
        transceiver->TransmitAccessCode();
    });
    button->Bind(ButtonPattern::SingleLong, [](){
        display->SetAll(LOW);
        restart = true;
    });
    button->Bind(ButtonPattern::DoubleShort, [](){
        for (int i = 0; i < 10; i++) {
            display->OddFlash();
            delay(100);
        }
        display->SetAll(LOW);
    });
    button->Bind(ButtonPattern::DoubleLong, [](){
        accelerometer->Calibrate();
        for (int i = 0; i < 3; i++) {
            display->SetAll(HIGH);
            delay(200);
            display->SetAll(LOW);
            delay(200);
        }
    });

}

void Standby()
{
    DEBUG_PRINTLN("Standing by!");
    while (accelerometer->Magnitude() < accelerometer->LowerLimit())
    {
        display->TrainIncrement();
        delay(30);
        button->Check();
        button->Evaluate();
        if (restart) return;
    }
    display->SetAll(LOW);
}

void Flying()
{
    // Experimentally, Magnitude() takes 0-2 ms to execute so no choke point
    // calling twice in the following loop.
    DEBUG_PRINTLN("Flying!");

    // While no peak in acceleration or within at least one second
    // since flying, transmit the acceleration and check button state.
    while ( (accelerometer->Magnitude() < accelerometer->LowerLimit()) ||
            (millis() - flight_begin < 1000) )
    {
        // According to the documentation, blocks until ACKed or until timeout
        // is reached, that is 60-70 ms. Choke point if no base station present.
        transceiver->PushAcceleration(accelerometer->Query());
        button->Check();
        button->Evaluate();
        
        if (restart) return;
    }

}

// Displays the flight duration in binary
void Landed(int duration)
{
    DEBUG_PRINTLN("Landed! Duration: "); DEBUG_PRINT(duration);
    while (!restart) {
        display->DisplayInt(duration);
        button->Check();
        button->Evaluate();
    }
}

void loop()
{
    restart = false;

    Standby();
    flight_begin = millis();
    if (restart) return;

    Flying();
    flight_end = millis();
    if (restart) return;

    int duration = (flight_end - flight_begin)/1000;
    Landed(duration);
}
