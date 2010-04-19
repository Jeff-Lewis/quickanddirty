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
#     the opencv image related functions
#
############################################################################################
# (C) 2010 Juhapekka Piiroinen
############################################################################################
import opencv

class Details(object):
  def __init__(self,image):
    self.image = image

  def size(self):
    return opencv.cvGetSize(self.image)

class Convert(object):
  def __init__(self,image):
    self.image = image
    self.details = Details(self.image)

  def toGrayscale(self):
    grayscale = opencv.cvCreateImage(self.details.size(), 8, 1)
    opencv.cvCvtColor(self.image, grayscale, 6)
    opencv.cvEqualizeHist(grayscale, grayscale)
    return grayscale

  def toPIL(self):
    img = opencv.cvGetMat(self.image)
    return opencv.adaptors.Ipl2PIL(img) 
