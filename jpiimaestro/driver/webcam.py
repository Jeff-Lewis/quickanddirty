#!/usr/bin/python
###########################################################################################
# Author: 
#     Juhapekka Piiroinen
# Email:
#     juhapekka.piiroinen@gmail.com
# License: 
#     GNU/GPLv3
#
# Description:
#     the opencv - webcam related functions
#
############################################################################################
# (C) 2010 Juhapekka Piiroinen
############################################################################################
from opencv import highgui 

class Webcam(object):
  def __init__(self,device=0):
    self.camera = highgui.cvCreateCameraCapture(device)

  def capture(self):
    img = highgui.cvQueryFrame(self.camera)
    return img


