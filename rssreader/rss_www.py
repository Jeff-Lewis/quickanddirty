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
	def __init__(self,filename="index.php",stats=False):
		self.c = rss_config.Config()
		self.f = open(filename,"w")
		self.conf = self.c.read_conf()
		self.description= self.c.get("HTML","description")
		self.title = self.c.get("HTML","title")
		self.db = rss_db.db_connection(self.conf[0])
		self.stats = stats
		
	def format(self,data):
		return data.encode("latin1","ignore")
	def write(self,line):
		self.f.write(self.format(line))
	
	def rss_f(self,msg):
		return msg.replace("&","").replace("<","").replace(">","")
		
	def rss_header(self):
		self.write("<?xml version=\"1.0\"?>")
		self.write("<rss version=\"2.0\">\n")
		self.write("<channel>\n")
		self.write("<title>"+self.title+"</title>\n")
		self.write("<description>"+self.description+"</description>\n")
	
	def rss(self,feeds):
		self.rss_header()
		for line in feeds:
			self.write("<item>\n")
			date,title,url,feedid = line
			self.write("<title>"+self.rss_f(title)+"</title>\n")
			self.write("<link>"+self.rss_f(url)+"</link>\n")
			self.write("<pubDate>"+date+"</pubDate>\n")
			self.write("</item>\n")
		self.rss_footer()
		
	def rss_footer(self):
		self.write("</channel>")
		self.write("</rss>")
		
	def html_header(self):
		self.write("<? include('show.php'); ?>\n");
		self.write("<html>\n<head>\n<title>"+self.title+"</title>")
		self.write("<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" media=\"all\" />")
		self.write("<meta http-equiv=\"refresh\" content=\"500;url=http://www.feed.fi\">")
		self.write("</head>\n<body>\n")
		self.write("<h1>"+self.title+"</h1>\n")
		self.write("<h5>"+self.description+"</h5>\n")
		
	def html_footer(self):
		self.write("<br />&copy; 2008 Juhapekka Piiroinen & Petri Ilmarinen - <a href=\"http://code.google.com/p/quickanddirty\">QuickAndDirty</a> -project\n")
		self.write("</body>\n</html>\n")
		
	def html(self,feeds,images=False):
		self.html_header()
		if (self.stats):
			self.write("<h2>Total topics in database: "+str(len(feeds))+"</h2>")
		self.write("<table>\n")
		for line in feeds:
			self.write("<tr>\n")
			date,title,url,feedid = line
			image = False
			if (images):
				image = self.db.read_feedimage(feedid)
			feedname = self.db.read_feedname(feedid)
			feedurl = self.db.read_feedurl(feedid)
			if (image):
				self.write("<td><a href=\"redirect.php?url="+url+"\">"+title+"</a></td><td>")
				self.write("<a href=\""+feedurl+"\">")
				self.write("<img src=\""+image+"\" alt=\""+feedname+"\" />")
				self.write("</a>")
				self.write("</td><td>"+date+"</td>")
			else:
				self.write("<td><a href=\"redirect.php?url="+url+"\">"+title+"</a></td><td>")
				self.write("<a href=\""+feedurl+"\">")
				self.write(feedname)
				self.write("</a>")
				self.write("</td><td>"+date+"</td>")
			self.write("<td><?=hitcounter('"+url+"'); ?></td>");
			self.write("\n</tr>\n")
		self.write("</table>\n")
		self.html_footer()
			
	def __del__(self):
		self.db.close()
		self.f.close()
