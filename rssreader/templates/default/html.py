#!/usr/bin/python

global _TITLE
global _ADDR
global _DESC
global _FOOTER

def init(title,addr,desc,footer):
	global _TITLE,_ADDR,_DESC,_FOOTER
	_TITLE = title
	_ADDR = addr
	_DESC = desc
	_FOOTER = footer

def header():
	retval = ""
	retval += "<? include('show.php'); ?>\n"
	retval += "<html>\n<head>\n<title>"+_TITLE+"</title>"
	retval += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" media=\"all\" />"
	retval += "<meta http-equiv=\"refresh\" content=\"500;url="+_ADDR+"\">"
	retval += "</head>\n<body>\n"
	retval += "<h1>"+_TITLE+"</h1>\n"
	retval += "<h5>"+_DESC+"</h5>\n"
	return retval

def footer():
	retval = ""
	retval += "<br />"+_FOOTER+"<br />\n"
	retval += "</body>\n</html>\n"
	return retval

def content(feeds,db):
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
