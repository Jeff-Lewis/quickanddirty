#!/usr/bin/env python
import core
import parse_settings
from flup.server.fcgi import WSGIServer
      
def myapp(environ, start_response):
	start_response('200 OK', [('Content-Type', 'text/html')])
	return [core.main(environ)]
    

settings = parse_settings.parse(".config.json")
port = settings.settings['PORT']
try:
		int(port)
except:
		port = 3000

WSGIServer(myapp, bindAddress = ("127.0.0.1", port)).run()
