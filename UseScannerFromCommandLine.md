# Introduction #

```
 sudo apt-get install sane sane-utils imagemagick
```


# List available scanners #
```
 scanimage -L
```
## example output ##
```
device `plustek:libusb:004:004' is a Canon CanoScan LiDE25 flatbed scanner
```

# Scan image #
```
 scanimage
```
## example output ##
the scanned image in ppm format.

# Scan image as A4 grayscale png #
```
scanimage -l 0 -t 0 -x 215 -y 297 --resolution 150 --mode Gray | convert - `date +%s`.png
```
## example output ##
This will create a png file which is a grayscale scan of the image and which is named with a timestamp.