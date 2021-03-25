
#!/usr/bin/env python3
# Derived from examples in the Flask-Ask repo: https://github.com/johnwheeler/flask-ask

from flask import Flask
from flask_ask import Ask, statement
import serial
import threading
import facerecognition as fr
import time

user_name = "Unknown"
default_user = "Shueyeeb"

app = Flask(__name__)
ask = Ask(app, '/')

ser = serial.Serial('/dev/ttyUSB0')

@ask.intent('Wander')
def wander():
    ser.write(b'w')
    speech_text = 'Wandering'
    return statement(speech_text).simple_card('My Robot', speech_text)

@ask.intent('Forward')
def go_forward():
    ser.write(b'f')
    speech_text = 'Going forward'
    return statement(speech_text).simple_card('My Robot', speech_text)

@ask.intent('Backward')
def go_forward():
    ser.write(b'b')
    speech_text = 'Going backward'
    return statement(speech_text).simple_card('My Robot', speech_text)

@ask.intent('Stop')
def stop():
    ser.write(b's')
    speech_text = 'Stopping!'
    return statement(speech_text).simple_card('My Robot', speech_text)

@ask.intent('Face')
def face():
    global user_name 
    user_name = fr.id
    if user_name == default_user:
        speech_text = 'Welcome {}!'.format(user_name)
    else:
        speech_text = 'You are {}, I do not know you!'.format(user_name)
    return statement(speech_text).simple_card('My Robot', speech_text)

if __name__ == '__main__':
    face = threading.Thread(target=fr.act_cam)
    face.start()
    app.run()