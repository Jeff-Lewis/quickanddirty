#!/usr/bin/env python

import structs
import os.path
import re
import plugin
import parse_style


def parse(templateFile, data):
		if data.settings['DEBUG']:
				data.debug.append("nestCounter: " + str(data.nestCounter) + "\ttemplate: " + templateFile)
		data.nestCounter += 1
		page = ""
		global nestCounter
		templateFile = data.settings['TEMPLATE_DIR'] + templateFile
		#check if tempalete file exist
		if os.path.isfile(templateFile):
				#match variables, templaset and blocks and so on..
				variableRe = re.compile('#.*#')
				templateRe = re.compile('{.*}')
				blockRe = re.compile('\[.*\]')
				linkRe = re.compile('\$.*\$.*\$')
				conditionRe = re.compile('.*\@.*\@.*\@.*')
				templVariableRe = re.compile('.*\%.*\%.*')

				#open file
				f = open( templateFile ,"r")
				for line in f:
						#Add variables
						if templVariableRe.match(line):
								newLine = line
								lineLen = len(line)
								lineLenTemp = len(line)
								paramTemp = []
								firstChar = 0
								secondChar = 0
								#find variables, check if exist and append
								while (lineLen > 0):
										#find first % character
										firstChar = line.find('%',firstChar, lineLenTemp)
										#second character
										secondChar = line.find('%', firstChar+1, lineLenTemp)
										#there is no first char, so break
										if firstChar < 0:
												break

										tempString = line[firstChar:secondChar+1].replace("%","")
										
										#check is there is data for variable
										try:
												data.variables[tempString]
										except KeyError:
												data.warnings.append("No variable " + tempString)
												#remove it?
												if data.settings['DEBUG']:
														newLine = newLine.replace("%"+tempString+"%","<b>%"+tempString+"%</b>")
												else:
														newLine = newLine.replace("%"+tempString+"%", "")
										else:
												newLine = newLine.replace("%"+tempString+"%", data.variables[tempString])

										firstChar = secondChar + 1
								line = newLine
						if variableRe.match(line):
								#pick data from variables
								parse_variables(line.replace("\n", ""), data)
						elif conditionRe.match(line):
								#test conditions and parse templates is conditions are true
								page = page + parse_conditions(line.replace("\n", ""), data)
						elif templateRe.match(line):
								#import other templates and parse it
								if data.nestCounter > data.maxNest:
										data.warnings.append("Too many recursives on templates: maxNest="+str(data.maxNest)+", nestCounter="+str(data.nestCounter)+"\n")
								page = page + parse_templates(line.replace("\n", ""), data)
						elif blockRe.match(line):
								#add plugins
								page = page + plugin.add_plugin(line.replace("\n", ""), data)
						elif linkRe.match(line):
								#parse links
								page = page + parse_links(line.replace("\n", ""),data)
						else:
								page = page + line
				f.close()
		else:
				#there is no requested temlate
				data.errors.append("No Such file: " + templateFile)

		return page

def parse_variables(line,data):
		#parse variables and ad it to data.params
		line = line.replace("#", "")
		variables = line.split(',')
		for i in variables:
				temp = i.split('=')
				data.variables[temp[0]]=temp[1]

def parse_templates(line, data):
		line = line.strip("{}")
		return parse(line, data) + "\n"

def parse_conditions(line, data):
		#@vaellus=2008@templates/vaellus2008.tmpl@
		page = ""
		temp = line.split('@')
		template = temp[2]
		condTemp = temp[1]
		cond = condTemp.split('=')
		all = condTemp.split(',')
		toggle2=1
		try:
				for i in all:
						test = i.split('=')
						data.queryString[test[0]]
		except:
				if cond[0] == 'DEFAULT' and data.toggle == 0:
						page =  parse(template, data) + "\n"
		else:
				if len(all) > 1:
						for t in all:
								tt = t.split('=')
								if len(tt) > 1:
										if not data.queryString[tt[0]] == tt[1]:
												toggle2 = 0
										else:
												data.permanent[tt[0]] = tt[1]
								else:
										toggle2 = 1
										data.permanent[tt[0]] = "index" #NULL"
						if toggle2:
								page =  parse(template, data) + "\n"
								data.toggle=1
				else:
						if len(cond) > 1:
								if data.queryString[cond[0]] == cond[1]:
										data.permanent[cond[0]] = cond[1]
										page =  parse(template, data) + "\n"
										data.toggle = 1
						else:
								data.permanent[cond[0]] = "index" #NULL"
								page =  parse(template, data) + "\n"
								data.toggle = 1
		return page

def parse_links(line,data):
		styles = parse_style.parse("page/style/style.css")
		link = ""
		style = ""
		classs = ""
		params = {}
		emphasis = []
		classTemp = ""
		wholeString = line.split('$')
		string = wholeString[1]
		name = wholeString[2]
		all = string.split(',')
		styleRe = re.compile('style=".*', re.IGNORECASE)
		classRe = re.compile('class=".*', re.IGNORECASE)
		currentRe = re.compile('emphasis=".*', re.IGNORECASE)
		for i in all:
				if styleRe.match(i):
						style =  i
				elif classRe.match(i):
						classs = i
						classTemp = classs.replace("class=", "")
						classTemp = classTemp.replace("\"", "")
				elif currentRe.match(i):
						temperoinen = i
						temperoinen = temperoinen.replace("emphasis=", "")
						temperoinen = temperoinen.replace("\"", "")
						emphasis = temperoinen.split('&')
				else:
						params[i] = i
						
		for a in params:
				link = link + a + "&"
		tokkeli = 0
		for aa in emphasis:
				temperoinen3 = aa.split('=')
				try:
						data.queryString[temperoinen3[0]]
				except KeyError:
						pass
				else:
						try:
								styles.style[classTemp + "Emphasis"]
						except KeyError:
								pass
						else:
								if len(temperoinen3) > 1:
										if data.queryString[temperoinen3[0]] == temperoinen3[1]:
												tokkeli = 1
										else:
												tokkeli = 0
												break
								else:
										tokkeli = 1
		if len(emphasis) == 1:
				if emphasis[0] == 'NULL':
						try:
								styles.style[classTemp + "Emphasis"]
						except KeyError:
								pass
						else:
								if len(data.queryString) == 0:
										tokkeli = 1
		if tokkeli:
				classs =  "class=\""+classTemp + "Emphasis\""

		if len(link) > 1:
				if link[len(link)-1] == '&':
						link = link[0:len(link)-1]
		return '<a ' + style + ' ' + classs + ' href="index.fcgi?' + link + '">' + name + "</a>\n"

