# Introduction #
Sometimes you might need to build a very small Linux rootfs+kernel for your embedded device, or you just want to optimize the space required for the core operating system. One way is to use [OpenEmbedded](http://wiki.openembedded.net/index.php/Main_Page), but there are other alternatives like [BuildRoot](http://buildroot.uclibc.org/) in this example.

# Steps #
## step 0) go to home folder ##
```
$ cd 
```
## step 1) download BuildRoot ##
```
$ wget -c http://buildroot.uclibc.org/downloads/buildroot-2010.02.tar.gz
```
## step 2) unpack BuildRoot ##
```
$ tar -xvzpf buildroot-2010.02.tar.gz
```
## step 3) move BuildRoot to ~/buildroot ##
```
$ mv buildroot-2010.02 buildroot
```
## step 4) install external dependencies ##
```
$ apt-get install binutils bzip2 automake g++ bison flex make ncurses-dev gettext
```
## step 5) go to ~/buildroot ##
```
$ cd buildroot
```
## step 6) configure BuildRoot ##
```
$ make menuconfig
```
## step 7) configure kernel ##
```
$ make linux26-menuconfig
```
## step 8) build BuiltRoot and Kernel ##
```
$ make
```
## step 9) install new root and kernel ##
TBD