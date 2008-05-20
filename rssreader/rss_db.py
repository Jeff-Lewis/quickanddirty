#!/usr/bin/python
from sqlite3 import dbapi2 as sqlite

class db_connection(object):
	def __init__(self,db_address="qad_rssreader.db"):
		self.conn = sqlite.connect(db_address)
		self.cursor = self.conn.cursor()

	def __del__(self):
		self.close()
		
	def default_db(self):
		self.cursor.execute("create table config (feed,time,title)")
		self.cursor.execute("create table feeds (time,title,link)")
		self.insert_new_feed()
		
	def close(self):
		self.conn.commit()
		self.cursor.close()
		
	def insert_new_feed(self,feedurl="http://www.iltalehti.fi/rss/rss.xml",title="Iltalehti"):
		self.cursor.execute("insert into config(feed,time,title) values ('"+feedurl+"',date('now'),'"+title+"')")
		
	def read_feeds(self,table):
		
		self.query = "select feed,title from "+table
		
		self.cursor.execute(self.query)
		self.answer = self.cursor.fetchall()
		
		return self.answer
	
	def read_table2(self):
		self.cursor.execute("select link from feeds")
		self.answer2 = self.cursor.fetchall()
		self.answer = []
		for item in self.answer2:
			self.answer.append(item[0])
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

	def write_stamp_feed(self,feed):
		self.cursor.execute("update config set time=date('now') where feed=?",(feed,))
		self.conn.commit()
		
	def write_stamp_news(self,title,link):
		self.cursor.execute("update feeds set time=date('now') where title=?",(title,))
		self.conn.commit()
