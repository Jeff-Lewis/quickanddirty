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
# Version 0.2
############################################################################
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
		self.write("<html>\n<head>\n<title>qad_rssreader</title>")
		self.write("<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" media=\"all\" />")
		self.write("</head>\n<body>\n")
		self.write("<h1>qad_rssreader</h1>\n")
		
	def html_footer(self):
		self.write("<br />&copy; 2008 Juhapekka Piiroinen & Petri Ilmarinen - <a href=\"http://code.google.com/p/quickanddirty\">QuickAndDirty</a> -project\n")
		self.write("</body>\n</html>\n")
		
	def html(self):
		feeds = self.db.read_news()
		self.html_header()
		self.write("<table>\n")
		for line in feeds:
			self.write("<tr>\n")
			date,title,url,feedid = line
			image = self.db.read_feedimage(feedid)
			feedname = self.db.read_feedname(feedid)
			if (image):
				self.write("<td>"+date+"</td><td><img src=\""+image+"\" alt=\""+feedname+"\" /></td><td><a href=\""+url+"\">"+title+"</a></td>")
			else:
				self.write("<td>"+date+"</td><td>"+feedname+"</td><td><a href=\""+url+"\">"+title+"</a></td>")
			self.write("</tr>\n")
		self.write("</table>\n")
		self.html_footer()
			
	def __del__(self):
		self.db.close()
		self.f.close()
