#!/usr/bin/python
import rss_db
import urllib2
import os

class layout:
	def init(self,title,addr,desc,footer):
		self._TITLE = title
		self._ADDR = addr
		self._DESC = desc
		self._FOOTER = footer
		self._IMAGES = []
	
	def __init__(self):
		self.init("default title","default addr","default desc","default footer")
	
	def download(self,url,filename):
		if (os.path.exists(filename)):
			return
		f = urllib2.urlopen(url)
		fout = open(filename,"wb")
		fout.write(f.read())
		fout.close()
		f.close()
		
	def name(self):
		return "Default HTML Document"
		
	def get_refresh(self):
		return "<meta http-equiv=\"refresh\" content=\"500;url="+self._ADDR+"\">"
	
	def get_menu(self,db):
		feeds = db.read_allfeeds()
		retval = ""
		retval += "<a class=\"info\" href=\"http://www.feed.fi\" alt=\"Home\"><img border=\"0\" src=\"home.png\" alt=\"home\" width=\"16\" height=\"16\" /><span>View 100 latest topics</span></a><br />"
		for item in feeds:
			try:
				img = item[3].lower().replace(" ","") + ".ico"
				if (item[4]):
					self.download(url=item[4],filename="tmp/"+img)
				retval += "<a class=\"info\" href=\""+item[3].lower().replace(" ","")+".php\" alt=\""+item[3]+"\"><img border=\"0\" src=\""+img+"\" alt=\""+item[3]+"\" width=\"16\" height=\"16\" /><span>"+item[3]+"</span></a><br />"
				self._IMAGES.append("tmp/"+img)
			except TypeError:
				retval += "<a class=\"info\" href=\""+item[3].lower().replace(" ","")+".php\">"+item[3]+"</a><br />"
		return retval
		
	def header(self,db=None):
		retval = ""
		retval += "<? include('show.php'); ?>\n"
		retval += "<html>\n<head>\n<title>"+self._TITLE+"</title>"
		retval += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" media=\"all\" />"
		retval += self.get_refresh()
		retval += "</head>\n<body>\n"
		retval += "<div id=\"main\">\n<div id=\"left\">"
		if db:
			retval += self.get_menu(db)
		retval += "</div>\n<div id=\"right\">"
		return retval
	
	def footer(self):
		retval = "</div></div>"
		retval += "<!-- "+self._FOOTER+" -->\n"
		retval += "\n</body>\n</html>\n"
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
		
	def files(self):
		retval = []
		retval.append("templates/default/show.php")
		#retval.append("templates/default/redirect.php")
		retval.append("templates/default/style.css")
		retval.append("templates/default/home.png")
		for image in self._IMAGES:
			retval.append(image)
		return retval

	def filename(self):
		return "index.php"
