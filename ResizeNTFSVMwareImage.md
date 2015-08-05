# Introduction #

As it might happen that you install a windows using too small disk size and then it hits you in the middle of your development cycle that actually you would have required twice as big virtual disk what you have now. Well it might not be so easy as you might think.

# Details #
```
Current virtual disk size: 10Gb
Target virtual disk size: 20Gb
```

# Resize the vmware image on the host machine #
```
vmware-vdiskmanager -x 20G imagename.vmdk
```

# Resize the ntfs partition using Linux on virtual machine #
Use Knoppix or install Debian from netinst to a new virtual machine. Install ntfs-3g package.
## Check that you have correct drive information ##
```
ntfsresize -i /dev/[your_drive]
```

## Try first ##
```
ntfsresize -n -s 20G /dev/[your_drive]
```

## Then do it ##
```
ntfsresize -s 20G /dev/[your_drive]
```

# Boot your windows virtual machine #
You should have now a bigger hard disk.