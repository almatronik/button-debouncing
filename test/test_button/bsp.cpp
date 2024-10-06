#include "bsp.h"
#ifndef DEVENV
#include <Arduino.h>
#endif

#define INVALID 0xFFU

static uint8_t pin_number = INVALID;
static uint8_t pin_mode = INVALID;
static uint8_t pin_state = BSP_HIGH;

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    pin_number = pin;
    pin_mode = mode;
#ifndef DEVENV
    pinMode(pin, mode);
#endif
}

int bsp_digital_read(uint8_t pin)
{
    pin_number = pin;

#ifdef DEVENV
    return pin_state;
#else
    return pin_state ? digitalRead(pin) : !digitalRead(pin);
#endif
}

uint8_t bsp_get_pin_number(void)
{
    return pin_number;
}

uint8_t bsp_get_pin_mode(void)
{
    return pin_mode;
}

void bsp_set_pin_state(uint8_t state)
{
    pin_state = state;
}