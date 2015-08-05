# Table of Contents #


# Internet Sharing with bridge #
## Introduction ##
This covers Ubuntu 10.04 LTS Linux with basic configuration using dnsmasq and hostapd.

## Install ##
```
 sudo apt-get install dnsmasq hostapd bridge-utils screen --force-yes --yes
```

## Configure ##
### interfaces ###
In this case there is adsl modem with static ip at 172.16.1.2.

/etc/network/interfaces
```
auto lo
iface lo inet loopback

auto eth0
iface eth0 inet static
        address 172.16.1.1
        network 172.16.1.0
        netmask 255.255.0.0
        gateway 172.16.1.2
        nameserver 172.16.1.1 
        nameserver 172.16.1.2
        up route add default gw 172.16.1.2
        down route del default gw 172.16.1.2

auto wlan0
auto br0

iface wlan0 inet manual
        wireless-mode master
        address 192.168.0.1
        netmask 255.255.255.0
        gateway 172.16.1.1
        nameserver 172.16.1.1
        nameserver 172.16.1.2
        nameserver 192.168.0.1

iface br0 inet manual
        bridge_ports eth0 wlan0

```

### DHCP ###
In this case the localhost is named serveri.

/etc/dnsmasq.conf
```
expand-hosts
domain=kotiverkko.lan
dhcp-range=172.16.1.50,172.16.1.150,12h
dhcp-option=option:router,172.16.1.2
dhcp-leasefile=/var/www/dnsmasq.leases.lan
address=/serveri.kotiverkko.lan/172.168.1.1
log-queries
log-dhcp
```

### WLAN ###
If you live in Finland and you have eth0 and wlan0, then only what you need to change is YOUR\_WLAN\_NAME and YOUR\_PASSWORD.

/etc/hostapd/hostapd.conf
```
interface=wlan0
driver=nl80211
bridge=br0

country_code=FI
ieee80211d=1

ssid=YOUR_WLAN_NAME
hw_mode=g
channel=6
wme_enabled=0

macaddr_acl=0
auth_algs=1
wpa=2
wpa_passphrase=YOUR_PASSWORD
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
```

## Start-up Scripts ##
### /usr/local/bin/create-bridge ###
```
#!/bin/bash
service hostapd stop
service dmsmasq stop

ifconfig eth0 down
ifconfig wlan0 down

ifconfig eth0 0.0.0.0 up
ifconfig wlan0 0.0.0.0 up

brctl addbr br0
brctl addif br0 eth0
brctl addif br0 wlan0

ifconfig br0 172.16.1.1 up

route add default gw 172.16.1.2

service hostapd start
service dnsmasq start
```

### /usr/local/bin/start-hotspot ###
Run this in screen session.
```
sudo hostapd -dd /etc/hostapd/hostapd.conf
```

# Alternative: Internet Sharing with iptables #
## Introduction ##
The easiest method is to just use iptables routing.

## Installation ##
```
sudo apt-get install iptables
```

## Internet Sharing Script ##
This should be called in /etc/rc.local for example.

```
#!/bin/bash
sudo iptables -F
sudo iptables -t nat -F
sudo iptables -t mangle -F
sudo iptables -X
sudo iptables -t nat -X
sudo iptables -t mangle -X

sudo ifconfig eth0 172.16.1.1
sudo ifconfig wlan0 192.168.0.1

sudo route del default gw 172.16.1.2
sudo iptables -A FORWARD -o eth0 -i wlan0 -m conntrack --ctstate NEW -j ACCEPT
sudo iptables -A FORWARD -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
sudo iptables -A POSTROUTING -t nat -j MASQUERADE
sudo route add default gw 172.16.1.2 eth0

sudo service dnsmasq restart
```