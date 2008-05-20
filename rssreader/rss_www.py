#!/usr/bin/python
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
	def html(self):
		feeds = self.db.read_news()
		self.write("<table>")
		for line in feeds:
			self.write("<tr>")
			date,title,url = line
			self.write("<td>"+date+"</td><td><a href=\""+url+"\">"+title+"</a></td>")
			self.write("</tr>")
		self.write("</table>")
			
	def __del__(self):
		self.db.close()
		self.f.close()
