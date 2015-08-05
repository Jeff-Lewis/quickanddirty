# **STOPPED, NOT RECOMMENDED PRODUCT** #



# Introduction #

## What is in the box (RDMMA845X Kit?) ##
### LFSTBEB845x - MMA845xQ accerometers ###
![http://cache.freescale.com/files/graphic/block_diagram/LFSTBEBMMA845x.jpg](http://cache.freescale.com/files/graphic/block_diagram/LFSTBEBMMA845x.jpg)
  * 700-26678: PWA, [LFSTBEB845X](http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=LFSTBEB845X)
  * 700-76784: PWA, [MMA8451Q](http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=MMA8451Q) DIP (14-bit)
  * 700-76785: PWA, [MMA8452Q](http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=MMA8452Q) DIP (12-bit)
  * 700-76786: PWA, [MMA8453Q](http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=MMA8453Q) DIP (10-bit)
  * 920-75531: Technical Information Center Freescale Semiconductor, Inc.
  * 920-75532: Warranty Card, Freescale
  * 920-78478: [Quick Start Guide](http://cache.freescale.com/files/sensors/doc/user_guide/LFSTBEBMMA845XQSG.pdf?fpsp=1), LFSTBEB845x
  * 951-00409: Sensors Toolbox XTrinsic Card
#### Comments ####
There are no CD/DVD or USB-sticks with datasheets and no real-value information inside. A CD or USB-stick with a regular HTML5+CSS3 website inside and those datasheets in PDF would be great. As well as other supporting software. Note also that no Flash or Silverlight should be used on possible CD/DVD or USB-stick.. Should work on all platforms.

### LFSTBUSB - USB Communication ###
![http://cache.freescale.com/files/graphic/block_diagram/LFSTBUSB_HR1.jpg](http://cache.freescale.com/files/graphic/block_diagram/LFSTBUSB_HR1.jpg)
  * 700-26091: PWA, [USB Interface Board](http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=LFSTBUSB)
  * 600-76796: Cable, USB Type A Male / Type Mini B Make 3ft
  * 920-75531: Technical Information Center Freescale Semiconductor, Inc.
  * 920-75532: Warranty Card, Freescale
  * 926-76336: [Quick Start Guide](http://cache.freescale.com/files/sensors/doc/user_guide/LFSTBUSBACCQSG.pdf?fpsp=1), LFSTBUSB
#### Comments ####
There are no CD/DVD or USB-sticks with datasheets and no real-value information inside. A CD or USB-stick with a regular HTML5+CSS3 website inside and those datasheets in PDF would be great. As well as other supporting software. Note also that no Flash or Silverlight should be used on possible CD/DVD or USB-stick.. Should work on all platforms.


# Using the Kit - LFSTBUSB #
## Without Reading the Online Manual ##
### Information in the Quick Start Guide ###
#### Steps ####
  1. Unpack the board. Verify package contents according to the kit website: freescale.com/sensortoolbox
  1. At freescale.com/sensortoolbox download the latest software version by clicking: Download Software
  1. Plug in the USB and turn the board on using the power switch. Run the Sensor Toolbox link on your desktop.
#### Comments ####
I would expect to see an assembly guide and usage information. And then as in more details on website. The facts are missing and seems more like a marketing flyer. Seems to rely heavily on Microsoft Windows. Having only a written links to a website is not a good thing, as Freescale might be upgrading their website in the near future and then all things might not be there anymore..

### Connecting to Linux ###
#### Steps ####
  1. Connect usb cable between LFSTBUSB and your Linux laptop
  1. Switch power on @ LFSTBUSB

#### dmesg ####
```
[14273.976025] usb 6-1: new full speed USB device using uhci_hcd and address 4
[14274.165110] ftdi_sio 6-1:1.0: FTDI USB Serial Device converter detected
[14274.165154] usb 6-1: Detected FT232BM
[14274.165156] usb 6-1: Number of endpoints 2
[14274.165158] usb 6-1: Endpoint 1 MaxPacketSize 64
[14274.165160] usb 6-1: Endpoint 2 MaxPacketSize 64
[14274.165162] usb 6-1: Setting MaxPacketSize 64
[14274.167110] usb 6-1: FTDI USB Serial Device converter now attached to ttyUSB0
```
# Using the Kit - LFSTBEB845x #
## Without Reading the Online Manual ##
### Information in the Quick Start Guide ###
#### Steps ####
  1. Unpack the board. Verify package contents according to the kit website: freescale.com/sensortoolbox
  1. At freescale.com/sensortoolbox download the latest software version by clicking: Download Software
  1. Plug in the USB and turn the board on using the power switch. Run the Sensor Toolbox link on your desktop.
#### Comments ####
Same flyer as in the LFSTBUSB, except picture has been changed. And same comments for this as well. Why to provide a Quick Start Guide, if you are not going to provide anything else than a website address and why to make an operating system specific presumptions. And if the information is only available from the website, what happens in few years, is the url still valid, I doubt. As this is for prototyping and concepting we should have some kind of long-term solution for having the datasheets are related technical information in-hand. The CD/DVD or USB-stick would provide at least one way ticket for the years to come.

### Connecting to LFSTBUSB ###
#### Steps ####
  1. Make sure that LFSTBUSB is disconnected from laptop
  1. Select accelerometer DIP (MMA8451Q,MMA8452Q or MMA8453Q)
  1. Insert LFSTBEB845x to LFSTBUSB
  1. Insert DIP to LFSTBEB845x
### Comments ###
You need to be sure that you insert the DIP to LFSTBEB845x in right way. Note that there are ID's for the sockets on the PCB. Make sure that J1 and J2 are going to matching sockets on both PCBs. The DIP has been also shaped in that way that the outer sides will match, one side of the DIP is longer and should be pointing inwards. Another thing to be noted is that LFSTBEB845x has a lot of SMD components on the backside, so that has to be inserted first to the LFSTBUSB other wise you can damage them by accident. When the LFSTBEB845x and LFSTBUSB have been connected together you can connect the DIP more safer.

# Following the Quick Start Guide #
  1. opening the url to [freescale.com/sensortoolbox](http://www.freescale.com/sensortoolbox)
  1. clicking the blue _button_ which says: Download Software.
## Comments ##
  * This is totally useless for me.
  * I dont use Windows and the Download Software takes me to License Agreement page from which it will push SensorToolbox.exe to me..
  * I just wonder if I can find some PDF files or manuals from the website.
  * Maybe the SensorToolbox.exe will run with Wine..

# Documents #
  * [SENSORTOOLBOXFS](http://cache.freescale.com/files/sensors/doc/fact_sheet/SENSORTOOLBOXFS.pdf?fpsp=1): Sensor Toolbox
  * [LFSTBUSBACCQSG](http://cache.freescale.com/files/sensors/doc/user_guide/LFSTBUSBACCQSG.pdf?fpsp=1): Sensor Toolbox LFSTBUSB Accelerometer Interface Board Quick Start Guide
  * [BRSENSORS](http://cache.freescale.com/files/sensors/doc/fact_sheet/BRSENSORS.pdf?fpsp=1&WT_TYPE=Fact%20Sheets&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): Sensor Portfolio
  * [MMA845XQFS](http://cache.freescale.com/files/sensors/doc/fact_sheet/MMA845XQFS.pdf?fpsp=1&WT_TYPE=Fact%20Sheets&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): MMA8450Q low-power, low noise, pin-compatible 3-axis accelerometers
  * [MMA8451Q](http://cache.freescale.com/files/sensors/doc/data_sheet/MMA8451Q.pdf?fpsp=1&WT_TYPE=Data%20Sheets&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): Datasheet, 3-Axis, 14-bit/8-bit Digital Accelerometer
  * [MMA8452Q](http://cache.freescale.com/files/sensors/doc/data_sheet/MMA8452Q.pdf?fpsp=1&WT_TYPE=Data%20Sheets&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): Datasheet, 3-Axis, 12-bit/8-bit Digital Accelerometer
  * [MMA8453Q](http://cache.freescale.com/files/sensors/doc/data_sheet/MMA8453Q.pdf?fpsp=1&WT_TYPE=Data%20Sheets&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): Datasheet, 3-Axis, 10-bit/8-bit Digital Accelerometer
  * [LFSTBEB845x\_\_SCH](http://cache.freescale.com/files/sensors/doc/support_info/LFSTBEB845x__SCH.pdf?fpsp=1&WT_TYPE=Supporting%20Information&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): Schematics
  * [AN4075](http://cache.freescale.com/files/sensors/doc/app_note/AN4075.pdf?fpsp=1&WT_TYPE=Application%20Notes&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): How Many Bits are Enough? The Trade-off Between High Resolution and Low Power Using Oversampling Modes
  * [AN4069](http://cache.freescale.com/files/sensors/doc/app_note/AN4069.pdf?fpsp=1&WT_TYPE=Application%20Notes&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): Offset Calibration of the MMA8451, 2, 3Q
  * [AN4070](http://cache.freescale.com/files/sensors/doc/app_note/AN4070.pdf?fpsp=1&WT_TYPE=Application%20Notes&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): Motion and Freefall Detection Using the MMA8451, 2, 3Q
  * [AN4071](http://cache.freescale.com/files/sensors/doc/app_note/AN4071.pdf?fpsp=1&WT_TYPE=Application%20Notes&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): High Pass Filtered Data and Transient Detection Using the MMA8451, 2, 3Q
  * [AN4072](http://cache.freescale.com/files/sensors/doc/app_note/AN4072.pdf?fpsp=1&WT_TYPE=Application%20Notes&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): MMA8451, 2, 3Q Single/Double and Directional Tap Detection
  * [AN4073](http://cache.freescale.com/files/sensors/doc/app_note/AN4073.pdf?fpsp=1&WT_TYPE=Application%20Notes&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): Using the 32 Sample First In First Out (FIFO) in the MMA8451Q
  * [AN4074](http://cache.freescale.com/files/sensors/doc/app_note/AN4074.pdf?fpsp=1&WT_TYPE=Application%20Notes&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): Auto-Wake/Sleep Using the MMA8451, 2, 3Q
  * [AN4076](http://cache.freescale.com/files/sensors/doc/app_note/AN4076.pdf?fpsp=1&WT_TYPE=Application%20Notes&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): Data Manipulation and Basic Settings of the MMA8451, 2, 3Q
  * [AN4077](http://cache.freescale.com/files/sensors/doc/app_note/AN4077.pdf?fpsp=1&WT_TYPE=Application%20Notes&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation): MMA845xQ Design Checklist and Board Mounting Guidelines
# Links #
  * http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=LFSTBUSB

# Videos #
<a href='http://www.youtube.com/watch?feature=player_embedded&v=nP8U6Un95-U' target='_blank'><img src='http://img.youtube.com/vi/nP8U6Un95-U/0.jpg' width='425' height=344 /></a>

# Running SensorToolbox.exe in Linux #
```
 wine sensortoolbox.exe
```
Installation will go just fine. However the software is done with .NET so you will need to install it as well. Install Mono for Windows.

```
wget http://ftp.novell.com/pub/mono/archive/2.10.1/windows-installer/2/mono-2.10.1-gtksharp-2.12.10-win32-2.exe
```
I can get the SensorToolbox.exe running with following command, but the FTDI com port does not get detected. So the application stays in the first screen:
```
cd /home/user/.wine/drive_c/Program Files/Freescale/Sensor Toolbox/SensorToolbox_MFC
wine SensorToolbox.exe
```

# Comments #
  * Why Freescale does not use Qt (or some other cross-platform free programming framework) for doing their demo applications?
  * Why Freescale does not publish the protocol what they are using to communicate to the device?
  * If I would get the protocol definitions for the evaluation kit I could port this one..
# Analyzing content of the SensorToolbox #
```
$ ls /home/user/.wine/drive_c/Program Files/Freescale/Sensor Toolbox/MMA845xQ
Freescale.SASD.Communication.dll  msvcp90.dll
mesa.dll                          msvcr90.dll
MMA845x-FW-Bootloader.s19         msvcrt.dll
MMA845xQDL.exe                    NationalInstruments.Analysis.Standard.dll
MMA845xQDL.exe.config             NationalInstruments.Common.dll
MMA845xQ-DL-FW.s19                NationalInstruments.Common.Native.dll
MMA845xQNVMDL.exe                 NationalInstruments.UI.dll
MMA845xQNVMDL.exe.config          NationalInstruments.UI.Styles3D.dll
MMA845xQSW.exe                    NationalInstruments.UI.WindowsForms.dll
MMA845xQSW.exe.config             SensorToolbox_SerialProtocol2.0.DOC
```
## S19 files ##
Seems to be hex files for the embedded microcontroller.

## SensorToolbox\_SerialProtocol2.0.DOC ##
Could this file contain what is says? Lets see if it opens with LibreOffice. Hmm.. The document contains following header text "Freescale Internal Use Only" is this valid? The installer and the data is from Freescale website from anonymous download, but it seems to contain a lot of detailed information about the serial communication. At least this is a good start.

|115200 8 N 1 None|
|:----------------|

|Command|Host to MCU|MCU to Host|
|:------|:----------|:----------|
|Handshake|0x20 'h' 0x0D|0x20 'H' 0x0D|

### Comments ###
  * I just wonder if it would be possible to get ProtocolBridge.c file in the ProtocolBridge.mcp?

# Contacted Freescale's online chat #
And asked a lot of questions:
  * Is there Linux support available for the kit?
  * Why .NET is used for SensorToolkit and not a cross-platform framework like Qt?
  * Can I have an access to that ProtocolBridge.c class which is mentioned in the document.

The person who I discussed with promised to forward my questions to a 3rd person who might be able to answer to the questions. And then that person would answer me using email. Lets see how well that online support works for this kit. After all, I would not prefer to do any reverse engineering for it.
## Got a first reply ##
Got an email confirmation that they are working on to provide information about the Linux support, etc. A really positive thing that their chat support works and that they are co-operative :) ..not all the companies have this kind of superb support :p
I also provided an email reply to support the quick online chat with more detailed questions, as for me it seems that someone have done a deal with m$ and more likely they are not going to do SensorToolbox with Qt or Python. :P ..but lets see what they have to answer to my questions. And if they like the idea that I would create a cross-platform library for free and if they are willing to offer any help for it.


---

Thank you for contact me. The biggest reason why I was contacting you was that my RoadTest review  for Element14.com (http://www.element14.com/community/roadTests/1016) seemed to be dead-ended as of lacking support for Linux. The original idea was to use the usb interface board with my Chumby (which runs Linux on Freescale i.MX233), as I thought that as the USB interface board uses FTDI chip which is recognized by the Linux as serial port and the connection works to it. That I could just use it in a prototype project. For that I would need to know the serial protocol in more detail and it seemed that the doc file contained some information.

The protocol seems to work:
[SPACE](SPACE.md) [command+payload] [CR](CR.md)

I have tested that the USB Interface Board communicates with 'minicom -d /dev/ttyUSB0' on Linux:
Host to MCU:
[SPACE](SPACE.md) h [CR](CR.md)
And i will receive:
[SPACE](SPACE.md) H [CR](CR.md)

So the connection seems to work on Linux. The only missing thing is that there is the sample/demo application SensorToolbox.exe which does not run on Linux. My skills would enable me to implement a cross-platform Qt (or Python) demo/library application for you for free based on the information in the SensorToolbox\_SerialProtocol2.0.doc file. However as the protocol parsing and class wrapper might take some hours to write, I was thinking of if you would have had something to share. As for example if you could have had the source code for the sensortoolbox .net application I could have read how the protocol has been parsed for the accelerometers, which would have made my _job_ easier.. :) ..the reason why I am pushing this is that I know that all the Hacker Space's and Universities would be interested this kind of _plug-and-play_ hacker device which the SensorToolbox could be with cross-platform Qt or Python library for communication.

But then there is also one fact, in the public SensorToolbox Windows Installer you are providing that SensorToolbox\_SerialProtocol.2.0.doc file which has a header labeled "Freescale Internal Use Only". Is that document header just not up to date or have someone made a mistake by providing the file in there? I presume that as it is provided in the package I am allowed to read and use the information for producing the unofficial Linux support for the community. This way my review could contain something more than "- not recommended, does not support Linux". As I have seen the videos and read all the specs and it is obvious that your product is superb, but it is disabled by .NET application.

P.S If you want to follow the work in progress memo for the review feel free to do so http://code.google.com/p/quickanddirty/wiki/Review_Freescale_LFSTBUSB_LFSTBEB845x

---

EDIT: 9.5.2011: Added comments to the RoadTest page.
```
Juhapekka Piiroinen May 9, 2011 5:55 PM

When do I receive the part for review?

EDIT 6.4.2011: got it this monday, review to be done next weekend.
EDIT 18.4.2011: the review got postponed as i was participating a 24h coding competition. this is next on my TODO list.
EDIT 9.5.2011: the review is blocked due to missing support for Linux. The development kit supports only Microsoft Windows, althought there are no operating system requirements anywhere. And freescale does not reply to the support ticket SR 1-742776043, which was raised 22.4.2011. The current review can be seen http://code.google.com/p/quickanddirty/wiki/Review_Freescale_LFSTBUSB_LFSTBEB845x, But all in all the sensorkit is a good idea, but it has been implemented poorly with .NET. I just can not understand why they have not used any crossplatform framework like Qt. As the device itself is detected as serial port and can be used on other operating systems than Windows.
EDIT 9.5.2011: Unable to submit review with Ubuntu 11.04 + Chromium 11. The review post will get a result of "An unexpected error has occurred"

The end result with the Sensor Kit is that "it is a nice idea, but poor desktop software implementation is blocking the real usage". I would have wanted to use this in my robotics project with that usb-serial connectivity board. But for that I would have to implement my own 3rd party library, and as Freescale has not released any official documentation about the protocol and as they do not answer to the technical tickets in 48h as promised on their website, now it has been over three weeks..

http://www.element14.com/community/roadTests/1016#comment-5636
```

---

The full chat discussion with Freescale is available @ http://pastebin.com/N0P5iCKD.

---

8.6.2011 - got contacted by Freescale, they commented to http://www.element14.com/community/roadTests/1016#comment-6381.

"toniz Jun 8, 2011 7:19 PM (in response to Juhapekka Piiroinen)

Hello Juhapekka,
I am from Freescale, I can´t comment on the technical review, not my specialty area. But I did a check on the open tickets and sorry to say, but you did _not_ submit one to us. You misinterpreted the automatic logging of your online chatting with us as an open ticket. Sorry for that misunderstanding but the ticket was created by the system and instantly closed again with your submitted chat survey result to timestamp the interaction. We do strive for 48hrs and honestly can often but not always meet them, but we don´t let our customers knowingly wait for weeks, sorry for the misunderstanding.
I will create an empty ticket and write to you to let you reply back with your actual questions. Thanks for your interest in Freescale anyway. The rule says: complaining customers still have an interest, the silent ones are the ones that are lost. Hope we did not lose you ...
Cheers,
Toni"

Related to that I also published the "public information" email related to the discussions and support tickets: http://pastebin.com/3zkD48UF

So now there is yet another ticket raised by them, now it is with subject "RE: SR# 1-758008381 : Question about Freescale MMA845XQ Evaluation board"


---

My answer to his comment was:
"Juhapekka Piiroinen Jun 8, 2011 8:35 PM (in response to toniz)

I am still interested about your products. But you must know that I received following email with status "public information":  http://pastebin.com/3zkD48UF

And I got contacted by B16998 on 23.4.2011. But the email was with status "[x](x.md) Freescale Semiconductor Confidential Proprietary". So I will forward you the email asap. I also replied to that one, but there was no reply anymore.. The content of the email was that you do not support Linux at the moment and a promise to contact me further.. Thats why I was stating in my post "missing support for Linux".

But anyway, thanks for hearing me.  ..and I would be able to write my own library for the kit with Qt/C++ for you, if you will give the technical support and provide officially the technical protocol documentation of the communication over the serial bridge for the community as public information. As I have also noted in my wiki page, that there is actually one protocol file included in the .NET application installation package SensorToolbox\_SerialProtocol.2.0.doc, but it is labeled "Freescale Internal Use Only"."
So I forwarded the email discussion what I had with another freescale person.

---

2.8.2011 It seems that they have closed the element14 thread and freescale send an email that they are closing the ticket..

This is for you freescale:
**I will not recommend your products anymore to anyone, and this concerns all the future work related projects as well. If you do not have any motivation to support little men, why would you do any better job with corporate customers.**


---

Here is the thread from element14.com for future reference:
```
Juhapekka Piiroinen May 9, 2011 5:55 PM

When do I receive the part for review?
 
EDIT 6.4.2011: got it this monday, review to be done next weekend.
EDIT 18.4.2011: the review got postponed as i was participating a 24h coding competition. this is next on my TODO list.
EDIT 9.5.2011: the review is blocked due to missing support for Linux. The development kit supports only Microsoft Windows, althought there are no operating system requirements anywhere. And freescale does not reply to the support ticket SR 1-742776043, which was raised 22.4.2011. The current review can be seen  http://code.google.com/p/quickanddirty/wiki/Review_Freescale_LFSTBUSB_LFSTBEB845x, But all in all the sensorkit is a good idea, but it has been implemented poorly with .NET. I just can not understand why they have not used any crossplatform framework like Qt. As the device itself is detected as serial port and can be used on other operating systems than Windows.
EDIT 9.5.2011: Unable to submit review with Ubuntu 11.04 + Chromium 11. The review post will get a result of "An unexpected error has occurred"
 
The end result with the Sensor Kit is that "it is a nice idea, but poor desktop software implementation is blocking the real usage". I would have wanted to use this in my robotics project with that usb-serial connectivity board. But for that I would have to implement my own 3rd party library, and as Freescale has not released any official documentation about the protocol and as they do not answer to the technical tickets in 48h as promised on their website, now it has been over three weeks..
Like (0) Edit Reply
 
toniz Jun 8, 2011 7:19 PM (in response to Juhapekka Piiroinen)

Hello Juhapekka,
I am from Freescale, I can´t comment on the technical review, not my specialty area. But I did a check on the open tickets and sorry to say, but you did _not_ submit one to us. You misinterpreted the automatic logging of your online chatting with us as an open ticket. Sorry for that misunderstanding but the ticket was created by the system and instantly closed again with your submitted chat survey result to timestamp the interaction. We do strive for 48hrs and honestly can often but not always meet them, but we don´t let our customers knowingly wait for weeks, sorry for the misunderstanding.
I will create an empty ticket and write to you to let you reply back with your actual questions. Thanks for your interest in Freescale anyway. The rule says: complaining customers still have an interest, the silent ones are the ones that are lost. Hope we did not lose you ...
Cheers,
Toni
Like (0) Report Abuse Reply
 
Juhapekka Piiroinen Jun 8, 2011 8:35 PM (in response to toniz)

I am still interested about your products. But you must know that I received following email with status "public information":  http://pastebin.com/3zkD48UF
 
And I got contacted by B16998 on 23.4.2011. But the email was with status "[x] Freescale Semiconductor Confidential Proprietary". So I will forward you the email asap. I also replied to that one, but there was no reply anymore.. The content of the email was that you do not support Linux at the moment and a promise to contact me further.. Thats why I was stating in my post "missing support for Linux".
 
But anyway, thanks for hearing me.  ..and I would be able to write my own library for the kit with Qt/C++ for you, if you will give the technical support and provide officially the technical protocol documentation of the communication over the serial bridge for the community as public information. As I have also noted in my wiki page, that there is actually one protocol file included in the .NET application installation package SensorToolbox_SerialProtocol.2.0.doc, but it is labeled "Freescale Internal Use Only".
Like (0) Edit Reply
 
Juhapekka Piiroinen Jun 8, 2011 8:52 PM (in response to toniz)

To also answer to your sentence: "Sorry for that misunderstanding but the ticket was created by the system and instantly closed again with your submitted chat survey result to timestamp the interaction".
 
That seems to be a bug in your side that you are sending those ticket id's to the customers and then you are not sending any status updates on them. It would make sense to send status updates as "opened, closed" at least.. And as you can read from the pastebin which contains that message that there is nothing mentioning (or at least not clearly) that it is a "temporary measure" for yourself to track things up.. It would however make sense that you system would send the chatlog with that ticket to the customer and then state that "if you have anything to add etc" please reply to this email.. And I truly did understand that is a Service Request and when your colleague contacted me and promised to provide more information, what else could i expect? 
Like (0) Edit Reply
 
Juhapekka Piiroinen Jun 8, 2011 8:54 PM (in response to toniz)

> complaining customers still have an interest,
That is true and thats why I am also keen to help you to provide better experience for the Linux geeks as well. As majority of the homebrew robotics projects are running some sort of 32-bit processor with Embedded Linux on it.

```