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
import driver.micromaestro
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
happyface = pygame.image.load("happyface.png")
previousFace = None
camera = driver.micromaestro.CameraDriver()
camera.reset()
while True:
    raw_img = webcam.capture()
    faces = facedetect.detect(raw_img)
    convert = driver.imagetools.Convert(raw_img)
    capture = convert.toPIL()
    image = pygame.image.frombuffer(capture.tostring(), capture.size, capture.mode)
    
    screen.blit(image, (0,0))
    
    if faces:
        face = faces[0]
        if (face==None):
            continue
        if (previousFace==None):
            previousFace = face
        if (face!=previousFace):
            dx = int(previousFace.x+previousFace.width/2) - int(face.x+face.width/2)
            dy = int(previousFace.y+previousFace.height/2) - int(face.y+face.height/2)
            if (abs(dx)>1 and abs(dx)<40):
                minimx = 1100
                minimy = 1400
                maximx = 1400
                maximy = 2000
                stepx = (maximx-minimx)/64
                stepy = (maximy-minimy)/64
                posx = int(face.x+face.width/2)/10
                posy = int(face.y+face.height/2)/10
                #print posx,posy
                x = minimx+(stepx*posx)
                y = minimy+(stepy*posy)
                #print x,y
                camera.goto(x,y)
                #camera.pan(dx*10)
            #if (abs(dy)>9 and abs(dy)<40):
            #    camera.tilt(-(dy*10))
            previousFace = face
        print "Face Detected @ x: %s\ty: %s\tw: %s\th: %s" % (face.x,face.y,face.width,face.height)
        pygame.draw.rect(screen,(255,0,0),(face.x,face.y,face.width,face.height))   
        screen.blit(pygame.transform.scale(happyface,(face.width,face.height)),(face.x,face.y))
    #for x in range(0,640,10):
    #    pygame.draw.line(screen,(255,0,0),(x,0),(x,480))
    pygame.display.update()
    pygame.time.delay(int(1000 * 1.0/25))
    events = pygame.event.get()
    for event in events:
        if (event.type == pygame.locals.QUIT or event.type == pygame.locals.KEYDOWN):
            camera.reset()
            sys.exit(0)
 
