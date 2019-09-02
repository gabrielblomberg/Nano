#include "Defs.hpp"
#include "Display.hpp"

void setup() {}

// main()
void loop()
{
    Display display;

    // while (|Acceleration| < 0.5);

    // int start_time = millis();
    // do stuff
    // int end_time = millis();

    // int duration = (end_time - start_time)/1000;
    
    // display.DisplayInt(duration);
    while (1) {
      for (int i = 0; i < 32; i++) {
        display.DisplayInt(i);
        delay(100);
      }
    }
}
