#!/usr/bin/python
##############################################################################
# This is a very quick and dirty rss reader with sqlite support
##############################################################################
# This script will read rss feeds
##############################################################################
#    rssreader.py is a script which reads rss feeds
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
# Contact: 	juhapekka.piiroinen@gmail.com
# 		petri.ilmarinen@gmail.com
#############################################################################
# Release info for version 0.1
# rssreader must have in the database "feeds" -table
# database path must be absolute
# configuration file passed as parameter must also be absolute
############################################################################
import feedparser,sys,ConfigParser,os,time
from sqlite3 import dbapi2 as sqlite
import rss_config
import rss_db

_DEBUG = False

def p(msg):
	if (_DEBUG):
		print msg
		

def f(data):
	return data.encode("latin1","ignore")

def rss_feed(feed):
	d = feedparser.parse(feed)
	db.write_stamp_feed(feed)
	feeds = db.read_table2()
	p("Total items: "+str(len(feeds)))
	for entry in d.entries:
		#print entry.link in feeds
		if not entry.link in feeds:
			#print "Updating timestamp for "+entry.link
			#	db.write_stamp_news(entry.title,entry.link)
			#else:
			p("Adding new link "+entry.link)
			db.write_table(entry.title,entry.link)

if __name__ == "__main__":
	if not _DEBUG:
		#do first fork
		try: 
        		pid = os.fork() 
	        	if pid > 0:
	        	    # exit first parent
        		    sys.exit(0) 
	    	except OSError, e: 
        		print >>sys.stderr, "fork #1 failed: %d (%s)" % (e.errno, e.strerror) 
	        	sys.exit(1)
	
		#os.chdir("/") 
		#os.setsid() 
		#os.umask(0) 

	    	# do second fork
    		try: 
	        	pid = os.fork() 
        		if pid > 0:
            			# exit from second parent, print eventual PID before
            			print "Daemon PID %d" % pid 
	            		sys.exit(0) 
    		except OSError, e: 
	        	print >>sys.stderr, "fork #2 failed: %d (%s)" % (e.errno, e.strerror) 
        		sys.exit(1) 
	p("Starting qad_rssreader..")
	while 1:

		c = rss_config.Config()
		db_things = c.read_conf()
	
		db = rss_db.db_connection(db_things[0])
		feeds = db.read_feeds(db_things[1])
	
		for feed in feeds:
			p("")
			p("Reading feed: "+feed[1])
			rss_feed(feed[0])
		p("Sleeping for "+str(db_things[3])+" seconds")
		time.sleep(db_things[3])
