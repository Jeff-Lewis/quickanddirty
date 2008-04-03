#!/usr/bin/python
##############################################################################
# This is a very quick and dirty portage updater script
##############################################################################
# This script is a part of gentoo portage www interface
##############################################################################
#    updateportage.py is a small Python script, which will read the config
#    file and then run emerge for the selected packages
#    Copyright (C) 2008  Juhapekka Piiroinen
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
# Contact: juhapekka.piiroinen@gmail.com
#############################################################################

import os,subprocess,sys,shutil
try:
	logfile = open("/tmp/lastupdatelog","w")
	print "Starting automated portage updating!"
	stdout = sys.stdout
	sys.stdout = logfile
	updatelist = open("/tmp/updatelist","r").readlines()
	for update in updatelist:
		update = update.strip()
		if len(update)>1:
			cmd = "emerge -q " + update
			print "Updating %s" % update
			p = subprocess.Popen(cmd,shell=True,stdout=sys.stdout)
			retcode = os.waitpid(p.pid,0)[0]
			if retcode!=0:
				print "Error updating %s" % update
			else:
				print "Updated %s" % update
	sys.stdout = stdout
	shutil.copyfile("/tmp/updatelist","/tmp/updatelist.last")
	f = open("/tmp/updatelist","w")
	f.write("")
	f.close()
	os.chmod("/tmp/updatelist",0777)
	print "Ending automated portage updating."
	logfile.close()
except IOError:
	print "updatePortage.py received IOError"

