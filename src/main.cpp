/**
 * In this assignment you are supposed to test and develop a single-instance module (button) to
 * debounce a push button and develop a program using the button module according to the requirements below.
 * 
 * The button module requirements
 * 
 * Use TDD and follow the dual targeting strategy  to test and develop the button module.
 * To build and run the test use make or cmake.
 * The internal pull-up resistor of the pin connected to the button shall be enabled
 * To read the pin and update the debounced state of the button there is an update function in the interface of the button module. This function is called intervally by the client of the module.
 *     If there are 5 consecutive states of the same value, it means that state of the button is stable and reliable.
 *  The module shall be able to detect RELEASED and PRESSED debounced states.
 *  The module shall be able to detect debounced RISING and FALLING edges.
 *     An edge is a unique event and it shall be readable only once
 * 
 * The program(int main.cpp) requirements
 *     Connect a push button to pin 34 of ESP32
 *     Using a timer interrupt, call the update function of the button module every 2 ms to update the debounced state of the button.
 *     When the button is pressed, on the falling edges of the button, print “Falling edge” to the terminal.
 * 
 * Grading
 *     To get G(godkänd) all the above requirements shall be fulfilled.
 *     To get VG(väl godkänd) all the above requirements shall be fulfilled and the module shall be tested fully and the code coverage shall be 100%. 
 */

#include "bsp.h"
#include "button.h"

static uint8_t state = BUTTON_RELEASED;

void setup()
{
    button_init(34);
    Serial.begin(115200);

    constexpr uint16_t DIVIDER{80};
    constexpr uint32_t INTERVAL{2000};

    hw_timer_t *timer{timerBegin(0, DIVIDER, true)};
    timerAttachInterrupt(timer, &button_update_state, true);
    timerAlarmWrite(timer, INTERVAL, true);
    timerAlarmEnable(timer);
}

void loop()
{
    state = button_get_state();
    
    if (state == BUTTON_FALLING_EDGE)
    {
        Serial.printf("FALLING EDGE\n");
    }
}