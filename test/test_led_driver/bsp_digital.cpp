#ifndef DEVENV
#include <Arduino.h>
#endif
#include <stdbool.h>
#include "bsp_digital.h"

static uint8_t pin_num = 0xFF;
static uint8_t pin_mode = 0xFF;
static uint8_t pin_state = 0xFF;
static uint8_t pin_status = true;

void bsp_set_pin_status(bool status)
{
    pin_status = status;
}

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    pin_num = pin;
    pin_mode = mode;
#ifndef DEVENV
    pinMode(pin, mode);
#endif
}

void bsp_digital_write(uint8_t pin, uint8_t val)
{
    pin_num = pin;
    pin_state = val;
#ifndef DEVENV
    digitalWrite(pin, val);
#endif
}

uint8_t bsp_digital_read(uint8_t pin)
{
    pin_num = pin;
#ifdef DEVENV
    return (pin_status ? pin_state : !pin_state);
#else
    return (pin_status ? digitalRead(pin) : !digitalRead(pin));
#endif
}

uint8_t bsp_get_pin_num(void)
{
    return pin_num;
}

uint8_t bsp_get_pin_mode(void)
{
    return pin_mode;
}
