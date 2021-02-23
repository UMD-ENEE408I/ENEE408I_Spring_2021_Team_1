import cv2
import numpy as np
import os 
recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read('trainer.yml')

faceCascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml');
font = cv2.FONT_HERSHEY_PLAIN

# starting id
id = 0
# id names
names = ['None', 'Chris', 'Jake'] 

cam = cv2.VideoCapture(0)
cam.set(3,640)
cam.set(4,480)

while True:
    ret, img =cam.read()

    # Convert into grayscale
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    
    # Detect faces
    faces = faceCascade.detectMultiScale(gray, 1.1, 4)

    # Draw rectangle around the faces
    for(x,y,w,h) in faces:
        cv2.rectangle(img, (x,y), (x+w,y+h), (255,0,0), 2)
        # Prediction function
        id, confidence = recognizer.predict(gray[y:y+h,x:x+w])
        
        # This is for displaying the correct name
        # confidence is actually opposite, so 100-confidence is printed
        if (confidence < 100):
            id = names[id]
            confidence = "{0}%".format(round(100 - confidence))
        else:
            id = "unknown"
            confidence = "{0}%".format(round(100 - confidence))
        print(str(id))
        print(str(confidence))
        cv2.putText(
                    img, 
                    str(id), 
                    (x+5,y-5), 
                    font, 
                    2, 
                    (255,255,255), 
                    2
                   )
        cv2.putText(
                    img, 
                    str(confidence), 
                    (x+5,y+h-5), 
                    font, 
                    2, 
                    (0,255,0), 
                    2
                   )  

    # Display the output
    cv2.imshow('camera',img) 

    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cam.release()
cv2.destroyAllWindows()