#!/usr/bin/python
# -*- coding: utf-8 -*-
##############################################################################
# This is a very quick and dirty rss reader with sqlite support
##############################################################################
# This script will read rss feeds
##############################################################################
#    dbus-client.py is a script a prototype script for dbus client
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
# http://dbus.freedesktop.org/doc/dbus-python/doc/tutorial.html#data-types
import sys
from traceback import print_exc
import dbus

def main():
    bus = dbus.SessionBus()

    try:
        remote_object = bus.get_object("fi.feed.RssReaderService","/RssReader")
    except dbus.DBusException:
        print_exc()
        sys.exit(1)

    iface = dbus.Interface(remote_object, "fi.feed.RssReaderInterface")

    news = iface.GetNews()

    for item in news:
    	print item	

if __name__ == '__main__':
    main()
