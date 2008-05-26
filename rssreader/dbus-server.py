#!/usr/bin/python
# -*- coding: utf-8 -*-
##############################################################################
# This is a very quick and dirty rss reader with sqlite support
##############################################################################
# This script will read rss feeds
##############################################################################
#    dbus-server.py is a script a prototype script for dbus server
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
#http://dbus.freedesktop.org/doc/dbus-python/doc/tutorial.html#data-types
import gobject

import dbus
import dbus.service
import dbus.mainloop.glib

class RssReader(dbus.service.Object):

    @dbus.service.method("fi.feed.RssReaderInterface",
                         in_signature='', out_signature='v')
    def GetNews(self):
    	print "GetNews called!"
    	import rss_db
	db = rss_db.db_connection()
	news = db.read_newslinks()
        return news

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    session_bus = dbus.SessionBus()
    name = dbus.service.BusName("fi.feed.RssReaderService", session_bus)
    object = RssReader(session_bus, '/RssReader')

    mainloop = gobject.MainLoop()
    mainloop.run()
