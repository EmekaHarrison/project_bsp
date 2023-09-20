#include "unity.h"
#include "led_driver.h"
#ifndef DEVENV
#include <Arduino.h>
#endif
#include "bsp_digital.h"

void setUp(void) {}
void tearDown(void) {}

void test_led_driver(void)
{
    // Test for an uninitialized condition
    TEST_ASSERT_FALSE(led_driver_set_state(LED_DRIVER_HIGH));

    led_driver_init();
    TEST_ASSERT_EQUAL_UINT8(LED_PIN, bsp_get_pin_num());
    TEST_ASSERT_EQUAL_UINT8(BSP_OUTPUT, bsp_get_pin_mode());

    TEST_ASSERT_TRUE(led_driver_set_state(LED_DRIVER_HIGH));
    TEST_ASSERT_EQUAL_UINT8(LED_PIN, bsp_get_pin_num());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_HIGH, bsp_digital_read(LED_PIN));

    bsp_set_pin_status(false);
    TEST_ASSERT_FALSE(led_driver_set_state(LED_DRIVER_HIGH));
    TEST_ASSERT_EQUAL_UINT8(LED_PIN, bsp_get_pin_num());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_LOW, bsp_digital_read(LED_PIN));
    bsp_set_pin_status(true);

#ifndef DEVENV
    delay(2000);
#endif

    TEST_ASSERT_TRUE(led_driver_set_state(LED_DRIVER_LOW));
    TEST_ASSERT_EQUAL_UINT8(LED_PIN, bsp_get_pin_num());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_LOW, bsp_digital_read(LED_PIN));

    TEST_ASSERT_FALSE(led_driver_set_state(0xF0));
}

#ifdef DEVENV
int main(void)
{
#else
void loop()
{
}

void setup()
{
    delay(2000);
#endif

    UNITY_BEGIN();

    RUN_TEST(test_led_driver);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();
#endif
}
