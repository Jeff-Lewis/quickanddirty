# Introduction #
This script presumes that you have sendmail installed and configured for example for gmail. I suggest that you define the cronjob for example for once per week and use gmail account for the storage, the 6,5Gb are enough for a while. ;)

# Steps #
  1. Create script for backuping mysql
```
#!/bin/sh
mysqldump --opt --user="username" --password="password" --all-databases > backup.mysql
```
  1. Create script which will send the backup to gmail for archiving:
```
#!/usr/bin/python
import smtplib,time,os
from email.MIMEMultipart import MIMEMultipart
from email.MIMEBase import MIMEBase
from email.MIMEText import MIMEText
from email.Utils import COMMASPACE, formatdate
from email import Encoders

def SendMsg(to, subject, text, files=[]):
    from = "Backup Tyokalu <youremail@yourdomain>"
    msg = MIMEMultipart()
    msg['From'] = from
    msg['To'] = COMMASPACE.join(to)
    msg['Date'] = formatdate(localtime=True)
    msg['Subject'] = subject
    msg.attach( MIMEText(text) )
    for file in files:
        part = MIMEBase('application', "octet-stream")
        part.set_payload( open(file,"rb").read() )
        Encoders.encode_base64(part)
        part.add_header('Content-Disposition', 'attachment; filename="%s"'
                       % os.path.basename(file))
        msg.attach(part)
    smtp = smtplib.SMTP("localhost")
    smtp.sendmail(from, to, msg.as_string() )
    smtp.close()
SendMsg(["yourarchive@gmail134.com"],"MySQL backup - %s" % time.strftime("%D %H:%M:%S",time.$
os.remove("backup.mysql")
```
  1. Write a script for crontab:
```
#!/bin/sh
cd /the_path_for_the_scripts
./backupmysql.sh
./sendmail.py
```
  1. Give execution right to scripts and write the cronjob