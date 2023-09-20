#include <Arduino.h>
#include "bsp_digital.h"

int bsp_digital_read(uint8_t pin)
{
    return digitalRead(pin);
}

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    pinMode(pin, mode);
}

void bsp_digital_write(uint8_t pin, uint8_t val)
{
    digitalWrite(pin, val);
}
