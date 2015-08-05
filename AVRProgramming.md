# Introduction #


# Compiling and Burning for ATtiny2313 #
## avr-gcc ##
### make elf ###
```
# avr-gcc -mmcu=attiny2313 -o main.elf main.c
```
## avr-objcopy ##
### make hex from elf ###
```
# avr-objcopy -R .eeprom -O ihex main.elf main.hex
```
## avrdude ##
### write hex ###
```
# avrdude -c avrispmkII -P usb -p t2313 -U flash:w:main.hex
```

# Errors #
## avrdude: stk500v2\_paged\_write: write command failed with 128 ##
_Apparently the factory setting for the clock on these chips is fairly random, so you need to set that explicitly before you try doing anything else like uploading code. If you don't do that, then you'll get a bunch of nasty timeout errors like avrdude: stk500v2\_paged\_write: write command failed with 128. So set the clock by dropping into the avr terminal:_
Source: [blog.kfish.org](http://blog.kfish.org/2007/02/atmel-avr-isp-mkii-avrdude-ubuntu.html)
```
$ avrdude -c avrispmkII -P usb -p m8 -F -u -t
avrdude> sck 10
avrdude> quit
```