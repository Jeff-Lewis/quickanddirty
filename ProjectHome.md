As we develop misc number of python scripts and small applications with Qt/C++, you can download them from here and use them as you like..

  * Some stuff also for Atmel AVR 8-bit MCU as well :p

Mainly these are small ones and unmaintained, but might come handy. ;)


If you have any questions you can contact us using juhapekka.piiroinen@gmail.com.

<a href='https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=7MVF42LLU4NUS'><img src='https://www.paypal.com/en_US/i/btn/btn_donateCC_LG.gif' /></a>



# Table of Contents #


# News #

## 7/2011 - Idea: Safe Way to Home ##
One idea got "No Thanks" from "Invent with Nokia". So here it is for you then:
```
*Title*
Safe Way to Home

*Created*
20-May-2011

*Updated*
04-Jul-2011

*Status*
No Thanks

*Summarise the invention in terms of the benefit to the consumer.*
The current mobile handsets has location tracking features. 
Those could be used to track your own children and 
make a learning patterns there to the routes. 
If the children are going away from the learned 
route the parents would get an alarm and the 
real-time location information to the parent
 mobile handset as push notification or similar methods. 

This would help also in the scenarios if children 
are abducted and they are carrying mobile handsets
 with location aware features. The system would 
be totally automatic so no user interaction would be required.

*Summarise the invention in terms of the potential benefits to Nokia.*
Positive media value 
Would make the world better place 
Would utilise already existing features on the mobile handsets

*Summarise the science and technology in your invention, as far as you are able to with non-confidential information.*
The location aware system would scan the local area network,
 including bluetooth, wlan and other wireless devices. 
Then it would get the current gps location and 
send the details to a web service, from which 
those details would be distributed to the parental devices.
 The pattern learning would be done in the server 
side in order to minimize the power usage on the device side.

*What are the main strengths of your IP?*
Uses existing technical solutions. 
Software only. 
Even I could implement it with Qt.
```

## 6/2011 - Livetransfer ##
This idea is to provide open and free protocol/transport-layer for applications and end-users. This is an application entry for MeeGo Coding Competition 2011. See more details @ http://code.google.com/p/livetransfer.

## 5/2011 - Motion stabilized web browser for mobile devices ##
The latest idea came to my mind when I was travelling in a bus and reading slashdot from my mobile phone. The most annoying part in that is that the whole device is shaking which makes it really hard to read. So I started to work on a software based image stabilization for web browser. I have a first prototype done and I should be able to release the source code for you soon.

But the quick-and-dirty idea is to use QGraphicsView and implement QGraphicsWebView in it, then use QtMobility to read sensor data to apply opposite action to the position of the webview.

The problem what this is solving is that the picture/text will stay put, even on the road. Should reduce headache and make the reading experience far more fluent what it is now.

An update 13.5.2011, It seems like that it might not be possible to get fast enough performance from the lower level sensor interfaces on Nokia Devices like N900 or E7. So the feature should be implemented by the hardware manufacturer itself to get really working version. The point is that we need high sample rate from the sensors we need to be able to make the corresponding adjustments to the screen also really fast. So the screen should be hardware accelerated GL, which would then do the work in the GPU.
## 4/2011 - Added cutetracker application concept ##
Cutetracker is a gps tracking application for mobile devices. It uses Qt and QtMobility 1.2. The idea is to provide an interface for logging the gps coordinates while the application is running and displaying map and current speed to the user.

http://code.google.com/p/cutetracker/

