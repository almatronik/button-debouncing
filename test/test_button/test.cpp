#include "bsp.h"
#include "unity.h"
#include "button.h"
#ifndef DEVENV
#include <Arduino.h>
#endif

#define GPIO_NUM_34 34

void setUp() {}
void tearDown() {}

void test_button_uninitialized(void)
{
    TEST_ASSERT_EQUAL_INT8(BUTTON_UNINITIALIZED, button_get_state());
}

void test_button_initialization(void)
{
    button_init(GPIO_NUM_34);
    TEST_ASSERT_EQUAL_UINT8(GPIO_NUM_34, bsp_get_pin_number());
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
    TEST_ASSERT_EQUAL_UINT8(BSP_INPUT_PULLUP, bsp_get_pin_mode());
}

void test_button_set_state(void)
{
    bsp_set_pin_state(BSP_HIGH);
    TEST_ASSERT_EQUAL_UINT8(BSP_HIGH, bsp_digital_read(GPIO_NUM_34));
    bsp_set_pin_state(BSP_LOW);
    TEST_ASSERT_EQUAL_UINT8(BSP_LOW, bsp_digital_read(GPIO_NUM_34));
}

void test_button_get_state_BSP_HIGH(void)
{
    button_init(GPIO_NUM_34);
    bsp_set_pin_state(BSP_HIGH);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
    bsp_set_pin_state(BSP_LOW);
    for (int i = 0; i < 4; i++)
    {
        button_update_state();
    }
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
    button_update_state();
    button_update_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_PRESSED, button_get_state());
    bsp_set_pin_state(BSP_HIGH);
    for (int i = 0; i < 4; i++)
    {
        button_update_state();
    }
    TEST_ASSERT_EQUAL_UINT8(BUTTON_PRESSED, button_get_state());
    button_update_state();
    button_update_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
    button_update_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
}

void test_button_get_state_returns_edge_only_once(void)
{
    button_init(GPIO_NUM_34);
    bsp_set_pin_state(BSP_HIGH);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
    bsp_set_pin_state(BSP_LOW);
    for (int i = 0; i < 5; i++)
    {
        button_update_state();
    }
    TEST_ASSERT_EQUAL_UINT8(BUTTON_FALLING_EDGE, button_get_state());
    TEST_ASSERT_EQUAL_UINT8(BUTTON_PRESSED, button_get_state());
    bsp_set_pin_state(BSP_HIGH);
    for (int i = 0; i < 5; i++)
    {
        button_update_state();
    }
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RISING_EDGE, button_get_state());
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
}
#ifdef DEVENV
int main (void)
#else
void loop() {}
void setup()
#endif
{
    UNITY_BEGIN();

    RUN_TEST(test_button_uninitialized);
    RUN_TEST(test_button_initialization);
    RUN_TEST(test_button_set_state);
    RUN_TEST(test_button_get_state_BSP_HIGH);
    RUN_TEST(test_button_get_state_returns_edge_only_once);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();
#endif
}