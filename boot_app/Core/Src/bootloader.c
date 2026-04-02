
#include "bootloader.h"
#include "stm32f4xx.h"
#include <stdint.h>

#define APP_ADDRESS 0x08004000

#include "stm32f4xx_hal.h"

#define BUTTON_PORT GPIOA
#define BUTTON_PIN  GPIO_PIN_0

uint8_t is_button_pressed(void)
{
    // Button pressed = LOW (because pull-up)
    HAL_Delay(2000);
    if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_RESET)
    {
        HAL_Delay(100); // debounce

        if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_RESET)
        {
            return 1;
        }
    }
    return 0;
}
uint8_t is_app_valid(void)
{
    uint32_t sp = *(volatile uint32_t*)APP_ADDRESS;

    // SRAM range check
    if ((sp >= 0x20000000) && (sp <= 0x20010000))
        return 1;

    return 0;
}

void jump_to_app(void)
{
    uint32_t appStack = *(volatile uint32_t*)APP_ADDRESS;
    uint32_t appReset = *(volatile uint32_t*)(APP_ADDRESS + 4);

    // Disable interrupts
    __disable_irq();
    HAL_DeInit();



    // Set MSP
    SCB->VTOR = 0x08004000;
    __set_MSP(appStack);
    SCB->VTOR = APP_ADDRESS;
    // Jump
    void (*app_entry)(void) = (void*)(appReset | 1);
    app_entry();
}
