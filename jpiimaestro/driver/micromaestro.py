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
#     A python-wrapper for Pololu Micro Maestro 6-Channel USB Servo Controller
#
############################################################################################
# /!\ Notes /!\
# You will have to enable _USB Dual Port_ mode from the _Pololu Maestro Control Center_.
#
############################################################################################
# (C) 2010 Juhapekka Piiroinen
############################################################################################
import serial
import time

#################################
class CameraDriver(object):
  def __init__(self,x_servo=0,y_servo=1):
    self.x_servo = x_servo
    self.y_servo = y_servo
    self.device = Device()
    self.device.set_acceleration(self.x_servo,10)
    self.device.set_speed(self.x_servo,10)
    self.device.set_acceleration(self.y_servo,10)
    self.device.set_speed(self.y_servo,10)
    self.device.go_home()
  
  def status_report(self):
    return "X: %s\tY: %s" % (self.device.get_position(self.x_servo),self.device.get_position(self.y_servo))

  def pan(self,dx):
    x = self.device.get_position(self.x_servo)
    x += dx
    self.device.set_target(self.x_servo,x)
 
  def tilt(self,dy):
    y = self.device.get_position(self.y_servo)
    y += dy
    self.device.set_target(self.y_servo,y)

  def reset(self):
    self.device.go_home()

###################################
class Device(object):
  def __init__(self):
    self.con = serial.Serial("/dev/ttyACM1")
    self.con.write(chr(0xAA))
    self.con.flush()
    self.ser = serial.Serial("/dev/ttyACM0")
  
  def go_home(self):
    self.write(0xA2)

  def write(self,*data):
    for d in data:
      self.ser.write(chr(d))
    self.ser.flush()

  def set_target(self,servo,value):
    highbits,lowbits = divmod(value,32)
    self.write(0x84,servo,lowbits << 2,highbits)

  def set_speed(self,servo,speed):
    highbits,lowbits = divmod(speed,32)
    self.write(0x87,servo,lowbits << 2,highbits)
  
  def set_acceleration(self,servo,acceleration):
    highbits,lowbits = divmod(acceleration,32)
    self.write(0x89,servo,lowbits << 2,highbits)

  def get_position(self,servo):
    self.write(0x90,servo)
    data = self.ser.read(2)
    return (ord(data[0])+(ord(data[1])<<8))/4
  
  def get_moving_state(self):
    self.write(0x93)
    data = self.ser.read(1)
    return ord(data[0])

  def get_errors(self):
    self.write(0xA1)
    data = self.ser.read(2)
    return ord(data[0])+(ord(data[1])<<8)

  def __del__(self):
    self.ser.close()


####################################
if __name__=="__main__":
  print "Begin"
  d = CameraDriver()
  print d.status_report()
  d.pan(1500)
  time.sleep(2)
  print d.status_report()
  d.pan(-1500)
  time.sleep(2)
  print d.status_report()
  d.tilt(1500)
  time.sleep(2)
  print d.status_report()
  d.tilt(-1500)
  time.sleep(2)
  print d.status_report()
  d.tilt(2000)
  time.sleep(2)
  print d.status_report()
  d.reset()
  print d.status_report()
  print "Bye"

## EOF
