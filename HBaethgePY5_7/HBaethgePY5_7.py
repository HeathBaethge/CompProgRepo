#computer vision library
import cv2

#name the window
cv2.namedWindow("Assignment5.7")

#set variable to video capture
vc = cv2.VideoCapture(0)

#rval is tracker for window if opened
if vc.isOpened():  #try to get first frame
    rval, frame = vc.read()
else:
    rval = False

while rval:
    #any operations on the frame come to imshow
    #while it is open, push frame into the window
    cv2.imshow("Assignment5.7", frame)
    rval, frame = vc.read()

    #read keys
    #what key is pressed
    key = cv2.waitKey(20)

    #look for esc key ---  ascii value is 27
    if key==27:  #exit on esc
        break

#after breaking out of loop
cv2.destroyWindow("Assignment5.7")