import importlib.machinery
import time
from turtle import delay
import board
import busio
from digitalio import DigitalInOut, Direction
import adafruit_fingerprint
from pathlib import Path

led = DigitalInOut(board.D13)
led.direction = Direction.OUTPUT

import serial
uart = serial.Serial("/dev/ttyS0", baudrate=57600, timeout=1)

finger = adafruit_fingerprint.Adafruit_Fingerprint(uart)

##################################################

def get_fingerprint():
    while finger.get_image() != adafruit_fingerprint.OK:
        pass
    if finger.image_2_tz(1) != adafruit_fingerprint.OK:
        return False
    if finger.finger_search() != adafruit_fingerprint.OK:
        return False
    return True

output = open("write.txt", "w")
input = open("read.txt", "r")
stop = 0
while True:
    if stop == 0:
        contents = input.read(1)
    if contents == "1":
        stop = 1
        if get_fingerprint():
            print("Finger Found")
            input.close()
            output.write("1")
            output.close()
            contents = " "
        else:
            print("Finger not found")
    