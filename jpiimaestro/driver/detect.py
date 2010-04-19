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
#     the opencv detection wrapper class
#
############################################################################################
# (C) 2010 Juhapekka Piiroinen
############################################################################################
import opencv
import driver.imagetools

class Face(object):
  def __init__(self,haarcascade="haarcascade_frontalface_alt.xml"):
    self.cascade = opencv.cvLoadHaarClassifierCascade(haarcascade,opencv.CvSize())
    self.storage = opencv.cvCreateMemStorage(0)
    opencv.cvClearMemStorage(self.storage)

  def detect(self,image):
      grayscale = driver.imagetools.Convert(image).toGrayscale()
      return opencv.cvHaarDetectObjects(grayscale, self.cascade, self.storage, 1.2, 2)
