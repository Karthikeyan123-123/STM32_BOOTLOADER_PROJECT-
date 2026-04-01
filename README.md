SIMPLE BOOTLOADER FOR BEGINNER GUIDE 

This project demonstrates a simple bootloader and application setup for the STM32F401CCU6 (Blackpill). The bootloader resides at the beginning of flash memory and is responsible for transferring control to the application, which is located at a different flash address. The application performs a basic LED blinking task using HAL drivers.

The project helps in understanding essential embedded concepts such as memory mapping, vector table relocation, and function pointer-based jumping between firmware sections. It serves as a foundational example for building more advanced bootloaders with features like firmware updates and communication interfaces.
