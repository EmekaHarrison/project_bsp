#ifndef BSP_SERIAL_H
#define BSP_SERIAL_H

#include <stdint.h>
#include <stdbool.h>

#define BAUD_RATE 9600

void bsp_serial_begin(void);

void bsp_serial_print(const char *str);

int bsp_serial_available(void);

char bsp_serial_read(void);

// Some helper functions to get access to the internal data of this test double
void bsp_set_user_input(char chr);
char *bsp_get_serial_output(void);
bool bsp_get_serial_init(void);

#endif /* BSP_SERIAL_H */
