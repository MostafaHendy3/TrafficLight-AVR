## AVR Drivers

This repository contains drivers for AVR microcontrollers. The drivers are written in C and are intended to be used with the AVR-GCC compiler.

### Usage

To use the drivers, simply copy the files you need into your project directory and include them in your source code. 
- ADD directory to the include path of your project.
- Include the header file of the driver you want to use in your source code. 
- Add the source file of the driver you want to use to your project.


### Features

The following drivers are currently available:

MCAL (MICROCONTROLLER ABSTRACTION LAYER):
- GPIO
- ADC
- External Interrupts

HAL (HARDWARE ABSTRACTION LAYER):
- LCD 
- Keypad
- LED
- 7-Segment Display
- LM35 Temperature Sensor
- switch


### future work
- Timers
- UART
- SPI
- I2C

