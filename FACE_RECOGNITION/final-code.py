# import the opencv library
import cv2
import subprocess  

screen_width = 500 #720 #640 #500
screen_hight = 281 #405 #360 #281

# define a video capture object
vid = cv2.VideoCapture(0)
face_cascade = cv2.CascadeClassifier('/home/pi/Desktop/haarcascade_frontalface_default.xml')

isRecognized = False

while(True):
      
    # Capture the video frame
    # by frame
    ret, frame = vid.read()
    frame = cv2.resize(frame, (screen_width, screen_hight))
    #Convert to grayscale
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    #Look for faces in the image using the loaded cascade file
    faces = face_cascade.detectMultiScale(gray, 1.1, 9)
        
    #Draw a rectangle around every found faceq
    for (x,y,w,h) in faces:
        cv2.rectangle(frame,(x,y),(x+w,y+h),(255,255,0),4)
    
    # Display the resulting frame
    cv2.imshow('frame', frame)
    
    if(len(faces) > 0 and isRecognized == False):
        print("Human Found! ")
        subprocess.call("sudo python3 LEDMatrix.py", shell = True)
        continue
        #isRecognized = True
      
    # the 'q' button is set as the
    # quitting button you may use any
    # desired button of your choice
    if cv2.waitKey(1) & 0xFF == ord('q'):
        subprocess.call("sudo pkill -9 -f LEDMatrix.py", shell = True)
        break
  
# After the loop release the cap object
vid.release()
# Destroy all the windows
cv2.destroyAllWindows()
