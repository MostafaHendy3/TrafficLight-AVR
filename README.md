# Traffic Light Controller System

This repository contains drivers for AVR microcontrollers. The drivers are written in C and are intended to be used with the AVR-GCC compiler.

## Hardware Requirements

- ATmega32 microcontroller.
- One push button connected to INT0 pin for pedestrian.
- Three LEDs for cars (Green, Yellow, and Red), connected on port D, pins 5, 6, and 7.
- Three LEDs for pedestrians (Green, Yellow, and Red), connected on port B, pins 5, 6, and 7.

## Software Requirements

### In Normal Mode

1. Cars' LEDs will change every five seconds starting from Green, then Yellow, then Red, then Yellow, then Green.
2. The Yellow LED will blink for five seconds before moving to Green or Red LEDs.

### In Pedestrian Mode
1. Change from normal mode to pedestrian mode when the pedestrian button is pressed.
2. If pressed when the cars' Red LED is on, the pedestrian's Green LED and the cars' Red LEDs will be on for five seconds. Pedestrians can cross the street while the pedestrian's Green LED is on.
3. If pressed when the cars' Green LED is on or the cars' Yellow LED is blinking, the pedestrian Red LED will be on. Then both Yellow LEDs start to blink for five seconds. Afterward, the cars' Red LED and pedestrian Green LEDs are on for five seconds. Pedestrians must wait until the Green LED is on.
4. At the end of the two states, the cars' Red LED will be off, and both Yellow LEDs start blinking for 5 seconds. The pedestrian's Green LED is still on.
5. After the five seconds, the pedestrian Green LED will be off, and both the pedestrian Red LED and the cars' Green LED will be on.
6. Traffic light signals return to normal mode.

