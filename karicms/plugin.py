#!/usr/bin/env python
import re
import os
import imp

def add_plugin(line, data):
		type = ""
		page = ""
		#remove []-characters at begining and end, remove spaces and split to all
		all = line.strip('[]').replace(' ','').split(',')

		#matc type=
		typeRe = re.compile('type=.*', re.IGNORECASE)
		params = {}
		debug=1
		for i in all:
				if typeRe.match(i):
						type = i.replace("type=", "")
				else:
						temp = i.split('=')
						if len(temp) == 1:
								temp.append("")
						#add all other tthan type= to parameters
						params[temp[0]] = temp[1]
		
		#recode all below to be more clean, smart, elegant, and less quick and dirty ;)
		#add dynamic module loading
		if not os.path.isdir(data.settings['PLUGIN_DIR']):
				data.errors.append("No such directory '" + data.settings['PLUGIN_DIR'] + "'")
		else:
				#mod_name,file_ext = os.path.splitext(os.path.split()[-1])
				if os.path.isfile(data.settings['PLUGIN_DIR'] + type + '.py') or os.path.isfile(data.settings['PLUGIN_DIR'] + type + 'pyc'):
						page = page + load_from_file(data.settings['PLUGIN_DIR'] + type + '.py',data,params)
				else:
						data.errors.append("No such plugin '" + type + ".py(c)'")
		return page


def load_from_file(filepath,data,params):
		class_inst = None
		expected_class = 'main'
		mod_name,file_ext = os.path.splitext(os.path.split(filepath)[-1])

		if file_ext.lower() == '.py':
				py_mod = imp.load_source(mod_name, filepath)
		elif file_ext.lower() == '.pyc':
				py_mod = imp.load_compiled(mod_name, filepath)

		if expected_class in dir(py_mod):
				class_inst = py_mod.main(data,params) 

		return class_inst