![http://cutetracker.googlecode.com/svn/trunk/screenshot.png](http://cutetracker.googlecode.com/svn/trunk/screenshot.png)
## 4/2011 - Started to work on a Review\_Freescale\_LFSTBUSB\_LFSTBEB845x for element14.com ##
work in progress memo is available [here](http://code.google.com/p/quickanddirty/wiki/Review_Freescale_LFSTBUSB_LFSTBEB845x).

## 4/2011 - Added a cheat sheet for N900DE Meego 1.2 ##
check it out [here](http://code.google.com/p/quickanddirty/wiki/SettingN900ForMeeGoDevelopment).
## 4/2011 - Quick-And-Dirty @ MeeGo Summit FI, Tampere 15-16.4.2011 ##
Follow me:
  * http://code.google.com/p/cutedrone
  * http://code.google.com/p/cutedrone/wiki/Meegathon
  * https://profiles.google.com/juhapekka.piiroinen

### 2nd place ###
I won new AR.Drone from COSS.fi and a Nokia N900 from Forum Nokia.
<a href='http://www.youtube.com/watch?feature=player_embedded&v=Mkk20ONSQe8' target='_blank'><img src='http://img.youtube.com/vi/Mkk20ONSQe8/0.jpg' width='425' height=344 /></a>

## 3/2011 - Chumby One with Qt ##
I have been playing with Chumby One and compiled and deployed Qt Framework to it. I have been written a wiki notes about the process, feel free to see them as i keep updating it.
ChumbyOneDevelopmentWithScratchbox

## 3/2011 - google code wiki and source pages are crashing again.. error 500.. ##
i was about to update a new wiki topic on Chumby One but it seems that the whole wiki section is down.. And no means to ask for support or notify that there is error 500 :D

EDIT: it was down about 15min.

## 3/2011 - added new idea ##
scroll down this page to the Ideas there is the [NFC Shopping Experience](http://code.google.com/p/quickanddirty/#NFC_shopping_experience).

## 3/2011 - cutedrone ##
[CuteDrone](http://code.google.com/p/cutedrone/) is an AR.drone controlling library for Qt.
## 3/2011 - cutechat ##
[CuteChat](http://code.google.com/p/cutechat) is a xmpp/gtalk client done with Qt.
## 3/2011 - cuterdprecorder ##
[CuteRDPRecorder](http://code.google.com/p/cuterdprecorder/) is a rdp recorder tool for Linux done with Qt.
## 3/2011 - cuteauthenticator ##
[CuteAuthenticator](http://code.google.com/p/cuteauthenticator/) is a [Google Authenticator](http://code.google.com/p/google-authenticator/) client which is coded with Qt. Works with Windows, Linux, OSX and Symbian^3.

![http://cuteauthenticator.googlecode.com/svn/trunk/screenshot.png](http://cuteauthenticator.googlecode.com/svn/trunk/screenshot.png)


## 2/2011 - how to setup APC UPS for Linux ##
[APCinLinux](APCinLinux.md)
## 1/2011 - welho dvb-t channels.conf for VDR ##
[WelhoDVBT](WelhoDVBT.md)
## 1/2011 - how to use scanner from command line ##
[UseScannerFromCommandLine](UseScannerFromCommandLine.md)

## 1/2011 - how to set-up quick-and-dirty hotspot with Linux ##
[CreatingWirelessHotspotWithLinux](CreatingWirelessHotspotWithLinux.md)

## 1/2011 - how to share data on plain sight ##
Sometimes you might want to share data with your BFFs, so i described a quick-and-dirty solution, which is obvious, but still good to document.
http://code.google.com/p/quickanddirty/wiki/HidingDataOnPlainSight

## 12/2010 - cutewebshot project started ##
Stay tuned @ http://code.google.com/p/cutewebshot/
## 9/2010 - tyotunnit web application released ##
A project work hours tracking application released. work in progress. several usability issues.. :S http://tyotunnit.appspot.com/

## 8/2010 - AVR: USI module I2C/SMBus to UART gateway in progress ##
  * i will document the progress to a wiki page @ [AVR\_USI\_I2C\_UART\_Gateway](AVR_USI_I2C_UART_Gateway.md)

## 7/2010 - JSON interface to Verkkokauppa.com released ##
  * The JSON interface is available @ http://www.jpii.fi/vk/productinfo.php?id=12345&callback=thecallback
  * The GWT (Java) and HTML5 Storage demo frontend @ http://www.jpii.fi/vk/PriceMonitor.html. Source code to be published soon, after refactoring.

## 6/2010 - Pololu Micro Maestro 6-Channel USB Servo Controller -python wrapper ##
Thank you Brian Wu for proving updates for the Python wrapper. I have combined the updates to the source tree and now checking the really kewl idea of the new CameraDriver -class.
  * [Revision notes](http://code.google.com/p/quickanddirty/source/detail?r=421)

## 6/2010 - Voipaperi ##
http://code.google.com/p/voipaperi/

## 5/2010 - Wireless Microphone for N900 ##
https://garage.maemo.org/projects/wirelessmic/

## 5/2010 - Upright for Maemo ##
https://garage.maemo.org/projects/upright/

## 9.5.2010 - DVB-T with Debian 5.0 ##
See [wiki](http://code.google.com/p/quickanddirty/wiki/DVBTWithDebian)

## 9.5.2010 - buildroot with Debian 5.0 ##
See [wiki](http://code.google.com/p/quickanddirty/wiki/BuildRootWithDebian5)

## 29.4.2010 -> 4.5.2010 - Connecting stuff to AVR ##
I have started to collect the small schematics which I have created during the hacking with AVR. See [wiki page](http://code.google.com/p/quickanddirty/wiki/AVRConnectingHardware).
## 29.4.2010 - Programming AVR ##
I have started to document the AVR related programming issues and software. See [wiki page](http://code.google.com/p/quickanddirty/wiki/AVRProgramming).
## 22.4.2010 - HUAWEI Mobile Connect E160E USB HSDPA Mobile Stick @ Ubuntu 9.10 ##
I have to admit that the device itself is a great piece of work, but when using it with Ubuntu 9.10 and NetworkManager it really felt to be too much of a trouble. These wasted hours of dirty deeds did remind me that you should not replace a working idea with a new one, when there is no obvious benefits from it. So the combination Ubuntu 9.10+wvdial worked fine for the old desktop which my parents have. See the details in [wiki](http://code.google.com/p/quickanddirty/wiki/HuaweiE160EUbuntu910).
## 20.4.2010 - jpiiLife ##
Got bored. So I made a game of life. :P <br />
..source code in svn. The idea started from a [Conway's Game of Life](http://en.wikipedia.org/wiki/Conway's_Game_of_Life) article in Wikipedia.<br /><br />
### Screenshots ###
![http://quickanddirty.googlecode.com/svn/trunk/jpiilife/screenshot.png](http://quickanddirty.googlecode.com/svn/trunk/jpiilife/screenshot.png)
![http://quickanddirty.googlecode.com/svn/trunk/jpiilife/screenshot2.png](http://quickanddirty.googlecode.com/svn/trunk/jpiilife/screenshot2.png)
```
USAGE: jpiilife.py --width=320 --height=240 --cell=20 --framelimit=100 --life=100

Press <any_key> to reset the board
Press <Mouse1> to add life
Press <Mouse2> to remove life
```
### Requires / Uses ###
  * Python
  * pygame
  * sys,random,getopt
### Source Code ###
  * [jpiilife.py](http://code.google.com/p/quickanddirty/source/browse/trunk/jpiilife/jpiilife.py)

## 19.4.2010 - Face Tracking with Webcam and Servos ##
I have started to play with Pololu Micro Maesto 6-channel USB Servo Controller and I managed to make a Python wrapper for it. I will document those ones later on.
<br /><br />
The biggest thingie now is that I have a webcam with face detection (opencv) and the camera is rotated automatically according to how much the user moves in the picture.
<br /><br />
Kewl stuff ;P ..[keep tuned](http://code.google.com/p/quickanddirty/wiki/RotatingWebcamWithFaceDetection)!
## 18.4.2010 - Pololu 3pi Robot Cheat Sheet ##
Added a cheat sheet for the 3pi robot to the [wiki](http://code.google.com/p/quickanddirty/wiki/Pololu3piRobot).
## 17.4.2010 - Mr Bug Duster documentation started ##
I have started to document the custom robot which I am building at home. The name of the robot is [MrBugDuster](http://code.google.com/p/quickanddirty/wiki/MrBugDuster).
## 29.3.2010 - Hardware virtualization and emulation based sandboxing for web rendering ##
```
I have been playing with the idea of having the web rendering 
processes running in an Linux environment inside QEmu/VMware -image. I 
have been looking for the IPC documentation of the Chromium browser as 
it would make sense just to separate the existing codebase to 
different packages and then handle the IPC over TCP/IP. The benefit in 
this would be that there could be a really good protection against 
malware and other evil apps from the user point of view. As the idea 
would be that each tab would have its own virtual computer and when 
the tab is closed the virtual computer is deleted. 
Another thing is that the firewall bypassing which is now reality with 
web browsers would limit to the virtual machine and the client machine 
would be safe, including the personal files. One benefit would be also 
that the antivirus applications and system monitoring could be running 
inside those virtual machines, which would mean also that you could 
assign browsing related scanning resource usage to the minimum. 
Or you could have the browser sessions for example in Amazon Web 
Services which would mean that next time you would recover full 
sessions on browser startup and the sessions would not be dependent of 
the location/machine. This would also enable real background 
downloading while the laptop is shutdown. 

I guess I could clarify my dumb question a bit more :P ..so the 
document in the http://www.chromium.org/developers/design-documents/inter-process-com... 
states that in Unix Chromium used socketpair and in Windows it uses 
named pipes. So at least in theory the Unix side should be easy to 
change and I guess in the windows side some kind of named pipe to tcp/ 
ip service should be done
```
  * More at [Chromium-discuss](http://groups.google.com/a/chromium.org/group/chromium-discuss/browse_thread/thread/57afc6eedd0dc9b8#)
## 29.3.2010 - New Wiki page for Electronics and Robotics ##
[ElectronicsAndRobotics](http://code.google.com/p/quickanddirty/wiki/ElectronicsAndRobotics)

## 28.3.2010 - New Wiki page for Maemo SDK ##
Created a [wiki page](http://code.google.com/p/quickanddirty/wiki/LinuxDeveloperEnvironment) which has all the steps how to create a Maemo development environment using vmware and cygwin/x.
![http://quickanddirty.googlecode.com/files/xephyr-af-sb-init.png](http://quickanddirty.googlecode.com/files/xephyr-af-sb-init.png)

## 28.3.2010 - SaunaSMS Garage Opened ##
development continues in [garage.maemo.org](https://garage.maemo.org/projects/saunasms/)

## 27.3.2010 - compiling Linux with OpenEmbedded for the iPaq ##
The resulting binary will be released soon, hopefully ;) EDIT: after some surfing, i noticed that there was a [online builder](http://www.angstrom-distribution.org/narcissus/) for the images available from Angstrom distribution.

## 27.3.2010 - applied for garage.maemo.org: SaunaSMS ##
new project access rights for SaunaSMS. The development has been started on the project and hopefully I will receive the rights to distribute for the Maemo5 devices.

## 27.3.2010 - Wiki page: Linux @ iPaq ##
[installed Linux on an old Pocket PC](http://code.google.com/p/quickanddirty/wiki/LinuxIPaqH38xx) (HP Compaq iPaq 38xx -series).
![http://quickanddirty.googlecode.com/files/iPaqOpie_desktop.jpg](http://quickanddirty.googlecode.com/files/iPaqOpie_desktop.jpg)

## 20.3.2010 - added new application: jpiiAVR ##
which is a wrapper application on top of the avrdude. Qt/C++. Available @ svn.
  * PDF reader ([poppler](http://poppler.freedesktop.org/)) for datasheets
  * ISP connectors in Help tab
  * [avr-gcc/avr-objcopy](http://www.nongnu.org/avr-libc/) wrapper for compiling code into hex,eep,elf
  * [avrdude](http://www.bsdhome.com/avrdude/) support for flashing hex into microprocessor
![http://quickanddirty.googlecode.com/svn/trunk/jpiiavr/screenshot.png](http://quickanddirty.googlecode.com/svn/trunk/jpiiavr/screenshot.png)

## 19.3.2010 - New script added: Quick-and-dirty Ruutu.fi Player ##
[quick-and-dirty ruutu player](http://quickanddirty.googlecode.com/files/quick-and-dirty-ruutu-player-0.1.zip) added. will play ruutu.fi videos on full screen inside browser. Uses HTML and JavaScript with FlowPlayer (SWF)

## 21.2.2010 - new application added: Quick-and-dirty Utility ##
[qadUtility](http://code.google.com/p/quickanddirty/source/browse/#svn/trunk/qadutility) which can be used to convert text to Base64, SHA1, MD4, MD5, Percent Encoding and from Base64, Percent Encoding, JavaScript. Made with Qt/C++. Available @ svn.
![http://quickanddirty.googlecode.com/svn/trunk/qadutility/screenshot.png](http://quickanddirty.googlecode.com/svn/trunk/qadutility/screenshot.png)

## 20.2.2010 - New script added: utf16-2-stdout ##
[utf16-2-stdout.py](http://quickanddirty.googlecode.com/files/utf16-2-stdout.py) - print UTF16 Big-Endian or UTF16 Little-Endian files to stdout. Excellent tool to view weird JavaScript files ;)

## 20.1.2010 - New application added: Quick-and-dirty Proto Designer ##
![http://quickanddirty.googlecode.com/svn/trunk/jpiiprotodesigner/screenshot.png](http://quickanddirty.googlecode.com/svn/trunk/jpiiprotodesigner/screenshot.png)
> [Quick-and-dirty Protoboard Designer 0.1](http://quickanddirty.googlecode.com/files/qadProtoDesigner-0.1) - Qt4, Linux x86 binary only! Sources and real release is coming.
> Features:
    * save/load and printing is supported.
    * mouse press to change tile type

## 4.1.2010 - New application added: Webcam Notebook ##
[Quick-and-dirty - WebcamNotebook](http://quickanddirty.googlecode.com/files/webcamNotebook-v0.1.py), application requires [VideoCapture](http://videocapture.sourceforge.net/), [PyQt4](http://www.riverbankcomputing.co.uk/software/pyqt/download), [PIL](http://www.pythonware.com/products/pil/)
http://quickanddirty.googlecode.com/files/quick-and-dirty_webcamnotebook.PNG

## Older News (Before 2010) ##
### K8055 Project launched ###
New project launched [quickanddirty-k8055-nslu2](http://code.google.com/p/quickanddirty-k8055-nslu2/)

### SaunaSMS OSX Dashboard Widget released ###
Now you can send sms from the dashboard, enjoy!

### SaunaSMS developer API released ###
see message [here](http://palsta.saunalahti.fi/index.php/topic,10095.msg88361.html#msg88361)

### SaunaSMS Online released ###
Now it is possible to send the sms messages from Google App Engine project. Cheers!   http://saunasms.appspot.com

### Added YLE Text ###
Added new small software, it is called [YLEtxTV.py](http://quickanddirty.googlecode.com/files/YLEtxTV.py), it "emulates" the old fashion television texttv.

### SSH Cron ###
New project is to be released soon. A software which will connect to SSH servers which are defined in CSV file. Then commands are executed in server automatically (cmds in csv file). I will have to find the file.. i have lost the file somewhere.. argh. -- Found it! You can download now [SSHCron](http://quickanddirty.googlecode.com/files/SSHCron.tbz).

### Eclipse Collaboration Plugin ###
Another project is under design. An Eclipse plugin for better collabration. Includes chat ;) => There is already that kind of feature in 3.4 and it is called Collabration :P ..and even better there is a plugin called [Cola](http://www.vimeo.com/1195398?pg=embed&sec=1195398) which enables to edit files with multiple persons at the same time.

### Added Quick And Dirty Chat ###
([qadchat.py](http://quickanddirty.googlecode.com/files/qadchat.py)) application to downloads. It is a working example how to build socket server with Python. Use Putty as an frontend for chats ;)

### Quick-and-dirty RRS Reader ###
New project is under development, it is called [qad\_rssreader](http://code.google.com/p/quickanddirty/wiki/qad_rssreader). You can see the results from [feed.fi](http://www.feed.fi/). Main software is in Python and frontend uses PHP.

# Ideas #
## Latest ##
### NFC shopping experience ###
#### preconditions ####
End user has his/her NFC/rfid enabled handset.
#### use-case ####
  1. goes to a store.
  1. finds an interesting item.
  1. moves handset over the price tag.
  1. gets the item to a virtual shopping cart
  1. moves to another item
  1. when leaving from store he/she has an option to reserve items for pickup or to store them for later reference. Or to get a quote to her/his email/handset.
  1. if user selects them for pickup then he/she goes to the storage/pickup area where is a NFC enabled counter.
  1. user places his/her handset over the counter and products will be delivered from the automated storage to the counter behind a glass.
  1. user then observes the items and selects the final set of items what he/she wants.
  1. user selects and makes the purchase with his/her handset which is still on the counter
    * when purchase has been done the glass is lifted and user can get his/her items and leave the store or
    * user can also select a shipping method for the items, and in this case user will receive an email or a message to handset which will contain the delivery information.
      * from the delivery information the user can then select when and where he/she wants to get the products.
      * products are moved automatically from the counter to the shipping department for automated shipping and handling.
      * user leaves the store and waits for the parcel

## Ideas Before 2010 ##
### Yet another poker project idea ###
..a php/python backend, ajax frontend. Online anonymous poker game where all the hands in the games are stored in database backend. All games can be browsed afterwards online. Shows also possibilities of the next coming hands based on game history. Database would have also json interface for 3rd party apps and statistics. The possibility to integrate the system to facebook should also be researched. It would be fun to challenge your contact to a poker game, where the game is not played realtime but as turnbased like some roleplaying games.

### a web spider ###
which will crawl websites and "clicks" ads and banners. Supports blacklist from adblock. If everybody would use this and adblock at the same time, in some point the ads wouldnt exist anymore. :) ..to be honest, this would work when it would be done like the Seti@Home. Everyone would run the software when they arent using their own www-connection and after awhile there wouldnt be any profit to buy web-ad-space :P

### Image Sharing software ###
software will create a packaged list of your shared pics and uses thumbnails. Shares that package thru network to your contacts. Contacts will request for an update of the packaged list. Contacts will then browse your pictures and ask for full pictures. Purpose of the software is to provide an easy-sharing method for normal computer users instead of email.

# Misc Before 2010 #
## Wiki Page MySQL Backup ##
[mysqlbackup](http://code.google.com/p/quickanddirty/wiki/mysqlbackup) - how to automate mysql backups

## Package Update application ##
[package\_update](http://code.google.com/p/quickanddirty/wiki/package_update) - generates a list of available updates, select the ones you want to update and get to bed. When you wake up in the morning the updates has been installed. Or just access your server remotely  using your mobile and install critical security update - (eix, apache, cron, subprocess, time, os, mod\_python, shutil, **Gentoo**)

## Script Applications ##
### YLE Text Television ###
[YLEtxTV](http://quickanddirty.googlecode.com/files/YLEtxTV.py) - desktop texttv for finnish television. uses [pygame](http://www.pygame.org).

### SSH Cron ###
[SSHCron](http://quickanddirty.googlecode.com/files/SSHCron.tbz) - connect to multiple SSH servers and execute commands automatically - ([pyssh](http://pyssh.sourceforge.net/))

### SaunaSMS <1.0 ###
[SaunaSMS (src)](http://quickanddirty.googlecode.com/files/saunasms_src.zip) or [SaunaSMS (win)](http://quickanddirty.googlecode.com/files/SaunaSMSv0.3.zip) - SMS messenger for a finnish gsm operator Saunalahti. You can send free sms from your desktop. - [wxpython](http://wxpython.org/), [urllib2](http://docs.python.org/lib/module-urllib2.html), [cookiejar](http://docs.python.org/lib/cookie-jar-objects.html), [sys](http://docs.python.org/lib/module-sys.html), [time](http://docs.python.org/lib/module-time.html), [re](http://docs.python.org/lib/module-re.html), [py2exe](http://www.py2exe.org/), [wxglade](http://wxglade.sourceforge.net/)

### Quick-and-dirty Chat ###
[qadchat.py](http://quickanddirty.googlecode.com/files/qadchat.py) - Chat server with threading - [thread](http://docs.python.org/lib/module-thread.html), [socket](http://www.python.org/doc/lib/module-socket.html)

### Gentoo Portage Uploader ###
[Gentoo Portage uploader and remover](http://code.google.com/p/quickanddirty/wiki/GentooPUAR) - ([dircache](http://docs.python.org/lib/module-dircache.html), [ftplib](http://docs.python.org/lib/module-ftplib.html))

### Shuffle MP3 Player ###
[Shuffle MP3 Player](http://code.google.com/p/quickanddirty/wiki/ShuffleMP3Player) with xosd support for Linux ([pyGame](http://www.pygame.org/),[pyosd](http://ichi2.net/pyosd/),[eyeD3](http://eyed3.nicfit.net/))

### Quick-and-dirty Media ###
[Quick and Dirty Media](http://code.google.com/p/quickanddirty/wiki/QuickAndDirtyMedia)  - Plays videos and audio

[pygtk](http://www.pygtk.org/),[pygst](http://gstreamer.freedesktop.org/modules/gst-python.html),[pyosd](http://ichi2.net/pyosd/))

### Portable Executable Reader ###
Reads string description from Portable Executable files a.k.a Windows binaries. -
  * Language:
```
Python
```
  * Requires:
```
pefile
```
  * Links:
    * [pefile](http://code.google.com/p/pefile/)

### Google Mail - New Message Checker ###
[check\_gmail](http://code.google.com/p/quickanddirty/wiki/check_gmail) - Check your gmail account for new messages, using IMAP / SSL connection from console
  * Language:
```
Python
```
  * Requires:
```
imaplib, md5, getpass
```
  * Links:
    * [md5](http://docs.python.org/lib/module-md5.html)
    * [imaplib](http://docs.python.org/lib/module-imaplib.html)
    * [getpass](http://docs.python.org/lib/module-getpass.html)


### Internet File Downloader - wget ###
[wget](http://code.google.com/p/quickanddirty/wiki/wget) - Internet file downloader
  * Language:
```
Python
```
  * Requires:
```
urllib2
```
  * Links:
    * [urllib2](http://docs.python.org/lib/module-urllib2.html)


### RSS Reader ###
[rssreader](http://code.google.com/p/quickanddirty/wiki/rssreader) - Reads RSS feeds
  * Language:
```
Python
```
  * Requires:
```
FeedParser
```
  * Links:
    * [feedparser](http://www.feedparser.org/)

### Google Mail Inbox Archiver ###
[ginbox](http://code.google.com/p/quickanddirty/wiki/ginbox) - Gmail Inbox Archiver
  * Language:
```
Python
```
  * Requires:
```
getpass, imaplib, tarfile
```
  * Links:
    * [getpass](http://docs.python.org/lib/module-getpass.html)
    * [imaplib](http://docs.python.org/lib/module-imaplib.html)
    * [tarfile](http://docs.python.org/lib/module-tarfile.html)

### WWW Server ###
[wwwserver](http://code.google.com/p/quickanddirty/wiki/wwwserver) - www server with cgi support
  * Language:
```
Python
```
  * Requires:
```
BaseHTTPServer, CGIHTTPServer
```
  * Links:
    * [BaseHTTPServer](http://docs.python.org/lib/module-BaseHTTPServer.html)
    * [CGIHTTPServer](http://docs.python.org/lib/module-CGIHTTPServer.html)

## Scripts ##
### Batch Rename Files To Lowercase ###
[tolower](http://code.google.com/p/quickanddirty/wiki/tolower) - Browse given folder and rename all files and subfolders to lowercase
  * Language:
```
Python
```

### FLV Cache Copier ###
[flvcache](http://code.google.com/p/quickanddirty/wiki/flvcache) - Browse flv movie cache folder, preview the cached movie and make a backup
  * Language:
```
Python
```
  * Requires:
```
shutil
```
  * Links:
    * [shutil](http://docs.python.org/lib/module-shutil.html)

### Make Thumbnail ###
[makethumb](http://code.google.com/p/quickanddirty/wiki/makethumb) - Creates thumbnail image from a picture
  * Language:
```
Python
```
  * Requires:
```
PIL
```
  * Links:
    * [PIL](http://www.pythonware.com/library/pil/handbook/index.htm)

### Adjust Image ###
[adjustimg](http://code.google.com/p/quickanddirty/wiki/adjustimg) - Adjust image properties (color,brightness,contrast,sharpness)
  * Language:
```
Python
```
  * Requires:
```
PIL
```
  * Links:
    * [PIL](http://www.pythonware.com/library/pil/handbook/index.htm)

### Rotate Image ###
[rotateimg](http://code.google.com/p/quickanddirty/wiki/rotateimg) - Flip or rotate image
  * Language:
```
Python
```
  * Requires:
```
PIL
```
  * Links:
    * [PIL](http://www.pythonware.com/library/pil/handbook/index.htm)

### Chroot Copy ###
[chroot\_cp](http://code.google.com/p/quickanddirty/wiki/chroot_cp) - Chroot filecopy utility
  * Requires:
```
ldd, shutil
```

### Console Scripts ###
#### Encrypted ISO Images ####
[Create and mount encrypted isoimages](http://code.google.com/p/quickanddirty/wiki/EncryptedIsoImages) - Secure DVD image creator and mounter script<br />
  * Requires:
```
aespipe, mkisofs and support from kernel for cryptoloop, aes
```

# Note #
We dont recommend the use of these applications. They might destroy your computer and your life and everything else. Use only with a great precaution! As we hear by say that we dont take any responsibility, but if you make modifications you will have to commit the changes to this project.