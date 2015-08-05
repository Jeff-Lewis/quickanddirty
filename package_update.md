# Introduction #

Python Server Pages script, which will generate html page containing information which packages should be updated.

# Status #
I will fix the script, but you can start using it as it is.
This package will provide an easier way to handle needed package updates.

# Installation #
  1. Download the files
  1. configure apache for mod\_python and for psp files
  1. add updateportage.py to cronjob, ex: `* 5 * * * /install_path/updateportage.py `
  1. add emerge --sync to cronjob, ex: `* 2 * * * emerge --sync `
  1. install eix
  1. password protect the www folder for the script
  1. configure scripts manually for correct path names
  1. start using

# Downloads #
[package\_update.bz2](http://quickanddirty.googlecode.com/files/package_update.bz2)