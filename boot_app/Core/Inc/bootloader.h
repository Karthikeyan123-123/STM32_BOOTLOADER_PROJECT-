
#include <stdint.h>
#ifndef BOOTLOADER_H
#define BOOTLOADER_H



void jump_to_app(void);
uint8_t is_button_pressed(void);
uint8_t is_app_valid(void);

#endif
