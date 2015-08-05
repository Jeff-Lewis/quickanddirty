# /!\ This document is under construction /!\ #

# Introduction #

The short idea is to have a remote controlled robot.


# Hardware #
| Name | Amount | Purpose | Price |
|:-----|:-------|:--------|:------|
| 5mm RGB Led | 6      | Debug lights, driving lights, etc | 1-5e each |
| Parallax Continuous Servo | 2      | controlled wheels | 10e each |
| ball caster | 1      | wheel   | 3e    |
| ATtiny2313 | 1      | support cpu - wheel and light controller | 1-4e  |
| ATmega8 | 1      | main cpu | 1-6e  |
| Wii Nunchuk Controller | 1      | The remote controller and accelerometer  | 6e for wired, 10e for wireless in konebox.fi |
| Resistors | n      | for leds and etc. | ~1e   |
| LDR  | 1      | for led brightness adjusting | ~1e   |

# Software #
C Language for the on-board microprocessors. PWM for Leds and Servos. I2C protocol for support cpu => main cpu communication and between remote controller => main cpu.

# Communication #
## RGB LEDs ##
### Automatic Brightness Adjusting ###
The vehicle should reduce the light intensity on low light conditions. This should reduce power usage, but the fact is that it does not make any sense to use intensive notification lights when less would do the same. Should be tried in action to confirm.

### Turn Actions ###
| Led | Mode | Color | Triggered On Action |
|:----|:-----|:------|:--------------------|
| Front Left | Blink | Yellow | Turn left           |
| Front Right | Blink | Yellow | Turn right          |
| Middle Left | Blink | Yellow | Turn left           |
| Middle Right | Blink | Yellow | Turn right          |
| Rear Left | Blink | Yellow | Turn left           |
| Rear Right | Blink | Yellow | Turn right          |

### Start Up ###
Fade all leds from OFF to ON with light blue color.

### Shutdown ###
Fade all leds from ON to OFF with light red color.

## Remote Controller ##
Protocol: i2c
### Commands ###
TBA

## Support cpu ##
Protocol: i2c
### Commands ###
TBA