

# Introduction #
**WORK IN PROGRESS**

The need for this page is to collect all required information into one place. You will see the links at the bottom of this page for those pages, from which the information is coming from. Some minor adjustments has been done to the information as well as to the scripts included here.
# Status #
## 31.3.2011 - I have Qt 4.7.2 based application running on Chumby One ##
The application is called bussi and it displays the bus schedule from home to city. The Qt application is started automatically on boot.

# Installing VirtualBox on amd64 #
```
nano /etc/apt/sources.list.d/virtualbox.list
deb http://download.virtualbox.org/virtualbox/debian squeeze contrib non-free
```
```
wget -q http://download.virtualbox.org/virtualbox/debian/oracle_vbox.asc -O- | sudo apt-key add -
sudo apt-get update
sudo apt-get install virtualbox-4.0
```

# Install Debian 6 - 32-bit to virtualbox #
download netinst iso (45.5MB) and install it. Clean install without scratchbox will take about 2G. Give 1024MB of ram and 100G of disk for the image. Disk is dynamic allocated.
```
wget http://cdimage.debian.org/debian-cd/6.0.1a/i386/iso-cd/debian-6.0.1a-i386-businesscard.iso
```
select correct keyboard option for your keyboard and use english as language. select default options except:
```
on tasksel:
[ ] Graphical desktop environment
[ ] Web server
[ ] Print server
[ ] DNS server
[ ] File server
[ ] Mail server
[ ] SQL database
[*] SSH server
[ ] Laptop
[*] Standard system utilities
```
TODO: add screenshots

make port forward from virtual machine to localhost port 2222

# Installing ScratchBox on virtual Debian 6 32-bit #


```
su
```

```
nano /etc/apt/sources.list.d/scratchbox.list
deb http://scratchbox.org/debian apophis main
```

```
apt-get update
apt-get install scratchbox-core scratchbox-libs
apt-get install scratchbox-toolchain-host-gcc scratchbox-devkit-doctools scratchbox-devkit-perl scratchbox-devkit-debian-squeeze scratchbox-devkit-cputransp
```
note that cputransp is not available for amd64.

```
chgrp -R sbox /scratchbox/compilers
chmod -R g+w /scratchbox/compilers
mkdir /scratchbox/device_tools
chgrp -R sbox /scratchbox/device_tools
chmod -R g+w /scratchbox/device_tools
```

```
echo 4096 > /proc/sys/vm/mmap_min_addr
```
nano /etc/sysctl.conf
```
vm.mmap_min_addr = 4096
```

```
/scratchbox/sbin/sbox_adduser user
```

```
exit
```

```
/scratchbox/login
[sbox-NO-TARGET: ~] > sb-menu
```

```
Setup a new target and call it HOST
Select the host-gcc compiler
Select the debian-etch, perl, and doctools devkits.
Select no cpu transparency method.
Select "Yes" to installing files, and check /etc and Devkits.
Select the target by choosing Yes
```
create host target.. add screenshots here.

```
Shell restarting...
[sbox-HOST: ~] > 
```

```
cd /scratchbox/compilers
wget http://files.chumby.com/toolchain/arm-2008q3-72-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz2
tar -xvjpf arm-2008q3-72-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz
cd arm-2008q3
ln -s arm-none-linux-gnueabi/libc/usr/include .
ln -s /scratchbox/compilers/arm-2008q3/arm-none-linux-gnueabi/include/c++ include/c++
```

```
pushd ~
rm -rf sb-toolchain-extras
darcs get --set-scripts-executable http://scratchbox.org/repos/1.0/sb-toolchain-extras
popd
~/sb-toolchain-extras/confhelper/create_toolchain_conf.py > ~/sb-toolchain-extras/meta/alien-tc/arm-2008q3.conf
```

```
cd ~/sb-toolchain-extras
nano meta/alien-tc/arm-2008q3.conf
COMPILER_PACKAGE = chumby
```

```
make CONFIG=meta/alien-tc/arm-2008q3.conf -C meta/alien-tc all-sums
make CONFIG=meta/alien-tc/arm-2008q3.conf -C meta/alien-tc
cd
```

