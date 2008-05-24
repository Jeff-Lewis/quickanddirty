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
		retval += "<? include('show.php'); ?>\n"
		retval += "<html>\n<head>\n<title>"+self._TITLE+"</title>"
		retval += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" media=\"all\" />"
		retval += "<meta http-equiv=\"refresh\" content=\"500;url="+self._ADDR+"\">"
		retval += "</head>\n<body>\n"
		retval += "<h1>"+self._TITLE+"</h1>\n"
		retval += "<h5>"+self._DESC+"</h5>\n"
		return retval

	def footer(self):
		retval = ""
		retval += "<br />"+self._FOOTER+"<br />\n"
		retval += "</body>\n</html>\n"
		return retval

	def content(self,feeds,db):
		retval = ""
		retval += "<table>\n"
		for line in feeds:
			retval += "<tr>\n"
			date,title,url,feedid = line
			feedname = db.read_feedname(feedid)
			feedurl = db.read_feedurl(feedid)
			retval += "<td><a target=\"_blank\" href=\"redirect.php?url="+url+"\">"+title+"</a></td><td>"
			retval += "<a target=\"_blank\"  href=\""+feedurl+"\">"
			retval += feedname
			retval += "</a>"
			retval += "</td><td>"+date+"</td>"
			retval += "<td><?=hitcounter('"+url+"'); ?></td>"
			retval += "\n</tr>\n"
		retval += "</table>\n"
		return retval
