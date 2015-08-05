# Table of Contents #

# Introduction #

The technique is obvious, but still too funny not to document :p ..the idea is to embed secured filesystem into a website background image.


# Details #

  * Take a website background image which is looking great, like a full color png.
  * Then create a secured filesystem into a file using TrueCrypt  (http://www.truecrypt.org/)
  * copy the truecrypt file at the end of the png file.
  * copy the png file to the website and use it as background or share it thru public www service, etc.

# Benefits #
Regular browsers does work just fine with the images when there are data appended at the end of the file. And usually the thumbnails which are pregenerated in the image file are working as well, so the basic operating system will also preview the image as well. So all in all this should be cross-platform. :-)

And you can use the same method to share data with your friends. Other option would be to replace the background image and with random data padding and footer for the encrypted data. Or you could just split the encrypted filesystem into 2kb pieces and distribute the pieces over several files. Multiple ways to do this ;p ..but this describes the quick-and-dirty solution.

# Scripts #
## Create png file containing the filesystem ##
```
#!/bin/bash
cat $1 > $1.target.png
cat $2 >> $1.target.png
```
### Usage ###
```
./script.sh bg.png filesystem.dta
```
## Extract filesystem from png file ##
```
#!/bin/bash
dd bs=1 if=$1 skip=`stat -c %s $2` of=$3
```
### Usage ###
```
./script.sh bg-with-filesystem.png bg.png target-filesystem-file.dta
```
# Alternate data streams #
On windows you could use alternate datastreams instead of image file.
http://en.wikipedia.org/wiki/NTFS#Alternate_data_streams_.28ADS.29
## Create ##
```
cat filesystem.dta > notepad.exe:thestream
```
## Extract ##
```
cat notepad.exe:thestream > extracted-filesystem.dta
```