```
nano /scratchbox/compilers/arm-2008q3/target_setup.sh
os.system('echo export SBOX_EXTRA_COMPILER_ARGS=-Wno-poison-system-directories >> ' + target + '.environment')
```
# Installing tslib #
```
wget https://github.com/kergoth/tslib/tarball/master
tar -xvjpf master
cd kergoth-tslib
./configure --prefix=/psp --host=arm-linux
make && make install
cd
```
```
nano /psp/chumby.env
export TSLIB_TSDEVICE=/dev/input/event1
export TSLIB_FBDEVICE=/dev/fb0
export TSLIB_PLUGINDIR=/psp/lib/ts
export TSLIB_CONSOLEDEVICE=none
export TSLIB_CONFFILE=/psp/etc/ts.conf
export TSLIB_CALIBFILE=/psp/etc/pointercal
export LD_LIBRARY_PATH=/lib:/psp/lib
export POINTERCAL_FILE=/psp/etc/pointercal
export QWS_MOUSE_PROTO=Tslib:/dev/input/event1
#export QWS_KEYBOARD=none
export QWS_KEYBOARD=USB:/dev/input/event1
export PATH=/psp/bin:/psp/usr/bin:/psp/usr/sbin:/psp/usr/local/bin:$PATH
```
```
nano /psp/etc/ts.conf
module_raw input
```
# Installing Qt 4.7.2 for Embedded Linux #
```
wget http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.2.tar.gz
tar -xvzpf qt-everywhere-opensource-src-4.7.2.tar.gz
cd qt-everywhere-opensource-src-4.7.2
```

nano configure-qt.sh
```
#!/bin/bash
DISABLED_MODULES="-no-qt3support -no-accessibility -no-svg"
ENABLED_MODULES="-qt-libjpeg -qt-libmng -qt-gif -qt-webkit -qt-libpng -qt-libtiff -qt-zlib -qt-freetype"
MISC_FLAGS="-opensource -embedded arm -xplatform qws/linux-arm-g++ -force-pkg-config"
DEVICES="-qt-gfx-linuxfb -qt-kbd-tty -qt-mouse-tslib"
DISABLED_PACKAGES="-nomake tests -nomake examples -nomake demos -nomake docs -nomake translations"
DIRECTORIES="-L/psp/lib/ -I/psp/include/ -prefix /psp/"
./configure -release $DIRECTORIES $DISABLED_MODULES $ENABLED_MODULES $MISC_FLAGS $DEVICES $DISABLED_PACKAGES
```

```
./configure-qt.sh
make
make install
```


# Compiling a Qt application #
Add following lines to .pro
```
LIBS += /psp/lib/libts.so
INCLUDEPATH += /psp/include
```
Inside scratchbox trigger the qmake
```
/psp/bin/qmake
```

# First run on Chumby #
```
cd /psp
source chumby.env
ts_calibrate
```
then copy the calibration data from /psp/etc/pointercal for later usage, if you want to avoid calibration in future hacks.

# Hardware #
## Specs ##
```
Codename: Falconwing
454 MHz Freescale i.MX233
Hynix 512Mbit DDR SDRAM (16-bit)
2 Gbyte microSD card (brand/type and capacity may vary depending on market availability, as of 4Q09 a 2GB Kingston brand card can be found in the device, although Samsung OEM and Sandisk cards ranging from 1GB - 4GB have also been qualified for use; some anecdotal testing has seen 16GB cards working but there has been no rigorous testing for compatibility.)
One external USB 2.0 High speed port
Ralink-based RT2571 USB wifi dongle
Nanovision 320 x 240 TFT LCD with 4-wire resistive touchscreen
2W mono speaker
headphone jack
built-in microphone
snooze crash bar switch
rotary encoder for "soft" volume control (it can be repurposed for other functions, such as a Pong-style paddle controller, by you)
QN8005B FM tuner
Freescale MMA7445 accelerometer
3.3V TTL serial port, 115200, 8N1; although, you can SSH into the device, and failing that, you can plug a USB keyboard into the USB port and it will pull up a shell console, so the serial port is mostly useful for early boot debug or controlling other devices
Optional lithium ion battery, Fujifilm NP-120 or equivalent , 3.7V @ 1800mAh. Beware knock-offs that lack embedded battery safety circuitry or sub-par quality batteries.
```
## Schematics ##
http://files.chumby.com/bunnie/chumbyone_hw/chumbyone_schematics.pdf
## Gerbers ##
http://files.chumby.com/bunnie/chumbyone_hw/chumbyone_gerbers.zip
## JTAG ##
```
The pinout of P100 is as follows:
1 - 3.3V
2 - TCK
3 - TDI
4 - GND
5 - TMS
6 - TDO
7 - TRST
8 - CHUMBY_RESET
```
# Software #
## Kernel ##
### Updating Kernel ###
  1. Build normal zImage
  1. Run it through a packer script
  1. Zip it
  1. Copy to USB stick
  1. Plug USB stick into Chumby
  1. Reboot the Chumby while pressing the screen
  1. Select software update option from the menu
## Bootloader ##
```
The standard embedded linux development method is to use a bootloader with network support (such as uboot) to load the kernel into RAM over the network (normally using TFTP). This avoids all the disadvantages listed above.
Unfortunately the Chumby bootloader has no network support. Switching bootloaders (eg to uboot), while theoretically possible has several disadvantages too:
The Chumby has no ethernet interface, only USB with an internal USB/Wifi adapter or an external USB/Ethernet adapter. This means that the bootloader would require USB support as well.
The I.MX21 SoC has a non standard USB host controller not supported in bootloaders (but now included in the kernel)
Updating the bootloader is risky and could brick the device requiring a JTAG connection to fix...
```
## Boot Process ##
http://wiki.chumby.com/index.php/Falconwing_boot

