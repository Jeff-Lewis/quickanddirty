# Introduction #

Setting up a N900 for MeeGo 1.2 development.

# Details #
## Enable DualBoot ##
Boot to Maemo5.
  * Enable [devel-extras](http://wiki.maemo.org/Extras-devel)
  * Install System > uboot-pr13
  * Disable devel-extras
More [Information](http://wiki.meego.com/ARM/N900/Install/Dual_Boot).

## Download flasher ##
http://tablets-dev.nokia.com/maemo-dev-env-downloads.php?f=maemo_flasher-3.5_2.5.2.2_i386.deb
```
sudo dpkg -i maemo_flasher*i386.deb
```

## Download card image ##
```
wget http://repository.maemo.org/meego/n900-de/archive/1.1.99.2.20110412.6.DE.2011-04-15.1/images/mg-handset-armv7nhl-n900-de-acceptance/mg-handset-armv7nhl-n900-de-acceptance-1.1.99.2.20110412.6.DE.2011-04-15.1-mmcblk0p.raw.bz2
```

## Download kernel image ##
```
http://repository.maemo.org/meego/n900-de/archive/1.1.99.2.20110412.6.DE.2011-04-15.1/images/mg-handset-armv7nhl-n900-de-acceptance/mg-handset-armv7nhl-n900-de-acceptance-1.1.99.2.20110412.6.DE.2011-04-15.1-vmlinuz-2.6.37-9.1-adaptation-n900
```

## Install MeeGo 1.2 ##
### Install rootfs to MicroSD ###
change /dev/sdX to your microsd card device.
```
sudo apt-get install pv
bzcat mg-handset-armv7nhl-n900-de-acceptance-1.1.99.2.20110412.6.DE.2011-04-15.1-mmcblk0p.raw.bz2 | pv | sudo dd bs=4096 of=/dev/sdX
```
### Install Kernel ###
  * disconnect N900 from Host
  * power off N900
  * run flasher
```
sudo flasher-3.5 -l -k mg-handset-armv7nhl-n900-de-acceptance-1.1.99.2.20110412.6.DE.2011-04-15.1-vmlinuz-2.6.37-9.1-adaptation-n900 -b
```
  * connect N900 when you see:
```
Suitable USB device not found, waiting.
```
# Now you have a DualBoot system for Maemo5 and MeeGo 1.2 #
The system will boot to MeeGo 1.2 DE automatically and you can change things back to Maemo5 by pressing a key in uboot and typing `run noloboot`