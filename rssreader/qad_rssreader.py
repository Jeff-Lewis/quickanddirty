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

class Config(object):
	def __init__(self, conf_path):
		self.conf_path = conf_path
		self.conf = ConfigParser.ConfigParser()
		self.conf.readfp(open(self.conf_path))
	
	def read_conf(self):
		self.a = self.conf.get('DATABASE','path')
		self.b = self.conf.get('DATABASE','config_table')
		self.c = self.conf.get('DATABASE','feed_table')
		self.d = self.conf.get('DATABASE','cycle')
		self.d = int(self.d)

		return self.a, self.b, self.c, self.d
		
class db_connection(object):
	def __init__(self,db_address):
		#self.conn = sqlite.connect("rssfeed.db")
		self.conn = sqlite.connect(db_address)
		self.cursor = self.conn.cursor()

	def read_table(self,table):
		
		self.query = "select feed from "+table
		
		self.cursor.execute(self.query)
		self.answer = self.cursor.fetchall()
		
		return self.answer
	
	def read_table2(self):
		self.cursor.execute("select link from feeds")
		self.answer = self.cursor.fetchall()
		return self.answer
	
	def write_table(self,title,link):
		self.cursor.execute("select * from feeds where title = ? and link = ?",(title,link))
		self.aa = self.cursor.fetchone()
		try:
			if len(self.aa) > 0: pass
			else:
				self.cursor.execute("insert into feeds values (date('now'),?,?)",(title,link))
				self.conn.commit()
		except TypeError:
			self.cursor.execute("insert into feeds values (date('now'),?,?)",(title,link))
			self.conn.commit()

	def write_stamp(self,title,link):
		self.cursor.execute("update set time = date('now') where title = ?",(title,))
		self.conn.commit()

def f(data):
	return data.encode("latin1","ignore")

def rss_feed(feed):
	d = feedparser.parse(feed)
	feeds = db.read_table2()
	for entry in d.entries:
		
		if entry.link in feeds:
			db.write_stamp(entry.title,entry.link)
		else:
			db.write_table(entry.title,entry.link)

if __name__ == "__main__":
	#do first fork
	try: 
        	pid = os.fork() 
        	if pid > 0:
        	    # exit first parent
        	    sys.exit(0) 
    	except OSError, e: 
        	print >>sys.stderr, "fork #1 failed: %d (%s)" % (e.errno, e.strerror) 
        	sys.exit(1)
	
	os.chdir("/") 
	os.setsid() 
	os.umask(0) 

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
	while 1:
		try:
			config_file = sys.argv[1]
		except IndexError:
			config_file = "./rss.cnf"

		c = Config(config_file)
		db_things = c.read_conf()
	
		db = db_connection(db_things[0])
		feeds = db.read_table(db_things[1])
	
		for feed in feeds:
			rss_feed(feed[0])
		
		time.sleep(db_things[3])
		#rss_feed("http://www.iltalehti.fi/rss/rss.xml")

