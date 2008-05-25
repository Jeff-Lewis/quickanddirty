#!/usr/bin/python
##############################################################################
#    rss_ftp.py is a part of qad_rssreader
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
# Version 0.2
############################################################################
import ftplib
import os

class ftp_upload(object):
	def __init__(self,username,password,server,path):
		self.ftp = ftplib.FTP(server)
		try:
			self.ftp.login(username,password)
		except EOFError,e:
			print "Error: %s" % str(e)
		self.ftp.cwd(path)
		
	def upload(self,filename):
		f = open(filename,"rb")
		try:
			self.ftp.storbinary("STOR "+os.path.basename(filename),f)
		except EOFError,e:
			print "Error: %s" % str(e)
		f.close()
		
	def __del__(self):
		self.ftp.quit()
