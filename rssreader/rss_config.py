#!/usr/bin/python
import ConfigParser
import rss_db
import os

class Config(object):
	def __init__(self, conf_path="qad_rssreader.conf"):
		self.conf_path = conf_path
		self.conf = ConfigParser.ConfigParser()
		try: 
			self.conf.readfp(open(self.conf_path))
		except IOError:
			self.default_conf()
	
	def get(self,section,key):
		return self.conf.get(section,key)
		
	def default_conf(self):
		self.conf.add_section("DATABASE")
		self.conf.set("DATABASE","path",os.getcwd()+os.sep+"qad_rssreader.db")
		self.conf.set("DATABASE","config_table","config")
		self.conf.set("DATABASE","feed_table","feeds")
		self.conf.set("DATABASE","cycle","30")
		self.conf.add_section("FTP")
		self.conf.set("FTP","path","/")
		self.conf.set("FTP","username","your_username")
		self.conf.set("FTP","password","your_password")
		self.conf.set("FTP","server","your_server")
		self.conf.add_section("HTML")
		self.conf.set("HTML","filename","index.html")
		f = open(self.conf_path,"w")
		self.conf.write(f)
		f.close()
		db = rss_db.db_connection(self.conf.get("DATABASE","path"))
		db.default_db()
		db.close()
		
	
	def read_conf(self):
		self.a = self.conf.get('DATABASE','path')
		self.b = self.conf.get('DATABASE','config_table')
		self.c = self.conf.get('DATABASE','feed_table')
		self.d = self.conf.get('DATABASE','cycle')
		self.d = int(self.d)

		return self.a, self.b, self.c, self.d
