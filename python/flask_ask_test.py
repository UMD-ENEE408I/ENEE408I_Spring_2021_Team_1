
#!/usr/bin/env python3
# Derived from examples in the Flask-Ask repo: https://github.com/johnwheeler/flask-ask

from flask import Flask
from flask_ask import Ask, statement
import serial

app = Flask(__name__)
ask = Ask(app, '/')

ser = serial.Serial('/dev/ttyUSB0')

@ask.intent('Wander')
def wander():
    ser.write(b'w')
    speech_text = 'Wandering'
    return statement(speech_text).simple_card('my robot', speech_text)
    
if __name__ == '__main__':
    app.run()