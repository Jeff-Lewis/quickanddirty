#!/usr/bin/python 
###########################################################################################
# Filename: 
#     LegacyCameraDriver.py
###########################################################################################
# Project Authors: 
#     Juhapekka Piiroinen
#     Brian Wu
# 
# Changes:
#     June 14, 2010 by Juhapekka Piiroinen - changes committed to svn
#           - added comments for the device commands according to the manual from Pololu
#           - added latest draft code for rotating base servo (Parallax Continuous Rotating Servo)
#           - note! you should be able to clear error flags with .get_errors function according to the manual
#           - renamed CameraDriver to LegacyCameraDriver as Brian Wu has done better one
#           - integrated batch of changes provided by Brian Wu
#
#     June 11, 2010 by Brian Wu - Changes committed thru email
#           - Decoupling the implementation from the program
#
#     April 19, 2010 by Juhapekka Piiroinen
#           - Initial Release
# 
# Email:
#     juhapekka.piiroinen@gmail.com
#
# License: 
#     GNU/GPLv3
#
# Description:
#     A python-wrapper for Pololu Micro Maestro 6-Channel USB Servo Controller
#
############################################################################################
# /!\ Notes /!\
# You will have to enable _USB Dual Port_ mode from the _Pololu Maestro Control Center_.
#
############################################################################################
# Device Documentation is available @ http://www.pololu.com/docs/pdf/0J40/maestro.pdf
############################################################################################
# (C) 2010 Juhapekka Piiroinen
#          Brian Wu
############################################################################################
import Device

class LegacyCameraDriver(object):
  def __init__(self,x_servo=0,y_servo=1,z_servo=2):
    self.x_servo = x_servo
    self.y_servo = y_servo
    self.z_servo = z_servo
    self.device = Device()
    self.device.set_acceleration(self.x_servo,10)
    self.device.set_speed(self.x_servo,10)
    self.device.set_acceleration(self.y_servo,10)
    self.device.set_speed(self.y_servo,10)
    self.device.set_acceleration(self.z_servo,10)
    self.device.set_speed(self.z_servo,10)
    self.device.go_home()

  def __del__(self):
    del(self.device)
    
  def status_report(self):
    return "X: %s\tY: %s\tZ: %s" % (self.device.get_position(self.x_servo),self.device.get_position(self.y_servo),self.device.get_position(self.z_servo))

  def pan(self,dx):
    x = self.device.get_position(self.x_servo)
    x += dx
    self.device.set_target(self.x_servo,x)
    self.device.wait_until_at_target()
 
  def tilt(self,dy):
    y = self.device.get_position(self.y_servo)
    y += dy
    self.device.set_target(self.y_servo,y)
    self.device.wait_until_at_target()

  def rotate(self,dz):
    z = self.device.get_position(self.z_servo)
    z += dz
    self.device.set_target(self.z_servo,z)
    self.device.wait_until_at_target()
    
  def goto(self,x,y,z=0):
    self.device.set_target(self.x_servo,x)
    self.device.set_target(self.y_servo,y)
    self.device.set_target(self.z_servo,z)
    self.device.wait_until_at_target()
    
  def reset(self):
    self.device.go_home()
    self.device.wait_until_at_target()