# Deploying Qt Framework to Chumby One #
In order to deploy the Qt Framework you have two options. You can either create your own custom update package or you can just transfer the framework using usb stick.
## Creating a custom update package for Chumby One ##
  * Download an official update package from, and extract it
```
 $ cd
 $ wget http://files.chumby.com/resources/chumbyone/1-0-7/update.tgz
 $ mkdir update
 $ cd update
 $ tar -xvzpf ../update.tgz
updater.sh
krn
rfs.tar.gz
psp.tar.gz
chumby_boot.bin
```
  * extract psp and add qt framework files there
```
 $ mkdir psp
 $ cd psp
 $ tar -xvzpf ../psp.tar.gz
```

```
copy files now there..
```

  * repackage everything
```
 $ cd; cd update
 $ rm psp.tar.gz
 $ cd psp
 $ tar -czf ../psp.tar.gz *
 $ cd
 $ mkdir update-new
 $ cd update-new
 $ cp ~/update/psp.tar.gz .
 $ cp ~/update/krn .
 $ cp ~/update/rfs.tar.gz .
 $ cp ~/update/chumby_boot.bin .
 $ cp ~/update/updater.sh .
 $ tar -czj ../update-new.tgz *
```

## Deploy custom update to Chumby One ##
I used an old 256MB Kingston DataTraveller II. Create Fat32 primary partition. Then copy the update-new.tgz as update.tgz to the root of the usb stick. Then sync and eject the stick from your computer and insert it to chumby. Then press touch screen on Chumby One and reconnect power. Keep finger on the screen until "Special Options" are loading. Then select _install updates_ and select usb.
http://www.chumby.com/pages/latest_software#usbupdate

# Internals / Misc Notes #
## How to Clear screen ##
```
dd if=/dev/zero of=/dev/fb0 bs=640 count=240
```
## How to write to the screen ##
```
 echo -n "Hello World!" | fbwrite --color=255,255,255 --pos=1,3 -
```
## How to adjust brightness ##
```
 /sys/devices/platform/stmp3xxx-bl/backlight/stmp3xxx-bl/brightness
```
## Dumping data from input devices ##
```
hexdump /dev/input/by­id/soc­noserial­event­joystick
hexdump /dev/input/by­id/soc­noserial­event­kbd
hexdump /dev/input/by­id/soc­noserial­event­ts
hexdump /dev/input/by­id/soc­noserial­ts
```

## Set volume level ##
```
amixer sset DAC 255
```
## Play wav ##
```
aplay [filename]
```

