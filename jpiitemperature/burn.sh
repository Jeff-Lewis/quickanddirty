#!/bin/bash
avrdude -P usb -p t2313 -c avrispmkII -e -U flash:w:jpiitemperature.hex
