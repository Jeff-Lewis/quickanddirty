#!/usr/bin/python
##############################################################################
#    rss_www.py is a part of qad_rssreader
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
import rss_db,rss_config
import ftplib

class html_generator(object):
	def __init__(self,filename="index.html"):
		self.c = rss_config.Config()
		self.f = open(filename,"w")
		self.conf = self.c.read_conf()
		self.db = rss_db.db_connection(self.conf[0])
	def format(self,data):
		return data.encode("latin1","ignore")
	def write(self,line):
		self.f.write(self.format(line))
		
	def html_header(self):
		self.write("<html>\n<head>\n<title>qad_rssreader</title>\n</head>\n<body>")
		
	def html_footer(self):
		self.write("</body>\n</html>")
		
	def html(self):
		feeds = self.db.read_news()
		self.html_header()
		self.write("<table>")
		for line in feeds:
			self.write("<tr>")
			date,title,url,feedid = line
			feedname = self.db.read_feedname(feedid)
			self.write("<td>"+date+"</td><td>"+feedname+"</td><td><a href=\""+url+"\">"+title+"</a></td>")
			self.write("</tr>")
		self.write("</table>")
		self.html_footer()
			
	def __del__(self):
		self.db.close()
		self.f.close()
