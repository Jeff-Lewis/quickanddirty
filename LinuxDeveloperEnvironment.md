

# Introduction #

Usually you have all your developer utilities on your every day machine? Right. Well I would say that you could do something a bit better. Why don't you install VMware Player and then Debian lenny on it? Then you could install for example Scratchbox and all other libraries for your development on the virtual machine.

# Installing Scratchbox on Debian virtual machine #
## Host machine ##
  * Download and Install [www.vmware.com/products/player/ VMware Player]
  * Download [Debian netinst CD](http://cdimage.debian.org/debian-cd/5.0.4/i386/iso-cd/debian-504-i386-netinst.iso) iso-image
  * Install Debian base install without X (Only Standard System selected in Tasksel)
```
Disk size: 20Gb
Network: NAT
Press <enter> on nearly all questions, except <yes> on disk partition and unselect Desktop checkbox on tasksel.
```
![http://quickanddirty.googlecode.com/files/debian-504-i386-netinst.png](http://quickanddirty.googlecode.com/files/debian-504-i386-netinst.png)

  * Download [\_Cygwin/X\_](http://x.cygwin.com/) on host machine
  * Install cygwin and select _xinit_ package.
![http://quickanddirty.googlecode.com/files/cygwin.png](http://quickanddirty.googlecode.com/files/cygwin.png)
  * Run X Server on your host machine
![http://quickanddirty.googlecode.com/files/xcygwin.png](http://quickanddirty.googlecode.com/files/xcygwin.png)

## Client machine ##
  * Login as ROOT
![http://quickanddirty.googlecode.com/files/debian-504-i386-netinst-freshboot.png](http://quickanddirty.googlecode.com/files/debian-504-i386-netinst-freshboot.png)
  * Download and Run [maemo-scratchbox-install\_5.0.sh](http://repository.maemo.org/stable/5.0/maemo-scratchbox-install_5.0.sh) script
```
wget -c http://repository.maemo.org/stable/5.0/maemo-scratchbox-install_5.0.sh
chmod +x maemo-scratchbox-install_5.0.sh
echo "vm.vdso_enabled = 0" >> /etc/sysctl.conf
sysctl -p
./maemo-scratchbox-install_5.0.sh
```
![http://quickanddirty.googlecode.com/files/scratchbox-installed.png](http://quickanddirty.googlecode.com/files/scratchbox-installed.png)

  * Add your default user to the scratchbox:
```
./maemo-scratchbox-install_5.0.sh -u USER 
```
  * Install xterm.
```
apt-get install xterm
```
  * Install Xephyr
```
apt-get install xserver-xephyr
```
  * Logout ROOT
  * Login in as USER.
  * Determine your NAT server address.
```
cat /etc/resolv.conf | grep nameserver
```
  * Set DISPLAY to point your HOST machine IP:
```
export DISPLAY=192.168.x.x:0
```
  * Run xterm
```
xterm
```
![http://quickanddirty.googlecode.com/files/set-display-xterm.png](http://quickanddirty.googlecode.com/files/set-display-xterm.png)
  * At this point you should see xterm popping up on your host machine desktop.
![http://quickanddirty.googlecode.com/files/xterm_win32.png](http://quickanddirty.googlecode.com/files/xterm_win32.png)
  * Login into scratchbox
```
/scratchbox/login
```
  * Install and configure TARGET
```
sb-conf st FREMANTLE_X86 -c cs2007q3-glibc2.5-i486 -d perl:debian-etch:doctools:svn:git -t none
wget -c http://repository.maemo.org/unstable/fremantle/i386/maemo-sdk-rootstrap_5.0beta2_i386.tgz
sb-conf se FREMANTLE_X86
sb-conf rs maemo-sdk-rootstrap_5.0alpha_i386.tgz
sb-conf in -edFL
apt-get update
```
![http://quickanddirty.googlecode.com/files/fremantle-x86.png](http://quickanddirty.googlecode.com/files/fremantle-x86.png)
  * Prepare rootstrap for development
```
fakeroot apt-get install maemo-sdk-debug
```
  * Install closed source Nokia binaries
    * visit [Nokia site](http://tablets-dev.nokia.com/eula/index.php) to get a line for /etc/apt/sources.list
```
nano /etc/apt/sources.list
apt-get update
fakeroot apt-get install nokia-binaries
```
# Launch XServer for maemo #
  * execute on the debian virtual host
![http://quickanddirty.googlecode.com/files/vmware-xephyr-launch.png](http://quickanddirty.googlecode.com/files/vmware-xephyr-launch.png)
  * Set environment flags:
```
export DISPLAY=192.168.x.x:0
```
  * Start Maemo xserver.
```
Xephyr :2 -host-cursor -screen 800x480x16 -dpi 96 -ac &
```
![http://quickanddirty.googlecode.com/files/xephyr.png](http://quickanddirty.googlecode.com/files/xephyr.png)
# Launch sbox #
  * Execute in SB
```
export DISPLAY=:2
af-sb-init.sh start
```
![http://quickanddirty.googlecode.com/files/xephyr-af-sb-init.png](http://quickanddirty.googlecode.com/files/xephyr-af-sb-init.png)
## Done ##
Now you can access sandbox developer environment from your host machine using xterm. This way you do not screw things up. :)
# Finishing touch #
  * Shutdown virtual machine
  * Take a backup of the newly created development environment
  * As if you fail in some point, then you can just start a new image with working environment and other thing is that you can take the whole environment on an USB stick as well. The total size for me is now 1.3Gb.
## start\_xephyr.sh ##
You might want to create a script for the next usage time.
```
export DISPLAY=192.168.207.2:0
Xephyr :2 -host-cursor -screen 800x480x16 -dpi 96 -ac &
```