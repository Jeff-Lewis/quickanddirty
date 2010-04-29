#!/bin/sh
#/usr/bin/avr-gcc -mmcu=attiny2313 -o main.elf main.c hd44780.S
/usr/bin/avr-gcc -c -mmcu=attiny2313 -o main.elf -O main.c -Wa,-ahls=main.lst
#/usr/bin/avr-gcc -c -x assembler-with-cpp -o main.elf main.S -Wa,--gstabs
/usr/bin/avr-objcopy -R .eeprom -O ihex main.elf jpiitemperature.hex


