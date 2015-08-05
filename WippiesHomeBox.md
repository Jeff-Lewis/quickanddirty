This wiki page is meant for me (Juhapekka Piiroinen) as online notepad for the research project.

# Table of Contents #


# ~~PENDING FOR PERMISSIONS from CERT-FI and Elisa~~ #
As there are some exploits for this device, but which are not fixed by the manufacturer. I have contacted CERT-FI and they have contacted Elisa. This process started 3/2010 and is still going on. I will release a full report of the findings on December.

## First email was sent 26.1.2010 ##
Where i reported issues to CERT-FI. They reported to Elisa
## First contact from Elisa 26.11.2010 ##
Where it seems that they do not see any exploit here. Waiting for the last written answer.
## Second contact from Elisa 1.12.2010 ##
The _exploit_ has been fixed in their latest firmware (A50803-Sauna35-24524). So it should be fine to release the stuff. However they noted that some one had noticed same thing in 8/2009. This raised a question that why they did not fix it asap, if they knew it :D

...and they did not reply to the question why they store the password in plaintext in the device, it would be more clever to store the password as hash.. oh well.. I will go next thru the material and release all of it. Should take few weekends..

## The data export ##
**This info has been reported to CERT-FI in 12/2010 with ticket #347299**

Exporting data
```
GET /cgi-bin/export.cgi?sExportMode=text HTTP/1.1
Host: 192.168.0.1
Referer: http://192.168.0.1/setup.htm
```


Writing settings
```
POST /cgi-bin/generic.cgi HTTP/1.1
Host: 192.168.0.1
Referer: http://192.168.0.1/setup.htm
Content-Type: application/x-www-form-urlencoded
Content-Length: 40

token=GxsWWC&write=Services_SSH_Enable:1
```


Begin of a partial dump
```
WebCam_1_UploadImage_Server='wsftp.wippies.com'
WebCam_1_UploadImage_Port=2222
WLANInterface_2_Config_SSID='WippiesVOIP'
WLANInterface_2_Config_WPADefaultKey='wippiesvoip'
WLANInterface_2_Config_WPAEncryption='TKIP'
WebConfigurator_SuLogin='bewan'
WebConfigurator_SuPassword='8Ve63Cl9hS4g.'
Services_TR069_ACSUrl='https://acs.wiax.net:8043/acs'
Services_UnixAdmin_Username='admin'
Services_UnixAdmin_Password='$1$$yDJWJcZIubC6Kuklfp5n0.'
Services_UnixAdmin_UserID=600
Services_UnixAdmin_GroupID=600
Services_UnixAdmin_Shell='/bin/cli'
Services_Telnet_Enable=0
Services_Ssh_Enable=0
```

# OpenWrt runs on this device #
See page 2+ @ https://forum.openwrt.org/viewtopic.php?id=15934

# Details #
## JTAG ##
Propably the JTAG connector is the one under the UART on the PCB. Correct me if i am wrong.
http://www.t-hack.com/wiki/index.php/EJTAG

## Hardware ##
http://www.arcadyan.com/english/products/product_detail.asp?PROD_L1ID=00000003&PROD_ID=00000024
## Memory ##
```
0x00000000-0x01000000 : "Flash"
0x00000000-0x00020000 : "Loader"
0x00020000-0x00040000 : "Config"
0x00040000-0x00820000 : "Firmware"
0x00820000-0x01000000 : "OldFirmware"
```

## Misc ##
The backfire/ifxmips version of the openwrt should have a support for ARV4519 based Arcadian boards.
  * http://backfire.openwrt.org/10.03-beta/ifxmips/
  * http://www.linux-mips.org/wiki/Danube
  * http://www.mail-archive.com/openwrt-devel@lists.openwrt.org/msg01503.html
  * https://forum.openwrt.org/viewtopic.php?id=15934
  * http://backfire.openwrt.org/10.03-rc3/README
## Bootloader ##
_BRN Bootloader_ is installed, but _u-boot_ is required for better usage.. and there is no asking for _space_ or anything so that we could access the _BRN Bootloader_ menu..
  * http://backfire.openwrt.org/10.03-beta/ifxmips/uboot-ifxmips/
### Pins ###
#### J16 ####
```
ROM VER: 1.0.3
CFG 05
Read EEPROMX
 X
SFLASH
X
SFLAS5)Â5ReÅ*jªÕH¨HHÕª
                      U*'HL.3
CFG 05
Read EEPROMX
 X
```

#### J21 ####

no header information (ROM VER.. etc). just booting normally.

