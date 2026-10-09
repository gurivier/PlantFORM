#!/usr/bin/env python3

import RPi.GPIO as GPIO

from serial import Serial
import termios

import time

H_RED        =   0
H_ORANGE     =  32
H_YELLOW     =  64
H_GREEN      =  96
H_AQUA       = 128
H_BLUE       = 160
H_PURPLE     = 192
H_PINK       = 224

S_WHITE      =   0
S_MIN        = 127
S_LOW        = 159
S_MED        = 191
S_HIGH       = 223
S_MAX        = 255

L_MIN        =   0
L_LOW        =  63
L_MED        = 127
L_HIGH       = 191
L_MAX        = 255

MS_FULL      =  1
MS_HALF      =  2
MS_FOURTH    =  4
MS_EIGTHTH   =  8
MS_SIXTEENTH = 16

POS_MIN      =  1
POS_LOW      =  3
POS_MED      =  5
POS_HIGH     =  8
POS_MAX      = 10

SWITCH_ARDUINO_PIN = 29 # GPIO-5
SWITCH_MOTORS_PIN = 31 # GPIO-6

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(True)
GPIO.setup(SWITCH_ARDUINO_PIN, GPIO.OUT)
GPIO.setup(SWITCH_MOTORS_PIN, GPIO.OUT)
GPIO.output(SWITCH_ARDUINO_PIN, GPIO.LOW)
GPIO.output(SWITCH_MOTORS_PIN, GPIO.LOW)

