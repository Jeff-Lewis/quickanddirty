# Introduction #
The idea was to create a software package for the webcam and servos, which would enable automatic object tracking using Linux.

# Hardware #
  * Creative Webcam NX Ultra!
  * Pan/Tilt sensor kit from Lets Make Robots
  * 2 Servos
  * Pololu Micro Maestro 6-Channel USB Servo Controller

# Software #
  * Python
  * [OpenCV](http://sourceforge.net/projects/opencvlibrary/)

# Software available @ svn #
  * The face detection and webcam capture is done.
  * _driver_ for the micro maestro is done.
  * servo _driver_ added to the webcam and face detection.

# Known Issues #
The servo's are not controlled correctly.
I have an issue with my laptop with external webcam, as the internal webcam is messing things up with V4L. To be investigated.

# Links #
  * [Tutorial: OpenCV haar training](http://note.sonots.com/SciSoftware/haartraining.html)
  * http://cvc.yale.edu/projects/yalefacesB/yalefacesB.html
  * http://www.bioid.com/support/downloads/software/bioid-face-database.html
  * http://www.face-rec.org/databases/
  * http://www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html
  * http://www.nist.gov/srd/index.htm
  * http://vis-www.cs.umass.edu/lfw/