```
Booting from partition 0 in flash.

Loading: Linux Kernel Image

Load address = 80000000
Uncompressing Linux.....................

kernel corrupted!


 -- System halted]
```

#### J16+J21 ####
```
ROM VER: 1.0.3
CFG 04
Read EEPROMX
 X
UART
```

### Other ###
There should be a hidden bootloader inside the main cpu as well. according to the discussion in openwrt devel mailinglist there should be few resistors on the board which needs to be changed to enable UART bootloader, or something.

## UART - The pins on the board ##
```
Now you have to identify the bootstrap pins. Maybe John knows more about 
it?

Your mode is 1 (BootSel0 1, BootSel1 0, BootSel2 0) .
We would need the configuration 4 for UART mode (BootSel0 0, BootSel1 0, 
BootSel2 1) .
The UART boot log should look like ...

>>>
ROM VER: 1.0.3
CFG 04
Read EEPROMX
 X
UART    
<<<

In case that's not possible to identify the correct bootstrap pins you would 
have to live with the original bootloader :-(

```
  * http://www.mail-archive.com/openwrt-devel@lists.openwrt.org/msg03920.html

## Enabling MIPS JTAG ##
There is also an existing place holder for the JTAG. - not tried yet.. we should be able to access the flash using that one and also modify the filesystem, etc.
### Info ###
```
First read the original configuration information from flash:

cable parallel 0x378 WIGGLER
detect
include admtek/adm5120/adm5120
detectflash 0xd000000
readmem 0x0d020000 0x20000 config.bin

Mount config.bin (it's in ext2 format) and find following line from
router.conf (hash changed in this example):

UserTable_1_Unix_Password='$1$$ASDFasdfASDfasdf'

and replace it with a password hash of your own choice.

check the size of router.conf and change router.magic accordingly. 

unmount and program flash:

cable parallel 0x378 WIGGLER
detect
include admtek/adm5120/adm5120
detectflash 0xd000000
flashmem 0x0d020000 config.bin

reboot the router, ssh root@192.168.0.1, enjoy.
```
  * http://koti.kapsi.fi/jvaarani/homebox/jtag_flash_procedure.txt


## Enabling Multicast mode on boot loader ##
Press _Wifi_ button when switching power On.
  * No idea what this mode does, Stays in multicast mode for few seconds.
    * udpcast?
    * tftp?
    * wtf?
```
  Capabilities    : 80000001

Entering multicast mode
Leaving multicast mode

Found valid bootable partition 0:
```


## Enabling Serial port ##
There is an existing connector inside the box.
```
Socket J3:
VCC  1 2 ?
RX   3 4 ?
TX   5 6 ?
?    7 8 ?
GND  9 10 ?
```
I used UB232R for USB-UART connection. with following settings:
```
Speed: 115200
Data bits: 8
Stop bits: 1
Parity: None
Flow control: None
```

