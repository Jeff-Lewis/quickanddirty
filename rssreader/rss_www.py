#!/usr/bin/python
##############################################################################
#    rss_www.py is a part of qad_rssreader
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
# Version 0.2
############################################################################
import rss_db,rss_config
from templates.default import *

class document(object):
	def __init__(self,filename="index.php"):
		self.template = structure.layout()
		self.c = rss_config.Config()
		self.f = open(filename,"w")
		self.db = rss_db.db_connection(self.c.get("DATABASE","path"))
		self.template.init(title=self.c.get("HTML","title"),desc=self.c.get("HTML","description"),addr=self.c.get("HTML","baseaddress"),footer=self.c.get("HTML","footer"))
		
	def format(self,data):
		return data.encode("latin1","ignore")
	def write(self,line):
		self.f.write(self.format(line))
		
	def generate(self,feeds):
		self.write(self.template.header())
		self.write(self.template.content(feeds,self.db))
		self.write(self.template.footer())
			
	def __del__(self):
		self.db.close()
		self.f.close()
