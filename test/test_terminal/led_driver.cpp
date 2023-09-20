#include "led_driver.h"
#ifndef DEVENV
#include <bsp_digital.h>
#endif

static uint8_t led_state = 0xFF;
static bool led_status = true;
static bool led_init = false;

void led_driver_init(void)
{
#ifndef DEVENV
    bsp_pin_mode(LED_PIN, BSP_OUTPUT);
#endif
    led_init = true;
}

bool led_driver_set_state(uint8_t state)
{
    if (led_status)
    {
        led_state = state;
#ifndef DEVENV
        bsp_digital_write(LED_PIN, (led_state == LED_DRIVER_HIGH) ? BSP_HIGH : BSP_LOW);
#endif
    }
    else
    {
        led_state = (state == LED_DRIVER_HIGH) ? LED_DRIVER_LOW : LED_DRIVER_HIGH;
#ifndef DEVENV
        bsp_digital_write(LED_PIN, (led_state == LED_DRIVER_HIGH) ? BSP_LOW : BSP_HIGH);
#endif
    }

    return led_status;
}

void bsp_set_led_driver_status(bool status)
{
    led_status = status;
}

bool bsp_get_led_init(void)
{
    return led_init;
}

uint8_t bsp_get_led_state(void)
{
    return led_state;
}
