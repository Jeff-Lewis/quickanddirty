# Introduction #

Ubuntu 10.04 LTS

# xmltv #
## install ##
```
sudo apt-get install xmltv xmltv-utils
```
```
wget http://xmltv.cvs.sourceforge.net/viewvc/xmltv/xmltv/grab/fi/tv_grab_fi
sudo mv tv_grab_fi /usr/bin
```
## configure ##
```
tv_grab_fi --configure
```
## update ##
```
tv_grab_fi > channels.xml
```

# vdr #
## install plugin ##
```
git clone git://projects.vdr-developer.org/vdr-plugin-xmltv2vdr.git
```
configure the plugin Makefile according to your VDR source location. And then compile it.

# automatic update #
```
#!/bin/bash
tv_grab_fi --config-file=/home/scripts/tv_grab_fi.conf --output /home/scripts/channels.xml --days 2
xmltv2vdr.pl -x /home/scripts/channels.xml -c /etc/vdr/channels.conf.xmltv
```
# channels.conf.xmltv #
```
YLE TV1;YLE:562000:I999B8C23D23M64T8G8Y0:T:27500:512:650=fin,651=dut:2321:0:17:8438:0:0:1.telkku.com
YLE TV2;YLE:562000:I999B8C23D23M64T8G8Y0:T:27500:513:660=fin:2321:0:33:8438:0:0:2.telkku.com
YLE FST5;YLE:562000:I999B8C23D23M64T8G8Y0:T:27500:514:670=swe:2321:0:81:8438:0:0:6.telkku.com
YLE Teema;YLE:562000:I999B8C23D23M64T8G8Y0:T:27500:516:690=fin:2321:0:113:8438:0:0:10.telkku.com
YLE Puhe;YLE:562000:I999B8C23D23M64T8G8Y0:T:27500:0:905=fin:0:0:4369:8438:0:0
YLEN KLASSINEN;YLE:562000:I999B8C23D23M64T8G8Y0:T:27500:0:901=fin:0:0:4401:8438:0:0
YLEMONDO;YLE:562000:I999B8C23D23M64T8G8Y0:T:27500:0:903=fin:0:0:4433:8438:0:0
MTV3;MTV Oy:570000:I999B8C23D23M64T8G8Y0:T:27500:305:561=fin:817:0:49:8438:8193:0:3.telkku.com
Nelonen;Sanoma Television Oy:570000:I999B8C23D23M64T8G8Y0:T:27500:512:650=fin:576:0:65:8438:8193:0:4.telkku.com
Sub;SubTV OY:570000:I999B8C23D23M64T8G8Y0:T:27500:353:609=fin:865:0:97:8438:8193:0:5.telkku.com
Jim;Sanoma Television Oy:570000:I999B8C23D23M64T8G8Y0:T:27500:516:690=fin:576:0:177:8438:8193:0:7.telkku.com
Liv;Sanoma Television OY:578000:I999B8C23D23M64T8G8Y0:T:27500:522:720=fin:0:0:129:8438:12289:0:11.telkku.com
4 Pro 2;Sanoma Television Oy:578000:I999B8C23D23M64T8G8Y0:T:27500:417:673=fin:929:0:145:8438:12289:0:8.telkku.com
The Voice/TV Viisi;SBS Finland:578000:I999B8C23D23M64T8G8Y0:T:27500:513:660=fin:0:0:161:8438:12289:0:9.telkku.com
SuomiTV;Family Channel Oy:578000:I999B8C23D23M64T8G8Y0:T:27500:520:620=fin:0:0:529:8438:12289:0:12.telkku.com
Iskelmï¿½/Harju&Pï¿½ntinen;SBS Finland Oy / Etelï¿½-Pohjanmaan Viestintï¿½ Oy:578000:I999B8C23D23M64T8G8Y0:T:27500:512:650=fin:0:0:817:8438:12289:0

```

# channels.xml #
```
<tv source-info-url="http://www.telkku.com/" source-data-url="http://www.telkku.com/" generator-info-name="XMLTV" generator-info-url="http://xmltv.org/">
  <channel id="1.telkku.com">
    <display-name>TV1</display-name>
  </channel>
  <channel id="10.telkku.com">
    <display-name>YLE Teema</display-name>
  </channel>
  <channel id="11.telkku.com">
    <display-name>Liv</display-name>
  </channel>
  <channel id="12.telkku.com">
    <display-name>SuomiTV</display-name>
  </channel>
.
.
.
```