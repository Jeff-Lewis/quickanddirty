

# Introduction #

There was several issues with the Ubuntu 9.10.<br />
First things first.<br />

_Update the kernel!_
```
sudo apt-get install linux
```

And the kernel headers as well:
```
sudo apt-get install linux-headers-[your kernel version]
```

## Disable PIN query ##
Remember to disable PIN query for the SIM card which you are using. This will ease the pain as well.
  * Note: If you have a fixed data plan and you have blocked all phone calls and sms, etc. then there is no real risk from this one. At least this is my opinion on this matter. But still do this at your own risk.

## Remember ~60s boot-up time ##
The modem will boot for about 60 seconds. As it will first enable internal cd-rom emulation and the micro-sd drive for the operating system. After those ones it will enable the modem functionality. So it takes time as the OS might scan the disk drives as well, etc.
  * this could be improved by disabling usb-storage for the usb-modem by vendor and device id with udev?

# How I did it #

It really seems that for a computer which has E160E as primary network device and always connected the NetworkManager is not the optimal solution at all.
## install the applications ##
  * Install wvdial and supervisor
```
sudo apt-get install wvdial python-setuptools
sudo easy_install supervisor
```
## wvdial ##
  * Configure wvdial (example for [Saunalahti](http://www.saunalahti.fi)):
```
[Dialer Defaults]
Modem = /dev/ttyUSB0
Baud = 921600
Init1 = AT+CGDCONT=1,"IP","internet.saunalahti"
Phone = *99***1#
Carrier Check = off
Auto DNS = off
Stupid Mode = 1
Username = " "
Password = " "
```
The _Carrier Check = off_ will fix the _NO CARRIER_ issue with the usb modem.<br />
The _Auto DNS = off_ will block automatic /etc/resolv.conf overwriting.
## pppd ##
Comment out usepeerdns (/etc/ppp/peers/wvdial) for disabling dns server information query from peer.

## supervisord ##
  * Create configuration template for _supervisord_:
```
echo_supervisord_conf > supervisord.conf
sudo mv supervisord.conf /etc/supervisord.conf
```
  * Configure _supervisord_ (/etc/supervisord.conf):
```
[program:saunalahti]
command=/usr/bin/wvdial
autostart=true
autorestart=true
process_name=wvdial
startretries=10
```
## make them run @ boot time and on request ##
  * Make _supervisord_ run on the boot time, add a line to /etc/rc.local:
```
/usr/local/bin/supervisord
```
  * Get vendor and device id:
```
lsmod | grep Huawei
```
  * Create a rules for the udev (/etc/udev/rules.d/99-wvdial.rules):
```
ACTION=="add", ATTRS{vendor}=="0x12d1", ATTRS{device}=="0x1003", KERNEL=="ttyUSB0", RUN="supervisorctl start saunalahti:wvdial"
ACTION=="remove", ATTRS{vendor}=="0x12d1", ATTRS{device}=="0x1003", KERNEL=="ttyUSB0", RUN="supervisorctl stop saunalahti:wvdial"
```
# post installation #
## enable proxy server for increased security ##
As you browse web now with your mobile, you are showing your mobile phone number as well. So it would make sense to enable proxy servers.<br /><br />
Edit /etc/bash.bashrc and add following lines:
```
export http_proxy="http://varasto.saunalahti.fi:80"
export ftp_proxy="http://varasto.saunalahti.fi:80"
```

## enable local dns cache and OpenDNS ##
It seems that the dns queries will take a lot of time over the 3G connection, so the local dns cache actually would make a huge difference.
```
sudo apt-get install dnsmasq
```
Configure the dnsmasq (/etc/dnsmasq.conf) by adding line:
```
listen-address=127.0.0.1
```
Reboot the service:
```
sudo /etc/init.d/dnsmasq restart
```
Take dns service into use, edit (/etc/resolv.conf):
```
nameserver 127.0.0.1
nameserver 208.67.222.222
nameserver 208.67.220.220
```
## Cache Content and Block Unwanted Content ##
The fact is that nowadays nearly 50% of all the traffic which is generated is flash-ads or similar not needed information. With 3G modem connection this sucks a bit too much. I know that this approach is a bit heavy but still it works and it is easy to do.
### Install Squid and Dansguardian ###
```
sudo apt-get install squid dansguardian apache2 iptables
```

### Configure Squid ###
Edit default config @ /etc/squid/squid.conf:
```
acl Safe_ports port 5222        # gtalk
acl SSL_ports port 5222         # gtalk
http_port 3128 transparent
connect_timeout 30 seconds
forward_timeout 1 minute
request_timeout 2 minutes
forwarded_for off
cache_peer varasto.saunalahti.fi parent 80 7 no-query default
prefer_direct off
```

### Configure DansGuardian ###
Edit default config @ /etc/dansguardian/dansguardian.conf:
```
#UNCONFIGURED
reportinglevel = 2
loglevel = 1
filterip = 127.0.0.1
filterport = 8080
proxyip = 127.0.0.1
proxyport = 3128
accessdeniedaddress = 'http://localhost/cgi-bin/dansguardian.pl'
weightedphrasemode = 0
phrasefiltermode = 1
forwardedfor = off
usexforwardedfor = off
logadblocks = on
```
#### block hosts ####
Look into folder /etc/dansguardian/lists.
Modify /etc/dansguardian/lists/bannedsitelist

### Configure iptables ###
Create and edit file /etc/init.d/3gfilteringproxy
```
iptables -t nat -A OUTPUT -p tcp -m owner ! --uid-owner proxy --dport 80 -j REDIRECT --to-port 8080
```
Add rights and enable startup:
```
$ sudo chmod a+x /etc/init.d/3gfilteringproxy
$ sudo update-rd.d 3gfilteringproxy enable
```

### Enable proxy settings ###
/etc/bash.bashrc
```
export http_proxy="127.0.0.1:8080"
export ftp_proxy="127.0.0.1:8080"
```

### Customize message for the content blocks ###
Edit /usr/lib/cgi-bin/dansguardian.pl

# Tests #
## download slashdot.org ##
```
$ time wget http://www.slashdot.org
real	0m6.861s
user	0m0.004s
sys	0m0.008s
```
## dig slashdot.org ##
```
$ dig engadget.com
;; Query time: 2783 msec
$ dig engadget.com
;; Query time: 8 msec
```
## connection startup test ##
```
$ cat test-connection.sh 
#!/bin/sh
sudo supervisorctl start saunalahti:wvdial
wget --quiet --retry-connrefused -t0 http://www.slashdot.org
```
```
$ chmod +x test-connection.sh
$ sudo supervisorctl stop saunalahti:wvdial
$ time ./test-connection.sh
saunalahti:wvdial: started

real	0m9.396s
user	0m0.164s
sys	0m0.064s
```