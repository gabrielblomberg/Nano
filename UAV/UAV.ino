#include "Display.hpp"
#include "Movement.hpp"

void test()
{
    for (int i = 0; i < 32; i++) {
        HexToLED(i);
    }
}

void init()
{
    LEDMatrix p {1,2,3,4,5,6};
}

void loop()
{

}
