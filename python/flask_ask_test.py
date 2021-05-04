
#!/usr/bin/env python3
# Derived from examples in the Flask-Ask repo: https://github.com/johnwheeler/flask-ask

from flask import Flask
from flask_ask import Ask, statement
import serial
import threading
import facerecognition as fr
import time
from chat_client import RobotChatClient

user_name = "Unknown"
default_user = "Shueyeeb"

app = Flask(__name__)
ask = Ask(app, '/')

username = 'suyaib'
ngrok_link = 'ws://something.ngrok.io'

ser = serial.Serial('/dev/ttyUSB0')

def test_callback(message_dict):
    
    if message_dict['type'] == 'message':
        print('{0} : {1}'.format(message_dict['user'],message_dict['message']))

    elif message_dict['type'] == 'command':
        print('Global Target: {0} Command: {1}'.format(
              message_dict['user'],
              message_dict['command']))

        if message_dict['user'] == 'all' or message_dict['user'] == username:
            print(message_dict['command'])
            ser.write(message_dict['command'].encode('utf-8'))
            
    elif message_dict['type'] == 'users':
        print('Number of users: {}'.format(message_dict['count']))

def Connected_Chat():
    global client
    client = RobotChatClient(ngrok_link, callback=test_callback)
    time.sleep(1)
    print('Suyaib has connected')
    client.send({'type': 'message', 'user': username,
                'message': 'Suyaib has connected' })


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
def go_backward():
    ser.write(b'b')
    speech_text = 'Going backward'
    return statement(speech_text).simple_card('My Robot', speech_text)

@ask.intent('Left')
def go_left():
    ser.write(b'l')
    speech_text = 'Going left'
    return statement(speech_text).simple_card('My Robot', speech_text)

@ask.intent('Right')
def go_right():
    ser.write(b'r')
    speech_text = 'Going right'
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

@ask.intent('AllWander')
def allWander():
    command = "w"
    speech_text = 'I asked all robots to wander'

    ser.write(command.encode('utf-8'))

    if command != "":
        client.send({'type': 'command',
                     'user': 'all',
                     'command': command})

    return statement(speech_text).simple_card('My Robot', speech_text)

if __name__ == '__main__':
    face = threading.Thread(target=fr.act_cam)
    face.start()
    app.run()