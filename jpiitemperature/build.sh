#!/bin/sh
/usr/bin/avr-gcc -mmcu=attiny2313 -o main.elf main.c
/usr/bin/avr-objcopy -R .eeprom -O ihex main.elf jpiitemperature.hex


