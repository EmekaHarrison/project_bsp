#ifndef BSP_DIGITAL_H
#define BSP_DIGITAL_H

#include <stdint.h>
#include <stdbool.h>

#define BSP_LOW 0
#define BSP_HIGH 1
#define BSP_OUTPUT 0x03

int bsp_digital_read(uint8_t pin);

void bsp_pin_mode(uint8_t pin, uint8_t mode);

void bsp_digital_write(uint8_t pin, uint8_t val);

// Helper functions
void bsp_set_pin_status(bool status);
uint8_t bsp_get_pin_mode(void);
uint8_t bsp_get_pin_num(void);

#endif /* BSP_DIGITAL_H */
