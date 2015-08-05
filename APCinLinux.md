# Introduction #
## Source code ##
Download source code for apcupsd from http://www.apcupsd.com and extract it.
## Dependencies ##
```
 sudo apt-get install libgd2-xpm-dev libusb-dev
```

# Details #
## Compile apcupsd ##
```
$ ./configure --enable-usb --enable-cgi
Configuration on Wed Feb  9 17:22:10 EET 2011:

  Host:                       x86_64-unknown-linux-gnu -- debian squeeze/sid
  Apcupsd version:            3.14.8 (16 January 2010)
  Source code location:       .
  Install binaries:           /sbin
  Install config files:       /etc/apcupsd
  Install man files:          /usr/share/man
  Nologin file in:            /etc
  PID directory:              /var/run
  LOG dir (events, status)    /var/log
  LOCK dir (for serial port)  /var/lock
  Power Fail dir              /etc/apcupsd
  Compiler:                   g++ 4.4.4-14ubuntu5)
  Compiler flags:              -I/usr/local/include -g -O2 -fno-exceptions -fno-  rtti -Wall
  Linker:                     gcc
  Linker flags:                -L/usr/local/lib64 -L/usr/local/lib
  Host and version:           debian squeeze/sid
  Shutdown Program:           /sbin/shutdown
  Port/Device:                /dev/ttyS0
  Network Info Port (CGI):    3551
  UPSTYPE                     apcsmart
  UPSCABLE                    smart

  drivers (no-* are disabled): apcsmart dumb net linux-usb snmp no-net-snmp pcne  t no-test

  enable-nis:                 yes
  with-nisip:                 0.0.0.0
  enable-cgi:                 yes
  with-cgi-bin:               /etc/apcupsd
  with-libwrap:
  enable-pthreads:            yes
  enable-dist-install:        yes
  enable-gapcmon:             no
  enable-apcagent:            no

$ make
$ sudo make install
```

## Basic Configuring for testing ##
```
$ nano /etc/apcupsd/apcupsd.conf
UPSCABLE usb
UPSTYPE usb
POLLTIME 60
LOCKFILE /var/lock
SCRIPTDIR /etc/apcupsd
PWRFAILDIR /etc/apcupsd
NOLOGINDIR /etc
BATTERYLEVEL 5
MINUTES 3
TIMEOUT 0
ANNOY 300
ANNOYDELAY 60
NOLOGON disable
KILLDELAY 0
NETSERVER on
NISIP 0.0.0.0
NISPORT 3551
EVENTSFILE /var/log/apcupsd.events
EVENTSFILEMAX 10
UPSCLASS standalone
UPSMODE disable
STATTIME 0
STATFILE /var/log/apcupsd.status
LOGSTATS off
DATATIME 0

```
## Test ##
```
$ apcaccess
APC      : 001,035,0888
DATE     : 2011-02-09 17:15:35 +0200
HOSTNAME : wlanlinux
VERSION  : 3.14.8 (16 January 2010) debian
UPSNAME  : wlanlinux
CABLE    : USB Cable
MODEL    : Back-UPS ES 700G
UPSMODE  : Stand Alone
STARTTIME: 2011-02-09 17:15:27 +0200
STATUS   : ONLINE
LINEV    : 236.0 Volts
LOADPCT  :   0.0 Percent Load Capacity
BCHARGE  : 100.0 Percent
TIMELEFT :  43.8 Minutes
MBATTCHG : 5 Percent
MINTIMEL : 3 Minutes
MAXTIME  : 0 Seconds
SENSE    : Medium
LOTRANS  : 180.0 Volts
HITRANS  : 266.0 Volts
ALARMDEL : Always
BATTV    : 13.6 Volts
LASTXFER : No transfers since turnon
NUMXFERS : 0
TONBATT  : 0 seconds
CUMONBATT: 0 seconds
XOFFBATT : N/A
STATFLAG : 0x07000008 Status Flag
MANDATE  : 2010-12-01
SERIALNO : XXX-removed
BATTDATE : 2010-12-01
NOMINV   : 230 Volts
NOMBATTV :  12.0 Volts
FIRMWARE : 871.O2 .I USB FW:O2
APCMODEL : Back-UPS ES 700G
END APC  : 2011-02-09 17:15:39 +0200
```

# Configure for real #
Edit the configuration file and read the comments in there. Make the adjustments what you want.

# screenshots from web interface #
|![http://quickanddirty.googlecode.com/files/apcupsd-multimon.png](http://quickanddirty.googlecode.com/files/apcupsd-multimon.png)|
|:--------------------------------------------------------------------------------------------------------------------------------|
|![http://quickanddirty.googlecode.com/files/apcupsd-upfsstats-.png](http://quickanddirty.googlecode.com/files/apcupsd-upfsstats-.png)|
|![http://quickanddirty.googlecode.com/files/apcupsd-stats.png](http://quickanddirty.googlecode.com/files/apcupsd-stats.png)      |