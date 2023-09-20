#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

#define LED_PIN 21

#define LED_DRIVER_LOW 0
#define LED_DRIVER_HIGH 1

void led_driver_init(void);

bool led_driver_set_state(uint8_t state);

#endif /* LED_DRIVER_H */
