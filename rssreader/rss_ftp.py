#!/usr/bin/python
import ftplib

class ftp_upload(object):
	def __init__(self,username,password,server,path,filename="index.html"):
		ftp = ftplib.FTP(server)
		ftp.login(username,password)
		f = open(filename,"rb")
		ftp.cwd(path)
		ftp.storbinary("STOR "+filename,f)
		f.close()
		ftp.quit()
	def __del__(self):
		pass
