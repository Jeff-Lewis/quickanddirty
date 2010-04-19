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
#     a small application which will get a picture from webcam and then detect faces and sensor them
#
############################################################################################
# (C) 2010 Juhapekka Piiroinen
############################################################################################
import sys
import time
import driver.webcam
import driver.imagetools
import driver.detect

import pygame,pygame.locals

webcam = driver.webcam.Webcam()

pygame.init()
pygame.display.set_caption("jpiimaestro - Webcam Capture")
window = pygame.display.set_mode((640,480))
screen = pygame.display.get_surface()
facedetect = driver.detect.Face()

while True:
    raw_img = webcam.capture()
    faces = facedetect.detect(raw_img)
    convert = driver.imagetools.Convert(raw_img)
    capture = convert.toPIL()
    image = pygame.image.frombuffer(capture.tostring(), capture.size, capture.mode)
    
    screen.blit(image, (0,0))
    
    for face in faces:
        print "Face Detected @ x: %s\ty: %s\tw: %s\th: %s" % (face.x,face.y,face.width,face.height)
        pygame.draw.rect(screen,(255,0,0),(face.x,face.y,face.width,face.height))   
    pygame.display.update()
    pygame.time.delay(int(1000 * 1.0/25))
    events = pygame.event.get()
    for event in events:
        if (event.type == pygame.locals.QUIT or event.type == pygame.locals.KEYDOWN):
            sys.exit(0)
