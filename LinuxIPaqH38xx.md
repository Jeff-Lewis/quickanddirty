

# Introduction #

small quick-and-dirty wiki page, which should contain at least links how to do it.
Opie is Qt-based embedded Linux distribution which has been endorsed by handhelds.org, but nowadays it is more or less obsolete. :)
## Time estimate ##
Without the jffi2 file transfer all of this will take less than one hour, around 20mins. The jffi2 transfer took over 1 hour for me. So more or less around 2 hour of work to be done.

## Requirements ##
  * Really old Pocket PC (HP/Compaq iPaq H38xx)
  * Bootloader and misc (available as download from this document)
  * USB/Serial cradle for Pocket PC
  * Serial-2-USB adapter for the laptop or laptop with Serial connector, required for flash upgrade.
  * A geek. Required for coffee drinking.

## HP Compaq iPaq H38xx ##
![http://quickanddirty.googlecode.com/files/h3800.jpg](http://quickanddirty.googlecode.com/files/h3800.jpg)
  * Processor: 206 MHz Intel StrongARM SA-1110 32-bit RISC Processor
  * Memory: 64/32Mb RAM - 32Mb Flash
  * Display: 64K color (65,536 colors) 16-bit touch-sensitive reflective thin film transistor (TFT) liquid crystal display (LCD)
### More information ###
From [HP page](http://h18000.www1.hp.com/products/quickspecs/10977_na/10977_na.HTML). Some of it has been copied here as the model is nearly 10 years old already, so they might delete stuff soon..


# Details #
## /etc/cpuinfo ##
```
root@h3600:~# cat /proc/cpuinfo
Processor       : StrongARM-1110 rev 9 (v4l)
BogoMIPS        : 137.21
Features        : swp half 26bit fastmult
CPU implementor : 0x69
CPU architecture: 4
CPU variant     : 0x0
CPU part        : 0xb11
CPU revision    : 9

Hardware        : HP iPAQ H3800
Revision        : 0000
Serial          : 0000000000000000
```

## dmesg ##
```
Linux version 2.4.19-rmk6-pxa1-hh37 (rw@sugarcube.dyndns.org) () #1 Tue Aug 15 0
4:50:01 CEST 2006
CPU: StrongARM-1110 revision 9
Machine: HP iPAQ H3800
Ignoring unrecognised tag 0x5441000a
On node 0 totalpages: 8192
zone(0): 8192 pages.
zone(1): 0 pages.
zone(2): 0 pages.
Kernel command line: mtdpart=bootldr@0x00000000:0x00040000,root@0x00040000:0x01F
80000,asset@0x01FC0000:0x00040000 root=/dev/mtdblock1 init=/linuxrc noinitrd con
sole=none
Relocating machine vectors to 0xffff0000
Console: colour dummy device 80x30
Calibrating delay loop... 137.21 BogoMIPS
Memory: 32MB = 32MB total
Memory: 30900KB available (1099K code, 304K data, 68K init)
Dentry cache hash table entries: 4096 (order: 3, 32768 bytes)
Inode cache hash table entries: 2048 (order: 2, 16384 bytes)
Mount-cache hash table entries: 512 (order: 0, 4096 bytes)
Buffer-cache hash table entries: 1024 (order: 0, 4096 bytes)
Page-cache hash table entries: 8192 (order: 3, 32768 bytes)
POSIX conformance testing by UNIFIX
Linux NET4.0 for Linux 2.4
Based upon Swansea University Computer Society NET3.039
Initializing RT netlink socket
CPU clock: 206.400 MHz (59.000-287.000 MHz)
sa1110_clk_init: h3xxx_membank_size[0]=33554432
sa1110_clk_init: 100 MHz Samsung 4Mx16bitx4banks SDRAM
SDRAM: tck: 10 trcd: 20 trp: 30 twr: 30 refresh: 64000 cas_latency: 3
MDCNFG: 33013355 MDREFR: 00302007 MDCAS0: aaaaaa9f MDCAS1: aaaaaaaa MDCAS2: aaaa
aaaa
new dri value = 12
Starting kswapd
devfs: v1.12a (20020514) Richard Gooch (rgooch@atnf.csiro.au)
devfs: boot_options: 0x1
JFFS2 version 2.2. (C) 2001-2003 Red Hat, Inc.
ttySA%d0 at MEM 0x80050000 (irq = 17) is a SA1100
dma period = 1398056 ps, clock = 206400 kHz
dma period = 1398056 ps, clock = 206400 kHz
Console: switching to colour frame buffer device 40x30
iPAQ H3600 keyboard driver v1.0.1
pty: 256 Unix98 ptys configured
RAMDISK driver initialized: 16 RAM disks of 4096K size 1024 blocksize
iPAQ flash: probing 32-bit flash bus, window=c28c0000 with CFI.
IPAQ flash bank 1: Found an alias at 0x2000000 for the chip at 0x0
cfi_cmdset_0001: Erase suspend on write enabled
0: offset=0x0,size=0x40000,blocks=128
Using buffer write method
iPAQ flash: found 33554432 bytes
iPAQ flash: probing 32-bit flash bus, window=c68d0000 with CFI.
CFI: Found no IPAQ flash bank 2 device at location zero
iPAQ flash: probing 32-bit flash bus, window=c68d0000 with JEDEC.
kmod: failed to exec /sbin/modprobe -s -k jedec_probe, errno = 2
iPAQ flash: failed to find flash.
kmod: failed to exec /sbin/modprobe -s -k RedBoot, errno = 2
RedBoot partition parsing not available
Using static partition definition
Creating 3 MTD partitions on "ipaq":
0x00000000-0x00040000 : "H3XXX boot firmware"
mtd: Giving out device 0 to H3XXX boot firmware
0x00040000-0x01fc0000 : "H3XXX root jffs2"
mtd: Giving out device 1 to H3XXX root jffs2
0x01fc0000-0x02000000 : "asset"
mtd: Giving out device 2 to asset
NET4: Linux TCP/IP 1.0 for NET4.0
IP Protocols: ICMP, UDP, TCP, IGMP
IP: routing cache hash table of 512 buckets, 4Kbytes
TCP: Hash tables configured (established 2048 bind 2048)
NET4: Unix domain sockets 1.0/SMP for Linux NET4.0.
NetWinder Floating Point Emulator V0.95 (c) 1998-1999 Rebel.com
mtdblock_open
ok
mtdblock_release
ok
mtdblock_open
ok
VFS: Mounted root (jffs2 filesystem).
Mounted devfs on /dev
Freeing init memory: 68K
Warning: unable to open an initial console.
H3600 Registering HAL abstraction layer
apm: BIOS version 1.2 Flags 0x02 (Driver version 1.13)
h3600_ts_init_module: registering char device
IPv6 v0.8 for NET4.0
IPv6 over IPv4 tunneling driver
irda_init()
IrCOMM protocol (Dag Brattli)
CSLIP: code copyright 1989 Regents of the University of California
PPP generic driver version 2.4.2
devfs_register(ppp): could not append to parent, err: -17
BlueZ Core ver 2.3 Copyright (C) 2000,2001 Qualcomm Inc
Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>
BlueZ L2CAP ver 2.3 Copyright (C) 2000,2001 Qualcomm Inc
Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>
BlueZ RFCOMM ver 1.1
Copyright (C) 2002 Maxim Krasnyansky <maxk@qualcomm.com>
Copyright (C) 2002 Marcel Holtmann <marcel@holtmann.org>
SA1100 Real Time Clock driver v1.03
SA1100 USB Controller Core Initialized
usbctl: Opened for usb-eth
usbctl: Started for usb-eth
[mmc_media.c:434] mmc_media_init
h3600_asic_shared_init
register_serial_h3800 0
 membase=f0000a00 irq=53
serial_h3800_config_port caad158c  flags=1
serial_h3800_request_port caad158c  mapbase=49000a00
ttySB%d0 at MEM 0x49000a00serial_h3800_type caad158c
 (irq = 53) is a H3800_ASIC
[h3600_asic_mmc.c:864] h3600_asic_mmc_init
enable_irq(59) unbalanced from caae6c64
one_wire_reset: OWM reset failed: no battery
iPAQ audio support initialized
Linux Kernel Card Services 3.1.22
  options:  [pm]
<6>SA-1100 PCMCIA (CS release 3.1.22)
sa1100_pcmcia_driver_init: pcmcia_low_level=cab92988
sa1100_pcmcia_driver_init: skt=0 skt->virt_io=caba0000
sa1100_pcmcia_driver_init: skt=1 skt->virt_io=cabc0000
sa1100_pcmcia_driver_init: done
Serial driver version 5.05c (2001-07-08) with no serial options enabled
dma period = 1398056 ps, clock = 206400 kHz
BlueZ HCI UART driver ver 2.1 Copyright (C) 2000,2001 Qualcomm Inc
Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>
```

## df ##
```
root@h3600:/home# df
Filesystem           1k-blocks      Used Available Use% Mounted on
/dev/root                32256     15564     16692  48% /
tmpfs                    15484        40     15444   0% /var
tmpfs                    15484         0     15484   0% /media/ram
```

## /etc/meminfo ##
```
root@h3600:~# cat /proc/meminfo
        total:    used:    free:  shared: buffers:  cached:
Mem:  31711232 29057024  2654208        0        0 19144704
Swap:        0        0        0
MemTotal:        30968 kB
MemFree:          2592 kB
MemShared:           0 kB
Buffers:             0 kB
Cached:          18696 kB
SwapCached:          0 kB
Active:          13328 kB
Inactive:         9848 kB
HighTotal:           0 kB
HighFree:            0 kB
LowTotal:        30968 kB
LowFree:          2592 kB
SwapTotal:           0 kB
SwapFree:            0 kB
```

## Boot messages ##
```
boot> boot
booting jffs2...
booting boot/zImage from partition >root<
loaded file of size = 0x0009C1C0 at location 0xC0008000
kernel partition base C0008000
kernel_magic=E1A00000
kernel_region_words[9]=016F2818
Linux ELF flash_imgstart=50040000 size=01F80000 dest=C0000000 offset=00008000
MMU Control=C19F4071
MMU PIDVAM=00000000
Skipping kernel copy by request.
C0008000: E1A00000
C0008004: E1A00000
C0008008: E1A00000
C000800C: E1A00000
C0008010: E1A00000
C0008014: E1A00000
C0008018: E1A00000
C000801C: E1A00000
C0008020: EA000002
C0008024: 016F2818
root_filesystem_name=ramdisk
Grabbed linuxargs, argc = 00000001
Using mach_type 00000089
setting boot parameters to
root=/dev/mtdblock1 init=/linuxrc noinitrd console=none
Makeing core tag at C0000100
Makeing cmdline tag at C0000114
Makeing mem32 tag at C00001B0
Makeing ptable tag at C00001C0
dram_size=02000000
nr_pages=54410001
command line is: mtdpart=bootldr@0x00000000:0x00040000,root@0x00040000:0x01F8000
0,asset@0x01FC0000:0x00040000 root=/dev/mtdblock1 init=/linuxrc noinitrd console
=none
Disabling LCD controller
linuxEntryPoint=C0008000
Booting Linux image
Uncompressing Linux........................................... done, booting the
 kernel.
boot> irda_con
Don't understand command>irda_con< Try help for a command list.
boot> get_param: could not find parameter placeholder_cmd
ser_con
Don't understand command>ser_con< Try help for a command list.
boot> Uncompressing Linux........................................... done, booti
ng the kernel.

Familiar Linux v0.8.4 h3600 ttySA0

h3600 login:
```
## misc memo ##

root@h3600:~# hciattach -p /dev/ttySB0 any 115200

# Links #

```
http://handhelds.org/download/distributions/familiar/releases/v0.8.4/install/install-serial.html
http://www.handhelds.org/download/distributions/compaq/ipaq/v0.30/install.html
http://www.handhelds.org/download/distributions/compaq/ipaq/stable/
```
# What can you do with this? #
One good reason why you might want to replace the old Pocket PC operating system with Linux, if you are interested to have small Linux server with touch screen for your projects.

# What next? #
I guess I will enable that USB Networking and connect the device to a NSLU2 which runs already Linux as well and then I will share that Internet connection from there using that one and enable Console access to iPaq using Serial-2-USB adapter.

# How did I do it? #
[Read this](http://handhelds.org/download/familiar/releases/v0.8.4/install/install-serial.html) or continue this list. I have copied the major information into this wiki as it seems that the target url does not seem to be up2date and the information might disappear as well soon.

## Install new boot loader to the Pocket PC ##
  1. Upload [bootldr-2.18.01.bin](http://quickanddirty.googlecode.com/files/bootldr-2.18.01.bin) and [BootBlaster\_1.18.exe](http://quickanddirty.googlecode.com/files/BootBlaster_1.18.exe) to Pocket PC.
  1. Run BootBlaster
  1. Install and **VERIFY** the new bootloader (If you FAIL this you leave this step with a brick in your hands)

## Connect Serial-to-USB ##
  * The **only way to install the new Linux** into Flash is to use the Serial interface and XModem transfer!
## Open HyperTerminal (XP/XP-mode) or minicom (Linux) ##
  1. Start terminal application
  1. Connect to the Pocket PC
  1. Reset Pocket PC
  1. See the boot loader info on the terminal
### Settings for serial console ###
  * Bits per second: 115200
  * Data bits: 8
  * Parity: None
  * Stop bits: 1
  * Flow control: None
## Screenshot ##
![http://quickanddirty.googlecode.com/files/iPaqOpie_bootloader.jpg](http://quickanddirty.googlecode.com/files/iPaqOpie_bootloader.jpg)

## Flash the Linux ##
  1. Write 'load root' and press enter
```
boot> load root
```
  1. Upload the [bootopie-v0.8.4-h3600.jffs2](http://quickanddirty.googlecode.com/files/bootopie-v0.8.4-h3600.tar) using XModem.
  1. **Wait for 1h** or more.
  1. **bling** - and the new meal of Linux is ready.
  1. Write 'boot' and press enter.
```
boot> boot
```

# Screenshots #
![http://quickanddirty.googlecode.com/files/iPaqOpie_desktop.jpg](http://quickanddirty.googlecode.com/files/iPaqOpie_desktop.jpg)
![http://quickanddirty.googlecode.com/files/iPaqOpie_cpuinfo.jpg](http://quickanddirty.googlecode.com/files/iPaqOpie_cpuinfo.jpg)