class DriverPlantFORM:
    
    def __init__(self, path='/dev/serial0', baudrate=9600, pos_max=260):
        self.serial_port = Serial(port=path, baudrate=baudrate)
        self.pos_max = [pos_max] * 11
        self.cur_positions = {}
        self.__unserialize_cur_positions()

    def save(self):
        self.__serialize_cur_positions()
        
    def wait_end_of_motion(self):
        while True:
            b = self.serial_port.read()
            #print(f'received: {b}')
            if b != -1 and b.decode() == '<':
                b = self.serial_port.read().decode()
                if b == 'e':
                    b = self.serial_port.read().decode() # '|'
                    reading_number = True
                    number = 0
                    while reading_number:
                        b = self.serial_port.read().decode()
                        if b == '>':
                            reading_number = False
                        else:
                            number = number * 10 + int(b)
                    return number
                
    def wait_reply_cur_position(self):
        while True:
            b = self.serial_port.read()
            #print(f'received: {b}')
            if b != -1 and b.decode() == '<':
                b = self.serial_port.read().decode()
                if b == 'j':
                    b = self.serial_port.read().decode() # '|'
                    reading_number = True
                    number = 0
                    while reading_number:
                        b = self.serial_port.read().decode()
                        if b == '|':
                            reading_number = False
                        else:
                            number = number * 10 + int(b)
                            reading_position = True
                            position = 0
                    while reading_position:
                        b = self.serial_port.read().decode()
                        if b == '>':
                            reading_position = False
                        else:
                            position = position * 10 + int(b)                    
                    return (number, position)
                
    # Give color to one LED (0 means all LEDs with same color)
    # hour in [1..10]
    def set_led_color(self, hour, color_hsl):
        code = 'l'
        h, s, l = color_hsl
        num = self.__hour_to_num(hour)
        self.__send(f'<{code}|{num}|{h}|{s}|{l}>')

    def set_energyshape_gain(self, value):
        code = 'g'
        self.__send(f'<{code}|{value}>')
        
    def set_energyshape_brightness(self, value):
        code = 'B'
        self.__send(f'<{code}|{value}>')
        
    def wait_led(self, delay_ms):
        code = 'w'
        self.__send(f'<{code}|{delay_ms}>')
        
    # Give colors to all LEDs
    def set_leds_colors(self, colors_hsl):
        code = 'L'
        values = '|'.join('|'.join(str(c) for c in color) for color in colors_hsl)
        #print(values)
        self.__send(f'<{code}|{values}>')

    def blink_led(self, hour, color):
        code = 'b'
        num = self.__hour_to_num(hour)
        h, s, v = color
        self.__send(f'<{code}|{num}|{h}|{s}|{v}>')

    def blink_led_stop(self, hour):
        code = 's'
        num = self.__hour_to_num(hour)
        self.__send(f'<{code}|{num}>')
        
    def switch_power_supply(self, enable):
        if enable: #-- Turn power on
            GPIO.output(SWITCH_ARDUINO_PIN, GPIO.HIGH)
            time.sleep(30)
            self.__restore_cur_positions()
            GPIO.output(SWITCH_MOTORS_PIN, GPIO.HIGH)
        else: #-- Turn power off
            GPIO.output(SWITCH_MOTORS_PIN, GPIO.LOW)
            self.ask_cur_positions()
            time.sleep(0.5)
            GPIO.output(SWITCH_ARDUINO_PIN, GPIO.LOW)

    def switch_power_supply5(self, enable):
        if enable: #-- Turn power on
            GPIO.output(SWITCH_ARDUINO_PIN, GPIO.HIGH)
            time.sleep(30)
            self.__restore_cur_positions()
        else: #-- Turn power off
            self.ask_cur_positions()
            time.sleep(0.5)
            GPIO.output(SWITCH_ARDUINO_PIN, GPIO.LOW)

    def switch_power_supply220(self, enable):
        if enable: #-- Turn power on
            GPIO.output(SWITCH_MOTORS_PIN, GPIO.HIGH)
        else: #-- Turn power off
            GPIO.output(SWITCH_MOTORS_PIN, GPIO.LOW)

    def ask_cur_position(self, num):
        code = 'i'
        self.__send(f'<{code}|{num}>')
        (n, p) = self.wait_reply_cur_position()
        self.__record_cur_position(n, p)

    def ask_cur_positions(self):
        code = 'i'
        print("ask cur positions = ", end='')
        for num in range(1, 11):
            self.__send(f'<{code}|{num}>')
            (n, p) = self.wait_reply_cur_position()
            print((n, p), end='')
            self.__record_cur_position(n, p)
            print('')
            
    # move one motor to a position
    def move_motor_to_position(self, hour, pos10):
        code = 'm'
        num = self.__hour_to_num_motor(hour)
        pos = self.__pos10_to_motor_position(num, pos10)
        self.__send(f'<{code}|{num}|{pos}>')

    # move all motors to their positions
    def set_motor_position_value(self, hour, pos10):
        code = 'p'
        num = self.__hour_to_num_motor(hour)
        pos = self.__pos10_to_motor_position(num, pos10)
        self.__send(f'<{code}|{num}|{pos}>')
        
    # move all motors to their positions
    def move_motors_to_positions(self, positions10):
        code = 'M'
        values = '|'.join(str(self.__pos10_to_motor_position(num, positions10[num])) for num in range(0, len(positions10)))
        #print(values)
        self.__send(f'<{code}|{values}>')
        
    def move_motor_to_position_and_send_led_color(self, hour, pos10, color_hsl):
        code = 'c'
        h, s, l = color_hsl
        num = self.__hour_to_num(hour)
        self.__send(f'<{code}|{num}|{pos}|{h}|{s}|{l}>')
        
    def move_motors_to_positions_and_send_leds_colors(self, positions10, colors_hsl):
        code = 'C'
        values = '|'.join(str(self.__pos10_to_motor_position(num, positions10[num])) for num in range(0, len(positions10)))
        values += '|' + '|'.join('|'.join(str(c) for c in color) for color in colors_hsl)
        #print(values)
        self.__send(f'<{code}|{values}>')
        
    def reset_motor_to_zero_position(self, hour):
        code = 'z'
        num = self.__hour_to_num(hour)
        self.__send(f'<{code}|{num}>')
        
    def reset_motors_to_zero_position(self):
        code = 'Z'
        self.__send(f'<{code}>')

    # default 163 (min)
    def set_motors_delay_us(self, delay_us):
        code = 'D'
        self.__send(f'<{code}|{delay_us}>')
        
    # mode in 1, 2, 4, 8, 16
    def set_microstepping(self, mode):
        code = 'S'
        self.__send(f'<{code}|{mode}>')

    # default 5
    def set_max_failed_steps(self, steps):
        code = 'F'
        self.__send(f'<{code}|{steps}>')

    # default: 5500
    def set_max_position(self, num, steps):
        code = 'x'
        self.pos_max[num] = steps
        self.__send(f'<{code}|{num}|{steps}>')

    # default: 5500
    def set_max_positions(self, steps):
        code = 'X'
        self.pos_max = [steps] * 11
        self.__send(f'<{code}|{steps}>')
        
    # default 400
    def set_blink_period_ms(self, period_ms):
        code = 'K'
        self.__send(f'<{code}|{period_ms}>')

    # pos10 in [1..10]: 1=folded 10=openned
    def __pos10_to_motor_position(self, num, pos10):
        print(f'num = {num}')
        if pos10 > 10:
            pos10 = 10
        elif pos10 < 0:
            pos10 = 0
            pos_steps = self.pos_max[num] - int(self.pos_max[num] * pos10 / 10)
            pos_steps = pos_steps if pos_steps <= self.pos_max[num] else self.pos_max[num]
            print(f'position = {pos_steps} steps ')
        return pos_steps

    def __hour_to_num(self, hour):
        return hour - 7 if hour > 0 else 0

    def __hour_to_num_motor(self, hour):
        return hour - 7 if hour > 0 else 0

    def __record_cur_position(self, num, pos):
        self.cur_positions[num] = pos

    def __restore_cur_positions(self):
        code = 'p' # set motor position value
        print('restore cur positions=', end='')
        for num in self.cur_positions:
            pos = self.cur_positions[num]
            print((num, pos), end='')
            self.__send(f'<{code}|{num}|{pos}>')
            print('')

    def __serialize_cur_positions(self):
        import pickle
        with open('cur_positions.pkl', 'wb') as f:
            pickle.dump(self.cur_positions, f)
            
    def __unserialize_cur_positions(self):
        import pickle
        import os
        if os.path.isfile('cur_positions.pkl'):
            with open('cur_positions.pkl', 'rb') as f:
                self.cur_positions = pickle.load(f)
                
    def __send(self, frame):
        self.serial_port.write(frame.encode())
        self.serial_port.flush()
        time.sleep(0.1)

if __name__ == '__main__':
    PF = DriverPlantFORM()
    hour = 8   # in [8..17]
    pos10 = 7  # in [1..10]
    PF.send_led_color(0, (0, 0, 0))
    PF.send_led_color(0, (H_RED, S_MAX, L_MAX))
    PF.send_led_color(hour, (H_RED, S_MED, L_MED))
    PF.send_motors_delay_us(1000)    
    PF.send_microstepping(MS_SIXTEENTH)
    PF.send_reset_motors_to_zero_position()
    PF.move_motor_to_position(hour, pos10)
