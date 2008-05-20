#!/usr/bin/python
##############################################################################
#    qad_rssreader_add.py is a part of qad_rssreader
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
import rss_db
import sys

args = sys.argv

if len(args)>2:
	db = rss_db.db_connection()
	db.insert_new_feed(feedurl=args[1],title=args[2])
	db.close()
	print "A new feed is added!"
else:
	print "USAGE: ./qad_rssreader_add.py url title"
