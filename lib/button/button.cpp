#include "bsp.h"
#include "button.h"

// #define SAMPLES (5U)
#define INVALID 0xFFU

static uint8_t pin_number = INVALID;
static uint8_t previous_state = BSP_HIGH;
static uint8_t current_state = BSP_HIGH;
static uint8_t debounced_state = BUTTON_RELEASED;
static uint8_t stable_count = 0;
static bool edge = false;

void button_init(uint8_t pin)
{
    pin_number = pin;
    bsp_pin_mode(pin, BSP_INPUT_PULLUP);
}

void button_update_state(void)
{
    previous_state = current_state;
    current_state = bsp_digital_read(pin_number);

    if (current_state == previous_state)
    {
        stable_count++;
    }
    else
    {
        edge = true;
        stable_count = 1; // The first time that a different state is detected is the first occurance of this state. So four more and we have a stable state.
    }
    
    if (stable_count == 5)
    {
        if (edge)
        {
            (current_state == BSP_HIGH) ? debounced_state = BUTTON_RISING_EDGE : debounced_state = BUTTON_FALLING_EDGE;
            edge = false;
        }
        else
        {
            (current_state == BSP_HIGH) ? debounced_state = BUTTON_RELEASED : debounced_state = BUTTON_PRESSED;
        }
        stable_count--;
    }
}

uint8_t button_get_state(void)
{
    uint8_t state;

    (pin_number == INVALID) ? state = BUTTON_UNINITIALIZED : state = debounced_state;

    if (debounced_state == BUTTON_FALLING_EDGE)
    {
        debounced_state = BUTTON_PRESSED;
    }
    else if (debounced_state == BUTTON_RISING_EDGE)
    {
        debounced_state = BUTTON_RELEASED;
    }
    else
    {
        ;
    }

    return state;
}