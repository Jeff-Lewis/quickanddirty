

# Power Supply #
for each project you will need a power supply. I use regular 9V battery as usually I can find them for 1e each from [Tarjoustalo](http://www.tarjoustalo.fi/).

## Schematics ##
### 5V with 7805 ###
![http://quickanddirty.googlecode.com/svn/trunk/documents/power-supply/7805.png](http://quickanddirty.googlecode.com/svn/trunk/documents/power-supply/7805.png)<br />
[Eagle -format](http://quickanddirty.googlecode.com/svn/trunk/documents/power-supply/7805.sch)

### 3.3V with LM2937ET-3.3 ###
![http://quickanddirty.googlecode.com/svn/trunk/documents/power-supply/LM2937ET-3.3.png](http://quickanddirty.googlecode.com/svn/trunk/documents/power-supply/LM2937ET-3.3.png)
<br />
[Eagle -format](http://quickanddirty.googlecode.com/svn/trunk/documents/power-supply/LM2937ET-3.3.sch)

### USB ###
![http://quickanddirty.googlecode.com/svn/trunk/documents/power-supply/usb.png](http://quickanddirty.googlecode.com/svn/trunk/documents/power-supply/usb.png)
<br />
[Eagle -format](http://quickanddirty.googlecode.com/svn/trunk/documents/power-supply/usb.sch)
#### Notes ####
The 1N4148 voltage drop down is around 0.6 to 0.9 so the resulting voltage will differ, but most of the MCU's can operate on scale from 2.7V to 5V so the end result is still fine.
#### Connector layout ####
![http://upload.wikimedia.org/wikipedia/commons/thumb/6/67/USB.svg/220px-USB.svg.png](http://upload.wikimedia.org/wikipedia/commons/thumb/6/67/USB.svg/220px-USB.svg.png)

# Input #
## Switch ##
### Connecting Switch to AVR ###
![http://quickanddirty.googlecode.com/svn/trunk/documents/switch/attiny2313_switch.png](http://quickanddirty.googlecode.com/svn/trunk/documents/switch/attiny2313_switch.png)
### Schematic ###
[Eagle -format](http://quickanddirty.googlecode.com/svn/trunk/documents/switch/attiny2313_switch.sch)



# Output #
## LED ##
![http://quickanddirty.googlecode.com/svn/trunk/documents/led/led_schematic.gif](http://quickanddirty.googlecode.com/svn/trunk/documents/led/led_schematic.gif)
### Connecting LED to AVR ###
![http://quickanddirty.googlecode.com/svn/trunk/documents/led/attiny2313_led.png](http://quickanddirty.googlecode.com/svn/trunk/documents/led/attiny2313_led.png)
### Schematic ###
[Eagle -format](http://quickanddirty.googlecode.com/svn/trunk/documents/led/attiny2313_led.sch)
## HD44780 ##
### Connecting HD44780 to AVR ###
![http://quickanddirty.googlecode.com/svn/trunk/documents/hd44780/attiny2313_hd44780.png](http://quickanddirty.googlecode.com/svn/trunk/documents/hd44780/attiny2313_hd44780.png)<br />
4-bit data transfer.
### Schematic ###
[Eagle -format](http://quickanddirty.googlecode.com/svn/trunk/documents/hd44780/attiny2313_hd44780.sch)
## Relay ##
![http://quickanddirty.googlecode.com/svn/trunk/documents/relay/srd-s.jpg](http://quickanddirty.googlecode.com/svn/trunk/documents/relay/srd-s.jpg)<br />
With relays you can control several different devices. According to [Sanyou](http://www.sanyourelay.ca/public/products/product_list_new.php?series=43&listby=0) the typical applications are:
  * Home appliances, Air conditioner,heater,etc.
  * Office machines, PC, facsimile, etc.
  * Vending machine
  * Automotive Power-window, car antenna,door-lock,etc.
But the point is that a relay is just _a switch_. You can use lower voltage to switch higher voltage/current devices.
### Connecting a relay to avr ###
![http://quickanddirty.googlecode.com/svn/trunk/documents/relay/srd-s-schematic.png](http://quickanddirty.googlecode.com/svn/trunk/documents/relay/srd-s-schematic.png)<br />
```
1 | Output Load 1 (default state)
2 | Output Load 2
3 | to AVR PIN
4 | Input Load
5 | to AVR GND
```
![http://quickanddirty.googlecode.com/svn/trunk/documents/relay/attiny2313_relay.png](http://quickanddirty.googlecode.com/svn/trunk/documents/relay/attiny2313_relay.png)<br />
If you want to switch the Load ON when the AVR has power then connect the Load between _Output Load 2_ and _Input Load_. In this way you can switch the Load ON by setting _AVR PIN_ to HIGH.
### Schematic ###
[Eagle -format](http://quickanddirty.googlecode.com/svn/trunk/documents/relay/attiny2313_relay.sch)

### Downloads ###
  * [SRD-S Datasheet](http://quickanddirty.googlecode.com/svn/trunk/documents/relay/Sanyou-SRD.pdf)

# Projects using these #
## jpiiRelay ##
The idea of this project is to enable remote shutdown of all tv related devices (including tv itself).
### schematic ###
![http://quickanddirty.googlecode.com/svn/trunk/avr/jpiirelay/jpiirelay.png](http://quickanddirty.googlecode.com/svn/trunk/avr/jpiirelay/jpiirelay.png)<br />
[Eagle](http://quickanddirty.googlecode.com/svn/trunk/avr/jpiirelay/jpiirelay.sch) -format

### source code ###
[svn](http://code.google.com/p/quickanddirty/source/browse/#svn/trunk/avr/jpiirelay)

## jpiiWorklights ##
![http://quickanddirty.googlecode.com/svn/trunk/avr/jpiiWorklights/jpiiWorklights.picture.png](http://quickanddirty.googlecode.com/svn/trunk/avr/jpiiWorklights/jpiiWorklights.picture.png)<br />
The need for this project came from the fact that I had bought some LED Strip for 12V use from [Partco](http://www.partco.biz), so I needed some kind of controller for it. I powered the controller with 9V battery and then used relays to run 12V external power supply. The end result is nothing but quick-and-dirty, but it works for me.

### schematics ###
![http://quickanddirty.googlecode.com/svn/trunk/avr/jpiiWorklights/jpiiWorklights.sch.png](http://quickanddirty.googlecode.com/svn/trunk/avr/jpiiWorklights/jpiiWorklights.sch.png)<br />
[Eagle](http://quickanddirty.googlecode.com/svn/trunk/avr/jpiiWorklights/jpiiWorklights.sch) -format
### source code ###
[svn](http://code.google.com/p/quickanddirty/source/browse/#svn/trunk/avr/jpiiWorklights)
### pending improvements ###
  * use external interrupts
  * use sleep
  * add _test_ button for the regulator led, so now it is just spending battery power.
  * it now runs 4h with a fresh 9V battery, this needs to be fixed. should be days or months at least.
  * check current usage on all unused pins

## Handheld Power Supply for 5V and 3.3V ##
The fact is that I need a portable quick-and-dirty power supply for prototyping. So I combined both 5V and 3.3V regulators into a same box. Now all I need is a 9V battery and I am ready to go.<br />
![http://quickanddirty.googlecode.com/svn/trunk/documents/power-supply/quick-and-dirty-9v-to-5v-or-3.3v.png](http://quickanddirty.googlecode.com/svn/trunk/documents/power-supply/quick-and-dirty-9v-to-5v-or-3.3v.png)