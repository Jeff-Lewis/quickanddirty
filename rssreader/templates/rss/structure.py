#!/usr/bin/python
import rss_db


class layout:
	def init(self,title,addr,desc,footer):
		self._TITLE = title
		self._ADDR = addr
		self._DESC = desc
		self._FOOTER = footer
	
	def __init__(self):
		self.init("default title","default addr","default desc","default footer")
		
	def header(self):
		retval = ""
		retval += "<rss version=\"2.0\">\n"
		retval += "<channel>\n"
		retval += "<title>"+self._TITLE+"</title>\n"
		retval += "<description>"+self._DESC+"</description>\n"
		return retval

	def footer(self):
		retval = ""
		retval += "</channel>"
		retval += "</rss>"
		return retval

	def content(self,feeds,db):
		retval = ""
		for line in feeds:
			retval += "<item>\n"
			date,title,url,feedid = line
			retval += "<title>"+title+"</title>\n"
			retval += "<link>"+url+"</link>\n"
			retval += "<pubDate>"+date+"</pubDate>\n"
			retval += "</item>\n"
		return retval
