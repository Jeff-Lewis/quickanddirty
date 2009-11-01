#!/usr/bin/python
from cgi import parse_qs, escape

class data:
		def __init__(self):
				#all styles
				self.style={}
				self.styleSheet = "page/style/style.css"

				#errors and warnings
				self.debug=[]
				self.warnings=[]
				self.errors=[]

				#settings
				self.settings={"PORT":3000, 
								"GALLERY_DB":"gallery.dp",
								"PLUGIN_DIR":"plugins/",
								"DEBUG":1,
								"TEMPLATE_DIR":"page/templates/",
								"TEMPLATE_MAIN":"main.tmpl"
								}

				#query strings
				self.queryString = {}
				self.permanent = {}

				#template parameters and variable for controlling behave
				self.variables={}
				self.toggle=0
				self.toggle2=1
				self.nestCounter = 0
				self.maxNest = 10

				#title
				self.part1 = ""
				self.part2 = "Vaeltaja.net"
				self.delimiter = ""
				self.title = self.part1 + self.delimiter + self.part2
