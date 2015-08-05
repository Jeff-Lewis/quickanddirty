# Steps #
## step 0) Install dvb-apps ##
```
$ apt-get install dvb-apps
```
## step 1) Scan available channels ##
```
$ scan /usr/share/dvb/dvb-t/fi-Espoo > channels.conf
```
## step 2) View channels with VLC ##
```
$ vlc channels.conf
```