## UART output on boot ##
```
ROM VER: 1.0.3
CFG 01
Read ˜
ROM VER: 1.0.3
CFG 01
Read EEPROMX
 X





   _                              
  | |__   _____      ____ _ _ __  
  | '_ \ / _ \ \ /\ / / _` | '_ \ 
  | |_) |  __/\ V  V / (_| | | | |
  |_.__/ \___| \_/\_/ \__,_|_| |_|

Portions Copyright (c) 2005-2007 bewan systems
   www.bewan.com


Parameters:
  Product         : A50803
  Product family  : A50800
  Flash size      : 1000000
  DRAM size       : 2000000
  Ethernet        : MII
  LAN MAC address : - deleted on paste -
  WAN MAC address : - deleted on paste -
  Dual bank boot  : yes
  Reset           : no
  Pairing         : no
  Serial number   : - deleted on paste -
  WEP key         : - deleted on paste -
  Loader version  : - deleted on paste -
  Capabilities    : - deleted on paste -


Found valid bootable partition 0:
  Copyright (c) 2006-2008 BeWAN Systems
  Arcadyan ARV4510PW-A-LF-L3 - Saunalahti
  A50803
  2009-07-03-15:30:18
  A50803-Sauna35-24524.bin

Found valid bootable partition 1:
  Copyright (c) 2006-2008 BeWAN Systems
  Arcadyan ARV4510PW-A-LF-L3 - Saunalahti
  A50803
  2008-10-14-09:04:02
  A50803-Sauna29-16953.bin

Booting from partition 0 in flash.

Loading: Linux Kernel Image

Load address = 80000000
Uncompressing Linux.....................
done, booting the kernel.

start addr = 802F1000
memsize=31
TODO: chip version
Linux version 2.6.16bewan (build@bewan.com) (gcc version 3.3.4) #1
Reserving memory for CP1 @0xa1f00000
memsize=31
CPU revision is: 00019641
PCI: Probing PCI hardware on host bus 0.
Board with an external oscillator
Determined physical RAM map:
 memory: 01f00000 @ 00000000 (usable)
User-defined physical RAM map:
 memory: 01f00000 @ 00000000 (usable)
Built 1 zonelists
Kernel command line: nofpu console=ttyS0,115200n1 bewan_boot=flash0 bewan_fs_addr=0x11c000 bewan_fs_size=0x6e7000 mem=31M 
Primary instruction cache 16kB, physically tagged, 4-way, linesize 32 bytes.
Primary data cache 16kB, 4-way, linesize 32 bytes.
Synthesized TLB refill handler (20 instructions).
Synthesized TLB load handler fastpath (32 instructions).
Synthesized TLB store handler fastpath (32 instructions).
Synthesized TLB modify handler fastpath (31 instructions).
Cache parity protection disabled
PID hash table entries: 128 (order: 7, 2048 bytes)
mips_hpt_frequency:166666667
r4k_offset: 00196e6a(1666666)
Using 166.667 MHz high precision timer.
Dentry cache hash table entries: 4096 (order: 2, 16384 bytes)
Inode-cache hash table entries: 2048 (order: 1, 8192 bytes)
Memory: 27628k/31744k available (2517k kernel code, 4116k reserved, 492k data, 160k init, 0k highmem)
Mount-cache hash table entries: 512
Checking for 'wait' instruction...  available.
NET: Registered protocol family 16
TC classifier action (bugs to netdev@vger.kernel.org cc hadi@cyberus.ca)
DANUBE MIPS24KEc MPS mailbox driver, Version 1.1.0
(c) Copyright 2006, Infineon Technologies AG
IFX_MPS: using proc fs
squashfs: version 3.0 (2006/03/15) Phillip Lougher
Squashfs 2.2 with LZMA support
devfs: 2004-01-31 Richard Gooch (rgooch@atnf.csiro.au)
devfs: boot_options: 0x1
Initializing Cryptographic API
io scheduler noop registered (default)
Danube MEI version:1.00.09
Danube MEI MIB version:0.90.04
Danube Port Settings

Danube Port Initialization
cgu: misc_register on minor = 63
gptu: totally 6 16-bit timers/counters
gptu: misc_register on minor 62
gptu: succeeded to request irq 118
gptu: succeeded to request irq 119
gptu: succeeded to request irq 120
gptu: succeeded to request irq 121
gptu: succeeded to request irq 122
gptu: succeeded to request irq 123
ttyS0 at MMIO 0xbe100c00 (irq = 9) is a DANUBEASC
ttyS1 at MMIO 0xbe100400 (irq = 2) is a DANUBEASC
RAMDISK driver initialized: 16 RAM disks of 8192K size 1024 blocksize
loop: loaded (max 8 devices)
PPP generic driver version 2.4.2
NET: Registered protocol family 24
danube ETOP driver loaded!
ppe: ATM init succeeded (firmware version 1.1.0.2.1.13
Danube IAD flash device: 0x1000000 at 0xb0000000
Danube IAD FLASH: Found 1 x16 devices at 0x0 in 16-bit bank
 Intel/Sharp Extended Query Table at 0x0031
cfi_cmdset_0001: Erase suspend on write enabled
Creating 5 MTD partitions on "Danube IAD FLASH":
0x00000000-0x01000000 : "Flash"
0x00000000-0x00020000 : "Loader"
0x00020000-0x00040000 : "Config"
0x00040000-0x00820000 : "Firmware"
0x00820000-0x01000000 : "OldFirmware"
bootpart=1
Creating 1 MTD partitions on "Danube IAD FLASH":
0x0011c000-0x00803000 : "ART"
rootdev = 31,5
dwc_otg: version 2.40a 10-APR-2006
usb0: Ethernet Gadget, version: Equinox 2004
usb0: using dwc_otg_pcd, OUT ep2 IN ep1 STATUS ep3
usb0: MAC 0e:ac:1d:0b:9b:e1
usb0: HOST MAC a2:d8:58:a1:c5:ea
usb0: RNDIS ready
LED and Buttons driver: v2.6.0
GACT probability on
Mirror/redirect action on
netem: version 1.2
u32 classifier
    Perfomance counters on
    input device check on 
    Actions configured 
Netfilter messages via NETLINK v0.30.
NET: Registered protocol family 2
IP route cache hash table entries: 256 (order: -2, 1024 bytes)
TCP established hash table entries: 1024 (order: 0, 4096 bytes)
TCP bind hash table entries: 1024 (order: 0, 4096 bytes)
TCP: Hash tables configured (established 1024 bind 1024)
TCP reno registered
ip_conntrack version 2.4 (248 buckets, 1984 max) - 232 bytes per conntrack
meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.
DS max rate = 0 kbps
US max rate = 0 kbps
DS payload rate = 0 kbps
US payload rate = 0 kbps
Local CRC = 0
Remote CRC = 0
ip_tables: (C) 2000-2006 Netfilter Core Team
arp_tables: (C) 2002 David S. Miller
TCP bic registered
Initializing IPsec netlink socket
NET: Registered protocol family 1
NET: Registered protocol family 17
NET: Registered protocol family 15
Ebtables v2.0 registered
802.1Q VLAN Support v1.8 Ben Greear <greearb@candelatech.com>
All bugs added by David S. Miller <davem@redhat.com>
Ethernet Multiplexer Support v1.0 Christophe Piel (c) 2006 BeWAN systems
VFS: Mounted root (squashfs filesystem) readonly.
Mounted devfs on /dev
Freeing unused kernel memorymeiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.init started:  BusyBox v1.00 multi-call binary 
Starting pid 130, console /dev/tts/0: '/etc/rc' 
Algorithmics/MIPS FPU Emulator v1.5
Software Watchdog Timer: 0.05, timer margin: 120 sec.
Mon Jan  1 00:00:00 UTC 2007
meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail. _                              
| |__   _____      ____ _ _ __  
| '_ \ / _ \ \ /\ / / _` | '_ \ 
| |_) |  __/\ V  V / (_| | | | |
|_.__/ \___| \_/\_/ \__,_|_| |_|
IFX TAPI, version 3.5.2.5, (c) 2007 Infineon Technologies

<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.IFX VMMC device driver, version 1.1.6.5, (c) 2007 Infineon Technologies AG

<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<6>usbcore: registered new driver usbfs
usbcore: registered new driver hub
meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<5>SCSI subsystem initialized
Initializing USB Mass Storage driver...
usbcore: registered new driver usb-storage
USB Mass Storage support registered.
meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.PCI: Enabling device 0000:00:0f.2 (0000 -> 0002)
plat_dev_init(803ed400)
ehci_hcd 0000:00:0f.2: EHCI Host Controller
ehci_hcd 0000:00:0f.2: new USB bus registered, assigned bus number 1
ehci_hcd 0000:00:0f.2: irq 26, io mem 0x18010000
ehci_hcd 0000:00:0f.2: USB 2.0 started, EHCI 1.00, driver 10 Dec 2004
usb usb1: configuration #1 chosen from 1 choice
hub 1-0:1.0: USB hub found
hub 1-0:1.0: 4 ports detected
USB Universal Host Controller Interface driver v2.3
meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.PCI: Enabling device 0000:00:0f.0 (0000 -> 0001)
plat_dev_init(803edc00)
uhci_hcd 0000:00:0f.0: UHCI Host Controller
uhci_hcd 0000:00:0f.0: new USB bus registered, assigned bus number 2
uhci_hcd 0000:00:0f.0: irq 26, io base 0x1ae00000
usb usb2: configuration #1 chosen from 1 choice
hub 2-0:1.0: USB hub found
hub 2-0:1.0: 2 ports detected
PCI: Enabling device 0000:00:0f.1 (0000 -> 0001)
plat_dev_init(803ed800)
uhci_hcd 0000:00:0f.1: UHCI Host Controller
uhci_hcd 0000:00:0f.1: new USB bus registered, assigned bus number 3
uhci_hcd 0000:00:0f.1: irq 26, io base 0x1ae00020
usb usb3: configuration #1 chosen from 1 choice
hub 3-0:1.0: USB hub found
hub 3-0:1.0: 2 ports detected
meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<6>Linux video capture interface: v1.00
pwc: Philips webcam module version 10.0.12-rc1 loaded.
pwc: Supports Philips PCA645/646, PCVC675/680/690, PCVC720[40]/730/740/750 & PCVC830/840.
pwc: Also supports the Askey VC010, various Logitech Quickcams, Samsung MPC-C10 and MPC-C30,
pwc: the Creative WebCam 5 & Pro Ex, SOTEC Afina Eye and Visionite VCS-UC300 and VCS-UM100.
usbcore: registered new driver Philips webcam
meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<6>usbcore: registered new driver gspca
../user/gspca/gspca_core.c: gspca driver 01.00.20 registered
meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.build router.conf from /etc/flash/router.diff
<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail.<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail./etc/init.d/syslog start
/etc/eom.d/update-config
<3>meiMailboxWrite: 

 MEI_TO_ARC_MSGAV not cleared by ARC<3>meiCMV: 

 MailboxWrite Fail./etc/init.d/dsl start
modprobe: module ctlmeth not found.
modprobe: failed to load module ctlmeth
/etc/init.d/interface start LANEthernetInterface 1
/etc/init.d/switch start 1
/etc/init.d/phy stop 1 1
using the specified MII index 19.
power down...
/etc/init.d/phy stop 1 2
using the specified MII index 18.
power down...
/etc/init.d/phy stop 1 3
using the specified MII index 17.
power down...
/etc/init.d/phy stop 1 4
using the specified MII index 16.
power down...
<7>eth0.1: add 01:00:5e:00:00:01 mcast address to master interface
/etc/init.d/switchvlan start 1
vlanTAGctl : disabling all hardware VLANs
vlanTAGctl : creating vlan VID=0x1 with UNTAGGED=0xF TAGGED=0x30 INDEX=0
vlanTAGctl : creating vlan VID=0x2 with UNTAGGED=0x0 TAGGED=0x30 INDEX=1
modprobe: module ctlmusb not found.
modprobe: failed to load module ctlmusb
/etc/init.d/interface start LANUSBInterface 1
wireless config : atheros
/etc/init.d/wifi.d/wifi start 1
ath_hal: module license 'Proprietary' taints kernel.
ath_hal: 0.9.14.25 (AR5212, AR5416, RF5111, RF5112, RF2413, RF5413, DEBUG)
ath_dfs: Version 2.0.0
Copyright (c) 2005-2006 Atheros Communications, Inc. All Rights Reserved
wlan: 0.8.4.2 (Atheros/multi-bss)
ath_rate_atheros: Version 2.0.1
Copyright (c) 2001-2004 Atheros Communications, Inc, All Rights Reserved
ath_pci: 0.9.4.5 (Atheros/multi-bss)
ath_pci: CR-LSDK-1.3.1.71
PCI: Enabling device 0000:00:0c.0 (0000 -> 0002)
plat_dev_init(8105a000)
Chan 2412: MaxPow = 88 MinPow = 0
Chan 2412: MaxPow = 82 MinPow = 0
Chan 2417: MaxPow = 88 MinPow = 0
Chan 2417: MaxPow = 82 MinPow = 0
Chan 2422: MaxPow = 88 MinPow = 0
Chan 2422: MaxPow = 82 MinPow = 0
Chan 2427: MaxPow = 88 MinPow = 0
Chan 2427: MaxPow = 82 MinPow = 0
Chan 2432: MaxPow = 88 MinPow = 0
Chan 2432: MaxPow = 82 MinPow = 0
Chan 2437: MaxPow = 88 MinPow = 0
Chan 2437: MaxPow = 82 MinPow = 0
Chan 2442: MaxPow = 88 MinPow = 0
Chan 2442: MaxPow = 83 MinPow = 0
Chan 2447: MaxPow = 88 MinPow = 0
Chan 2447: MaxPow = 83 MinPow = 0
Chan 2452: MaxPow = 88 MinPow = 0
Chan 2452: MaxPow = 83 MinPow = 0
Chan 2457: MaxPow = 88 MinPow = 0
Chan 2457: MaxPow = 83 MinPow = 0
Chan 2462: MaxPow = 88 MinPow = 0
Chan 2462: MaxPow = 83 MinPow = 0
Chan 2467: MaxPow = 88 MinPow = 0
Chan 2467: MaxPow = 83 MinPow = 0
Chan 2472: MaxPow = 88 MinPow = 0
Chan 2472: MaxPow = 84 MinPow = 0
Chan 2412: MaxPow = 33 MinPow = 0
Chan 2412: MaxPow = 33 MinPow = 0
Chan 2417: MaxPow = 33 MinPow = 0
Chan 2417: MaxPow = 33 MinPow = 0
Chan 2422: MaxPow = 33 MinPow = 0
Chan 2422: MaxPow = 33 MinPow = 0
Chan 2427: MaxPow = 33 MinPow = 0
Chan 2427: MaxPow = 33 MinPow = 0
Chan 2432: MaxPow = 33 MinPow = 0
Chan 2432: MaxPow = 33 MinPow = 0
Chan 2437: MaxPow = 33 MinPow = 0
Chan 2437: MaxPow = 33 MinPow = 0
Chan 2442: MaxPow = 33 MinPow = 0
Chan 2442: MaxPow = 33 MinPow = 0
Chan 2447: MaxPow = 33 MinPow = 0
Chan 2447: MaxPow = 33 MinPow = 0
Chan 2452: MaxPow = 33 MinPow = 0
Chan 2452: MaxPow = 33 MinPow = 0
Chan 2457: MaxPow = 33 MinPow = 0
Chan 2457: MaxPow = 33 MinPow = 0
Chan 2462: MaxPow = 33 MinPow = 0
Chan 2462: MaxPow = 33 MinPow = 0
Chan 2467: MaxPow = 33 MinPow = 0
Chan 2467: MaxPow = 33 MinPow = 0
Chan 2472: MaxPow = 33 MinPow = 0
Chan 2472: MaxPow = 33 MinPow = 0
Chan  Freq  RegPwr  HT   CTL CTL_U CTL_L DFS
   1  2412g     20        0    0    0     N
   1  2412b     20        0    0    0     N
   2  2417g     20        0    0    0     N
   2  2417b     20        0    0    0     N
   3  2422g     20        0    0    0     N
   3  2422b     20        0    0    0     N
   4  2427g     20        0    0    0     N
   4  2427b     20        0    0    0     N
   5  2432g     20        0    0    0     N
   5  2432b     20        0    0    0     N
   6  2437g     20        0    0    0     N
   6  2437b     20        0    0    0     N
   7  2442g     20        0    0    0     N
   7  2442b     20        0    0    0     N
   8  2447g     20        0    0    0     N
   8  2447b     20        0    0    0     N
   9  2452g     20        0    0    0     N
   9  2452b     20        0    0    0     N
  10  2457g     20        0    0    0     N
  10  2457b     20        0    0    0     N
  11  2462g     20        0    0    0     N
  11  2462b     20        0    0    0     N
  12  2467g     20        0    0    0     N
  12  2467b     20        0    0    0     N
  13  2472g     20        0    0    0     N
  13  2472b     20        0    0    0     N
wifi0: 11b rates: 1Mbps 2Mbps 5.5Mbps 11Mbps
wifi0: 11g rates: 1Mbps 2Mbps 5.5Mbps 11Mbps 6Mbps 9Mbps 12Mbps 18Mbps 24Mbps 36Mbps 48Mbps 54Mbps
wifi0: mac 7.8 phy 4.5 radio 5.6
wifi0: Use hw queue 1 for WME_AC_BE traffic
wifi0: Use hw queue 0 for WME_AC_BK traffic
wifi0: Use hw queue 2 for WME_AC_VI traffic
wifi0: Use hw queue 3 for WME_AC_VO traffic
wifi0: Use hw queue 8 for CAB traffic
wifi0: Use hw queue 9 for beacons
wifi0: Use hw queue 7 for UAPSD
wifi0: Atheros 5212: mem=0x18000000, irq=95 hw_base=0xb8000000
wlan: mac acl policy registered
/etc/init.d/wifi.d/easyp nothing
/etc/init.d/wifi.d/wifi start 2
/etc/init.d/wifi.d/easyp nothing
/etc/init.d/wifi.d/wifi start 3
/etc/init.d/wifi.d/easyp nothing
ath_newstate: Resetting VAP dfswait_run
modprobe: module ctlmatm not found.
modprobe: failed to load module ctlmatm
/etc/init.d/interface start ATMEthernetInterface 1
/etc/init.d/atm start 1
ath_chan_set: Changing to channel 2417, Flags c0, PF 0
/bin/atmcfg atm1 -grpreq 1 1
/bin/atmcfg atm1 -flowset 15 0 0 3 0 0 0 1
/bin/atmcfg atm1 -vccopen 8 35 15 llc brip
ath_chan_set: Changing to channel 2422, Flags c0, PF 0
/etc/init.d/interface nothing ATMEthernetInterface 2
/etc/init.d/interface nothing ATMEthernetInterface 3
/etc/init.d/interface nothing ATMEthernetInterface 4
/etc/init.d/interface nothing ATMEthernetInterface 5
/etc/init.d/autodslam start auto-stop
/etc/init.d/lan start 1
ath_chan_set: Changing to channel 2427, Flags c0, PF 0
/etc/init.d/lanif start 1 all
/etc/init.d/lanintf start lan1 eth0.1
ath_chan_set: Changing to channel 2432, Flags c0, PF 0
eth0.1: dev_set_promiscuity(master, 1)
device eth0 entered promiscuous mode
device eth0.1 entered promiscuous mode
/etc/init.d/lanintf start lan1 usb0
device usb0 entered promiscuous mode
/etc/init.d/lanintf start lan1 ath0
ath_newstate: Resetting VAP dfswait_run
device ath0 entered promiscuous mode
ath_chan_set: Changing to channel 2437, Flags c0, PF 0
/etc/init.d/shaping nothingath_chan_set: Changing to channel 2442, Flags c0, PF 0

/etc/init.d/lanip start 1
/etc/config.default/ip-up-dhcp lan1 192.168.0.1
lan1: port 3(ath0) entering listening state
lan1: port 1(eth0.1) entering listening state
ath_chan_set: Changing to channel 2447, Flags c0, PF 0
/etc/init.d/host start
/etc/init.d/igmp start
ath_chan_set: Changing to channel 2452, Flags c0, PF 0
/etc/init.d/inittab
/etc/init.d/ipsec restart all
ath_chan_set: Changing to channel 2457, Flags c0, PF 0
/etc/init.d/ipsec start 1
/etc/init.d/landhcp start 1
/etc/init.d/wifi.d/lanacl start 1
ath_chan_set: Changing to channel 2462, Flags c0, PF 0
/etc/init.d/passthrough start 1
/etc/init.d/lan start 2
ath_chan_set: Changing to channel 2467, Flags c0, PF 0
/etc/init.d/racoon stop
/etc/init.d/lanif start 2 all
ath_chan_set: Changing to channel 2472, Flags c0, PF 0
/etc/init.d/lanintf start lan2 ath1
ath_newstate: Resetting VAP dfswait_run
device ath1 entered promiscuous mode
ath_newstate: Resetting VAP dfswait_run
ath_chan_set: Changing to channel 2437, Flags c0, PF 0
ath_newstate: Resetting VAP dfswait_run
ath_newstate: Resetting VAP dfswait_run
/etc/init.d/shaping nothing
/etc/init.d/lanip start 2
/etc/config.default/ip-up-dhcp lan2 192.168.1.1
lan2: port 1(ath1) entering learning state
/etc/init.d/host start
/etc/init.d/igmp start
/etc/init.d/inittab
/etc/init.d/ipsec restart all
/etc/init.d/ipsec start 1
/etc/init.d/landhcp start 2
/etc/init.d/wifi.d/lanacl start 2
/etc/init.d/passthrough nothing 2
/etc/init.d/lan start 3
/etc/init.d/racoon stop
/etc/init.d/lanif start 3 all
/etc/init.d/lanintf start lan3 ath2
device ath2 entered promiscuous mode
/etc/init.d/shaping nothing
/etc/init.d/lanip start 3
/etc/config.default/ip-up-dhcp lan3 10.10.234.193
lan3: port 1(ath2) entering learning state
/etc/init.d/host start
/etc/init.d/igmp start
/etc/init.d/inittab
/etc/init.d/ipsec restart all
/etc/init.d/ipsec start 1
lan1: port 3(ath0) entering learning state
lan1: port 1(eth0.1) entering learning state
/etc/init.d/landhcp start 3
/etc/init.d/wifi.d/lanacl start 3
/etc/init.d/racoon stop
/etc/init.d/passthrough nothing 3
/etc/init.d/lan nothing 4
/etc/init.d/users start
/etc/init.d/unix start
/etc/init.d/unixusers start 1
/etc/init.d/unixusers start 2
/etc/init.d/samba start
/etc/init.d/pureftpd start
/etc/init.d/webusers start
rm: cannot remove `/var/etc/config/.naspasswd': No such file or directory
rm: cannot remove `/var/etc/config/.nasaudiopasswd': No such file or directory
/etc/init.d/unixadmin start
/etc/init.d/time start
/etc/init.d/mdns nothing
/etc/init.d/rmthttp start
/etc/init.d/wan nothing 1
/etc/init.d/wan nothing 2
/etc/init.d/wan start 3
/etc/init.d/wan nothing 4
/etc/init.d/qos start all
lan2: topology change detected, propagating
lan2: port 1(ath1) entering forwarding state
/etc/init.d/shaping nothing
/etc/init.d/dhcp start all
/etc/init.d/dhcpd nothing all
/etc/init.d/dhcrelay nothing all
/etc/init.d/hbrdhcp start all
/etc/init.d/dnsmasq start all
/etc/init.d/dnsmasq start all
/etc/init.d/pppd start all
/etc/init.d/dhclient start all
/etc/init.d/wifi.d/hostapd start all
/etc/init.d/wifi.d/wsccmd start all
/etc/init.d/wifi.d/wpa_supplicant start all
/etc/init.d/pptp stop
/etc/init.d/openl2tp stop
lan3: topology change detected, propagating
lan3: port 1(ath2) entering forwarding state
/etc/init.d/ipsec all
/etc/init.d/fwrules start
lan1: topology change detected, propagating
lan1: port 3(ath0) entering forwarding state
lan1: topology change detected, propagating
lan1: port 1(eth0.1) entering forwarding state
/etc/init.d/iptables start
/etc/init.d/ebtables start
/etc/init.d/routes start
/etc/init.d/upnp nothing
/etc/init.d/dyndns nothing
/etc/init.d/inittab
/etc/init.d/stunnel start
/etc/init.d/phy start 1 1
using the specified MII index 19.
resetting the transceiver...
restarting autonegotiation...
/etc/init.d/phy start 1 2
using the specified MII index 18.
resetting the transceiver...
restarting autonegotiation...
/etc/init.d/phy start 1 3
using the specified MII index 17.
resetting the transceiver...
restarting autonegotiation...
/etc/init.d/phy start 1 4
using the specified MII index 16.
resetting the transceiver...
restarting autonegotiation...
/etc/init.d/inittab
rc completed
Starting pid 2109, console /dev/null: '/sbin/klogd' 
Starting pid 2110, console /dev/null: '/bin/dnsmasq-2' 
Starting pid 2111, console /dev/null: '/sbin/hostapd' 
Starting pid 2112, console /dev/null: '/sbin/igmpproxyd' 
Starting pid 2114, console /dev/console: '/bin/wdgd' 
Starting pid 2113, console /dev/console: '/bin/resetd' 
Starting pid 2108, console /dev/null: '/sbin/syslogd' 
Software Watchdog Timer: set margin to 40 sec.
ni->ni_vap->iv_opmode = 6
ni->ni_vap->iv_opmode = 6
ni->ni_vap->iv_opmode = 6
ni->ni_vap->iv_opmode = 6
ni->ni_vap->iv_opmode = 6
ni->ni_vap->iv_opmode = 6
lan1: port 3(ath0) entering disabled state
ath_newstate: Resetting VAP dfswait_run
ath_newstate: Resetting VAP dfswait_run
lan1: port 3(ath0) entering listening state
 key_alloc_2pair: sc_splitmic SET to 1
ni->ni_vap->iv_opmode = 6
ni->ni_vap->iv_opmode = 6
lan2: port 1(ath1) entering disabled state
ath_newstate: Resetting VAP dfswait_run
ath_newstate: Resetting VAP dfswait_run
lan2: port 1(ath1) entering learning state
 key_alloc_2pair: sc_splitmic SET to 1
fuse init (API version 7.8)
fuse distribution version: 2.6.5
/etc/init.d/upgd nothing
/etc/init.d/inetd start
/etc/init.d/http start
/etc/init.d/htpwd start
/etc/init.d/tr069 nothing
/etc/init.d/usbdevices
usbcore: registered new driver usbserial
drivers/usb/serial/usb-serial.c: USB Serial support registered for generic
usbcore: registered new driver usbserial_generic
drivers/usb/serial/usb-serial.c: USB Serial Driver core
drivers/usb/serial/usb-serial.c: USB Serial support registered for airprime
usbcore: registered new driver airprime
/etc/init.d/voip-asterisk start
lan1: port 3(ath0) entering learning state
lan2: topology change detected, propagating
lan2: port 1(ath1) entering forwarding state
/etc/init.d/bluetooth nothing
/etc/init.d/host start
/etc/init.d/userscreatedir start
/etc/init.d/usersdir start 1
/etc/init.d/usersdir start 2
/etc/init.d/sambaserver refresh
/etc/init.d/upnpav nothing
/etc/init.d/pureftpdserver start
/etc/init.d/obexpush nothing4
/etc/init.d/web start
/etc/init.d/printer start
lan1: topology change detected, propagating
lan1: port 3(ath0) entering forwarding state
/etc/init.d/webcam start
usbcore: registered new driver usblp
drivers/usb/class/usblp.c: v0.13: USB Printer Device Class driver
/etc/init.d/inittab
Reloading /etc/inittab 
Starting pid 2833, console /dev/console: '/bin/thttpd' 
Starting pid 2840, console /dev/null: '/sbin/inetd' 
Starting pid 2841, console /dev/null: '/sbin/nmbd' 
Starting pid 2832, console /dev/console: '/bin/asterisk' 
Starting pid 2842, console /dev/null: '/sbin/p910nd' 
Starting pid 2843, console /dev/null: '/sbin/smbd' 

```