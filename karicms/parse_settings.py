#!/usr/bin/python
import simplejson
import structs
import os.path

def parse(configFile):
		data = structs.data()
		if os.path.isfile(configFile):
				config = simplejson.load(open(configFile))

				for i in data.settings:
						try:
								config[i]
						except KeyError:
								data.warnings.append("Missing config " + i)
						else:
								data.settings[i] = config[i]
		else:
				data.warnings.append("No Such File: " + configFile)
				#generate default config
				print data.settings
		return data
