#!/usr/bin/python
import structs
import os.path
import re

def parse(file):
		#debug = structs.debug()
		data = structs.data()
		styleTemp = ""
		if os.path.isfile(file):
				start = re.compile('^\..*', re.IGNORECASE)
				aalto = re.compile('.*{.*', re.IGNORECASE)
				f = open(file, "r")
				for i in f:
						if start.match(i):
								i = i.replace(' ','')
								if aalto.match(i):
										styleTemp2 = i.split('{')
										styleTemp = styleTemp2[0]
								else:
										styleTemp = i.replace('\n','')
								data.style[styleTemp.replace('.','')]=styleTemp.replace(".", "")

		return data

#print parse('style/style.css').style
