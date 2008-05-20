#!/usr/bin/python
##############################################################################
#    rss_db.py is a part of qad_rssreader
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
from sqlite3 import dbapi2 as sqlite
import os

class db_connection(object):
	def __init__(self,db_address="qad_rssreader.db"):
		if (os.path.exists(db_address)):
			self.conn = sqlite.connect(db_address)
			self.cursor = self.conn.cursor()
		else:
			self.conn = sqlite.connect(db_address)
			self.cursor = self.conn.cursor()
			self.default_db()

	def __del__(self):
		self.close()
		
	def default_db(self):
		self.cursor.execute("create table config (feed,time,title)")
		self.cursor.execute("create table feeds (time,title,link,feedid)")
#		self.insert_new_feed()
		self.insert_new_feed(feedurl="http://rss.slashdot.org/Slashdot/slashdot",title="Slashdot")
		self.insert_new_feed(feedurl="http://feeds.feedburner.com/ItechNewsNet",title="iTech News Net")
		self.insert_new_feed(feedurl="http://www.linuxdevices.com/backend/headlines.rss",title="Linux Devices")
		
	def close(self):
		self.conn.commit()
		self.cursor.close()
		
	def insert_new_feed(self,feedurl="http://www.iltalehti.fi/rss/rss.xml",title="Iltalehti"):
		self.cursor.execute("insert into config(feed,time,title) values ('"+feedurl+"',date('now'),'"+title+"')")
		
	def read_feeds(self,table):
		
		self.query = "select feed,title,rowid from "+table
		
		self.cursor.execute(self.query)
		self.answer = self.cursor.fetchall()
		
		return self.answer
	
	def read_feedname(self,feedid):
		self.cursor.execute("select title from config where rowid="+str(feedid))
		return self.cursor.fetchone()[0]
		
	def read_newslinks(self):
		self.cursor.execute("select link from feeds")
		self.answer2 = self.cursor.fetchall()
		self.answer = []
		for item in self.answer2:
			self.answer.append(item[0])
		return self.answer
		
	def read_news(self):
		self.cursor.execute("select * from feeds order by time")
		self.answer = self.cursor.fetchall()
		return self.answer		
	
	def write_table(self,title,link,feedid):
		self.cursor.execute("select * from feeds where title = ? and link = ?",(title,link))
		self.aa = self.cursor.fetchone()
		try:
			if len(self.aa) > 0: pass
			else:
				self.cursor.execute("insert into feeds values (date('now'),?,?,?)",(title,link,feedid))
				self.conn.commit()
		except TypeError:
			self.cursor.execute("insert into feeds values (date('now'),?,?,?)",(title,link,feedid))
			self.conn.commit()

	def write_stamp_feed(self,feed):
		self.cursor.execute("update config set time=date('now') where feed=?",(feed,))
		self.conn.commit()
		
	def write_stamp_news(self,title,link):
		self.cursor.execute("update feeds set time=date('now') where title=?",(title,))
		self.conn.commit()
