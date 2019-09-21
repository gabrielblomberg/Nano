#include <Arduino.h>

#include "Debug.hpp"
#include "Display.hpp"
#include "Accelerometer.hpp"
#include "Transceiver.hpp"
#include "Button.hpp"

using namespace LED;

Accelerometer *accelerometer = nullptr;
Transceiver *transceiver = nullptr;
Display *display = nullptr;
Button *button = nullptr;

bool restart;
unsigned long flight_begin;
unsigned long flight_end;

void setup()
{
    InitDebugging();

    // Heap allocation because *Arduino* oOoOOoO
    // These are effectively static and don't need to be deleted.
    display = new Display();
    accelerometer = new Accelerometer();
    transceiver = new Transceiver();
    button = new Button();

    // Button bindings to lambda functions. These should be as fast as possible
    // so as not to hold up processing.
    button->Bind(ButtonPattern::SingleShort, [&](){
        transceiver->TransmitAccessCode();
    });
    button->Bind(ButtonPattern::SingleLong, [&](){
        restart = true;
    });
    button->Bind(ButtonPattern::DoubleShort, [&](){
        for (int i = 0; i < 10; i++) {
            display->TrainIncrement();
            delay(100);
        }
    });

}

void Standby()
{
    DEBUG_PRINTLN("Standby");
    while (accelerometer->Magnitude() < accelerometer->LowerLimit())
    {
        display->TrainIncrement();
        delay(30);
        button->Check();
        button->Evaluate();
        if (restart) return;
    }

}

void Flying()
{
    DEBUG_PRINTLN("Flying");
    bool maxed_accl = false; // max acceleration
    bool maxed_time = false; // Time before accepting change in acceleration
    
    // While no peak in acceleration or withinn at least one second
    // since flying
    while ( (accelerometer->Magnitude() < accelerometer->LowerLimit()) ||
            (millis() - flight_begin < 1000) )
    {
        if (restart) return;
        transceiver->PushAcceleration(accelerometer->Query());
        button->Check();
        button->Evaluate();
    }

}

void Landed(int duration)
{
    DEBUG_PRINTLN("Landed. Duration: "); DEBUG_PRINT(duration);
    while (!restart) {
        display->DisplayInt(duration); // Incase TrainIncrement is called
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