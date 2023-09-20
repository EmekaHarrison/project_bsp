#include <stdbool.h>
#include "led_driver.h"
#include "bsp_digital.h"

static bool initialized = false;

void led_driver_init(void)
{
    bsp_pin_mode(LED_PIN, BSP_OUTPUT);
    initialized = true;
}

bool led_driver_set_state(uint8_t state)
{
    bool status = false;

    if (initialized)
    {
        if ((state == LED_DRIVER_LOW) || (state == LED_DRIVER_HIGH))
        {
            uint8_t led_state = (state == LED_DRIVER_LOW) ? BSP_LOW : BSP_HIGH;

            bsp_digital_write(LED_PIN, led_state);

            if (led_state == bsp_digital_read(LED_PIN))
            {
                status = true;
            }
        }
    }

    return status;
}
