#!/usr/bin/python
##############################################################################
#    rss_email.py is a part of qad_rssreader
#    Copyright (C) 2008  Juhapekka Piiroinen & Petri Ilmarinen
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#############################################################################
# Version 0.01 Not to be used anywhere.. totally unfinished!!!!
############################################################################
import imaplib
import smtplib
import sys, MimeWriter, base64, StringIO

class emailbot(object):
	def __init__(self,username,password,imap="imap.gmail.com",imapport=993,smtp="smtp.googlemail.com",smtpport=587):
		self.username = username
		self.password = password
		self.imap = imap
		self.smtp = smtp
		self.imapport = imapport
		self.smtpport = smtpport
		
	def getValue(self,title,data):
		i = data.find(title)
		e = data.find("\n",i)
		value = data[i:e].replace(title,"").strip()
		return value
	def markAsRead(self,item,box):
		box.store(item, '+FLAGS', '\\Seen')
	def markAsUnRead(self,item,box):
		box.store(item, '-FLAGS', '\\Seen')
	def read(self):
		box = imaplib.IMAP4_SSL(self.imap,self.imapport)
		box.login(self.username,self.password)
		box.select(readonly=1)
		result,data = box.search(None,"(UNSEEN)")
		if result=="OK":
			data = data[0].split(" ")
			for item in data:
				if item:
					result,msg = box.fetch(item,"(BODY[HEADER.FIELDS (FROM SUBJECT)])")
					if result=="OK":
						msg = msg[0][1].strip()
						sender = self.getValue("From:",msg).split("<")[1].replace(">","")
						subject = self.getValue("Subject:",msg)
						self.runcmd(sender,subject)
						
		box.close()
		box.logout()
		
	def runcmd(self,sender,subject):
		if (subject=="register"):
			self.send(sender,"account registered","currently not implemented")
		if (subject=="unregister"):
			self.send(sender,"account unregistered","currently not implemented")
		if (subject=="when"):
			self.send(sender,"changed timing","currently not implemented")
		if (subject=="usage"):
			self.send(sender,"usage is here","register,unregister,when,usage")
		if (subject=="read"):
			self.send(sender,"Todays 100 latest news",self.content)
		if (subject=="users"):
			self.send(sender,"Registered users","not implemented. only for admin")

	def send(self,receiver,subject,body="no msg"):
		msg = StringIO.StringIO()
		writer = MimeWriter.MimeWriter(msg)
		writer.addheader('From', self.username)
		writer.addheader('To',receiver)
		writer.addheader('Subject', subject)
		writer.startmultipartbody('mixed')

		# start off with a text/plain part
		part = writer.nextpart()
		body = part.startbody('text/plain')
		body.write(body)

		# now add an image part
		#part = writer.nextpart()
		#part.addheader('Content-Transfer-Encoding', 'base64')
		#body = part.startbody('image/jpeg')
		#base64.encode(open('kitten.jpg', 'rb'), body)
		writer.lastpart()
		server = smtplib.SMTP(self.smtp,self.smtpport)
		server.set_debuglevel(1)
		server.ehlo()
		server.starttls()
		server.ehlo()
		server.login(self.username,self.password)
		server.sendmail(self.username, receiver, msg.getvalue())
		server.quit()
		
	def execute(self,feeds,db):
		self.content = ""
		for line in feeds:
			date,title,url,feedid = line
			feedname = db.read_feedname(feedid)
			feedurl = db.read_feedurl(feedid)
			line.append(feedname)
			line.append(feedurl)
			self.content += "; ".join(line)
		
		self.read()

