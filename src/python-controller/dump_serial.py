#!/usr/bin/env python3

import RPi.GPIO as GPIO

from serial import Serial
import termios

import sys

path='/dev/serial0'
baudrate=9600

serial_port = Serial(port=path, baudrate=baudrate)

while True:
    b = serial_port.read()
    if b != -1:
        b = b.decode()
        print(b, end='')
        sys.stdout.flush()
        if b == '>':
            print('')
