# from ast import match_case
from ctypes import sizeof
import encodings
from http.client import FOUND
from io import TextIOWrapper
from lib2to3.pgen2 import driver
from time import sleep
from turtle import clear, update
from typing import final
import RPi.GPIO as GPIO
from rpi_lcd import LCD
import board
import busio
import time
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn
import math
from gpiozero import Servo
from gpiozero.pins.pigpio import PiGPIOFactory #sudo pigpiod before running
from imutils.video import VideoStream
from imutils.video import FPS
import face_recognition
import imutils
import pickle
import cv2
from multiprocessing import Process
from pathlib import Path

LOCK = 17
BUTTON = 27
SERVO = 22
GPIO.setmode(GPIO.BCM)
GPIO.setup(LOCK, GPIO.OUT)
GPIO.setup(BUTTON, GPIO.IN, pull_up_down=GPIO.PUD_UP)
pifactory = PiGPIOFactory()
servo = Servo(SERVO, min_pulse_width=0.5/1000, max_pulse_width=2.5/1000, pin_factory=pifactory) #prevent jitter
lcd = LCD()
i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
vert = AnalogIn(ads, ADS.P0) #voltage middle 2.4 - 2.6, up > 2.6, down < 2.3
names = ["Aidan"]
age = ["20"]
height = ["6'1"]
likes = ["Sleep"]

def toggleLock(n): #used to toggle lock
    global unlock
    unlock = n

found = 0

def updateFound(n): #used to update found
    global found
    found = n

def updateState(n): #used to change states
    global state
    state = n

def tickLock():
    if(unlock):
        GPIO.output(LOCK, 1)
    else:
        GPIO.output(LOCK, 0)

def scanLoop():
    time.sleep(5.0)
    i = 0
    stop = 0
    while(1):
        file = open('share.txt', 'r')
        buffer = file.read()
        if(buffer):
            found = buffer[0]
        else:
            found == "0"
        if(found == "0"):
            if i < 360:
                buffer = file.read()
                if(buffer): 
                    found = buffer[0]
                servo.value = math.sin(math.radians(i))
                i += 1
                sleep(0.02)
            else:
                i = 0

def facialRec():
    currentname = "unknown"
    encodingsP = "encodings.pickle"
    data = pickle.loads(open(encodingsP, "rb").read())
    camera = VideoStream(usePiCamera=True).start()
    time.sleep(2.0)
    counter = 0
    found = 0
    file = open('share.txt', 'w')
    file.write("0")
    file.close()

    while True:
        frame = camera.read()
        frame = imutils.resize(frame, width=500)
        boxes = face_recognition.face_locations(frame)
        encodings = face_recognition.face_encodings(frame, boxes)
        names = []
        if(encodings):
            for encoding in encodings:
                matches = face_recognition.compare_faces(data["encodings"],
                    encoding)
                name = "Unknown"
                if True in matches:
                    matchedIdxs = [i for (i, b) in enumerate(matches) if b]
                    counts = {}
                    for i in matchedIdxs:
                        name = data["names"][i]
                        counts[name] = counts.get(name, 0) + 1
                    name = max(counts, key=counts.get)
                    if(found == 0):
                        file = open('share.txt', 'w')
                        if(name == "Aidan"):
                            index = "0"
                            file.write("1" + index)
                            found = 1
                            counter = 0
                        file.close()
                    if currentname != name:
                        currentname = name
                    names.append(name)
        else:
            if(counter == 15):
                file = open('share.txt', 'w')
                file.write("0")
                file.close()
                counter = 0
                found = 0
            else:
                counter += 1
        cv2.imshow("Camera", frame)
        key = cv2.waitKey(1) & 0xFF

def search():
    Process(target=scanLoop).start()
    Process(target=facialRec).start()

#states: start, searching, found, info, error, follow

def tickRun():
    press = GPIO.input(BUTTON)
    global check
    if(state == 0): #start
        search()
        lcd.text("      Starting", 2)
        lcd.text("   Please Wait", 3)
        sleep(0.5)
        lcd.text("   Please Wait.", 3)
        sleep(0.5)
        lcd.text("   Please Wait.", 3)
        sleep(0.5)
        lcd.text("   Please Wait..", 3)
        sleep(0.5)
        lcd.text("   Please Wait...", 3)
        sleep(0.5)
        updateState(1)
        i = 0
        lcd.clear()
    elif(state == 1): #searching
        file = open('share.txt', 'r')
        buffer = file.read()
        if(buffer):
            found = buffer[0]
            if(found != "1"):
                lcd.text("   Searching", 2)
                sleep(0.5)
                lcd.text("   Searching.", 2)
                sleep(0.5)
                lcd.text("   Searching..", 2)
                sleep(0.5)
                lcd.text("   Searching...", 2)
                sleep(0.5)
            else:
                updateState(2)
                lcd.clear()
    elif(state == 2):
        lcd.text("       Found!", 2)
        sleep(1)
        lcd.text("     Displaying", 2)
        lcd.text("   Information", 3)
        sleep(0.5)
        lcd.text("   Information.", 3)
        sleep(0.5)
        lcd.text("   Information..", 3)
        sleep(0.5)
        lcd.text("   Information...", 3)
        sleep(0.5)
        updateState(3)
        lcd.clear()
    elif(state == 3):
        file = open('share.txt', 'r')
        buffer = file.read()
        found = buffer[0]
        if(len(buffer) > 1):
            index = buffer[1]
        if(found == "0"):
            updateState(1)
            lcd.clear()
        else:
            if(not press):
                toggleLock(1)
            else:
                toggleLock(0)
            lcd.text("Name: " + names[int(index)], 1)
            lcd.text("Age: " + age[int(index)], 2)
            lcd.text("Height: " + height[int(index)], 3)
            lcd.text("Likes: " + likes[int(index)], 4)

def tickTest():
    if(vert.voltage > 2.4 and vert.voltage < 2.6):
        lcd.clear()
        lcd.text("Mid", 2)
    elif(vert.voltage > 2.6):
        lcd.clear()
        lcd.text("Up", 1)
    elif(vert.voltage < 2.4):
        lcd.clear()
        lcd.text("Down", 3)

def main():
    print("Starting")
    updateState(0)
    updateFound(0)
    toggleLock(0)
    try:
        while(1):
            # tickTest()
            tickRun()
            sleep(0.05) #needed for i2c to settle otherwise crash
            tickLock()
            sleep(0.05)
    
    except KeyboardInterrupt:
        pass
    finally:
        GPIO.cleanup()
        lcd.clear()
        print("")
main()