## Prepare System and Launch Qt application at the end ##
nano /psp/rcS
```
#!/bin/sh
# Original script by scross@chumby.com
# Edited and modified heavily by juhapekka.piiroinen@gmail.com
OKPOS=37

# Turn on the backlight
echo "100" > /sys/devices/platform/stmp3xxx-bl/backlight/stmp3xxx-bl/brightness

####################
dd if=/dev/zero of=/dev/fb0 bs=640 count=240
echo -n "Entering Console mode" | fbwrite --color=255,255,255 --pos=1,1 -

###################
echo -n "Bring up udev.." | fbwrite --color=255,255,255 --pos=1,2 -
mount /dev
mknod /dev/null c 1 3
mkdir /dev/oprofile
mkdir /dev/pts
udevd --daemon
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,2 -

###################
echo -n "udev triggers.." | fbwrite --color=255,255,255 --pos=1,3 -
udevadm trigger
# Wait for all that noise to die down.
udevadm settle
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,3 -

####################
echo -n "preparing usb.." | fbwrite --color=255,255,255 --pos=1,4 -
reset_usb.sh
modprobe ehci_hcd
# Wait for things to quiet down after the USB reset
udevadm settle
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,4 -

####################
# Fire off syslog.  This quiets down the boot screen a little.
echo -n "starting syslogd.." | fbwrite --color=255,255,255 --pos=1,5 -
/sbin/syslogd -C200
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,5 -

####################
# Mount the USB partition, which should be available now that USB is loaded.
echo -n "mounting usb.." | fbwrite --color=255,255,255 --pos=1,6 -
mount /proc/bus/usb
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,6 -

#####################
# Load the i2c interface.  This will enable the dcid query program to talk to
# the dcid eeprom.
echo -n "Loading the i2c interface" | fbwrite --color=255,255,255 --pos=1,7 -
modprobe i2c-dev
modprobe i2c-stmp378x
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,7 -

####################
 # Bring audio up
echo -n "enabling audio.." | fbwrite --color=255,255,255 --pos=1,8 -
enable_audio.sh
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,8 -

###############
# Set up the rotary coder, which is present on some units.
echo -n "rotary encoder setup.." | fbwrite --color=255,255,255 --pos=1,9 -
modprobe stmp3xxx_rotdec
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,9 -

####################
# Start the accelerometer daemon. 
echo -n "Starting acceld.." | fbwrite --color=255,255,255 --pos=1,10 -                                                                                                                                   
acceld &                                                                                                   
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,10 -                    

#########################
echo -n "preparing network.." | fbwrite --color=255,255,255 --pos=1,11 -                                                                                                           
# Assign the hostname.  Generate a default one if one doesn't exist.
if [ -e /psp/hostname ]
then
    cat /psp/hostname > /proc/sys/kernel/hostname
    HOSTNAME="$(hostname)"
fi
if [ ! -e /psp/hostname -o "${HOSTNAME}" = "chumby" -o "${HOSTNAME}" = "(none)" ]
then
    HOSTNAME=chumby-$(ifconfig wlan0 | grep HWaddr | awk '{print $5}' | cut -d':' -f4,5,6 | tr ':' '-' | tr A-Z a-z )
    echo "${HOSTNAME}" > /psp/hostname
    echo "Creating default hostname: ${HOSTNAME}"
fi
cat /psp/hostname > /proc/sys/kernel/hostname


# Bring up the "local" network interface.  Other network interfaces will
# be brought up as their devices are discovered via udev events.
ifconfig lo 127.0.0.1
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,11 -

######################
# Start the network 
echo -n "Configuring network.." | fbwrite --color=255,255,255 --pos=1,12 -
start_network
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,12 -

echo -n "Starting httpd.." | fbwrite --color=255,255,255 --pos=1,13 -
/usr/sbin/httpd -h /www
echo -n "ok" | fbwrite --color=255,255,255 --pos=$OKPOS,13 -

echo -n "Getting wlan0 ip.." | fbwrite --color=255,255,255 --pos=1,14 -
ifconfig wlan0 | grep "inet addr" | cut -d' ' -f11-12 | fbwrite --color=255,255,255 --pos=6,15 -

###################
echo -n "All systems are running!" | fbwrite --color=255,255,255 --pos=1,16 -

sleep 5
source /psp/chumby.env
bussi -qws &

```

## Configure network ##
```
/psp/network_config
/psp/network_configs
```

## start ssh at boot ##
```
/psp/start_sshd
```

## disable intro ##
```
/psp/disable_intro
```

## execute qt app ##
```
source /psp/chumby.env
qtapp -qws
```


# Links & Material #
  * http://wiki.chumby.com/index.php/Scratchbox
  * https://github.com/kergoth/tslib
  * http://forum.chumby.com/viewtopic.php?id=5974
  * http://www.jespersaur.com/drupal/node/30
  * http://www.armadeus.com/wiki/index.php?title=Qt/Embedded
  * http://thelins.se/learnqt/2009/06/an-embedded-linux-development-setup/
  * http://files.chumby.com/source/
  * http://wiki.chumby.com/index.php/Chumby_Software_Applications,_Scripts_and_Tools
  * http://forum.chumby.com/viewtopic.php?id=1145
  * http://forum.chumby.com/viewtopic.php?id=1469
  * http://forum.chumby.com/viewtopic.php?id=1493
  * http://wiki.chumby.com/index.php/Hacking_Linux_for_chumby
  * http://forum.chumby.com/viewtopic.php?id=3454
  * http://sourceforge.net/apps/mediawiki/chumby-kernel/index.php?title=Kexec_boot
  * http://code.google.com/p/chumbydevboot/
  * http://dangerousprototypes.com/tag/chumby/
  * http://dangerousprototypes.com/2011/03/08/convert-the-chumby-serial-port-into-two-pwm-outputs/
  * http://code.google.com/p/chumbycv/
  * http://wiki.chumby.com/index.php/Main_Page#Chumby_devices
  * http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=i.MX233
  * http://wiki.chumby.com/index.php/Hacking_hardware_for_chumby
  * http://www.linuxtoys.org/chumbot/chumby_robot.tgz
  * http://www.linuxtoys.org/chumbot/chumby_as_robot.pdf
  * http://www.linuxtoys.org/chumbot/hands_on_bb4.pdf
  * http://wiki.chumby.com/index.php/Chumby_Rootdisk_-_RFS1_(analyzed)
  * http://boconnor.is-a-geek.com/pmwiki/index.php?n=Geek.Chumby
  * http://www.bunniestudios.com/blog/?p=1294
  * http://wiki.chumby.com/index.php/Web_Browser
  * http://www.bunniestudios.com/blog/?p=1140
  * http://www.bunniestudios.com/blog/?p=792
  * http://www.bunniestudios.com/blog/?p=262
