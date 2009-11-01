#!/usr/local/bin/env python
#-*- coding: <utf-8> -*-
from cgi import parse_qs, escape
import cgi
import os
import re
import structs
import parse_settings
import parse_layout
import parse_style
import sys


def head(data):
	header = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"\n\
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">\n\
	<html xmlns="http://www.w3.org/1999/xhtml" lang="fi" xml:lang="fi">\n\
	<head>\n\
	<link href="'+data.styleSheet+'" rel="stylesheet" type="text/css" media="screen"/>\n'
	header = header + '<title>' + data.title + '</title>\n'
	header = header + '<link rel="shortcut icon" href="/favicon.ico"/>\n\
	</head><body onload="load()" onunload="GUnload()">\n'
	return header
	
def main(environ):
		data = parse_settings.parse(".config.json")
		list = {}
		
		#Parse QUERY_STRING
		for i in parse_qs(environ.get('QUERY_STRING', '')):
				data.queryString[i] = escape(parse_qs(environ.get('QUERY_STRING', ''))[i][0])

		page = parse_layout.parse(data.settings['TEMPLATE_MAIN'] , data)
		
		page = head(data) + page + tail(data)

		return page

def tail(data):
	tail = "<div style=\"text-align:right;font-size:small;\"><p>Powered by <img src=\"KariCMS.png\" /></p></div>"
	
	#Add debug and errors
	if data.settings['DEBUG']:
			tail = tail + '<div style="background-color:#EEEEEE;\
							border-width:1px; border-color:#3E489B;border-style:solid;padding:10px;">'
			tail = tail + "<h3>Debug, Warnings, & Errors</h3>"
			for i in data.debug:
					tail = tail + '<b style="color:black;">' + i + '</b><br />'
			for i in data.errors:
					tail = tail + '<b style="color:red;">' + i + '</b><br />'
			for i in data.warnings:
					tail = tail + '<b style="color:blue;">' + i + '</b><br />'
			tail = tail + '</div>'
	
	tail = tail + "</body></html>"
	return tail

