#!/usr/bin/env python3

import time
import DriverPlantFORM as pf
from DriverPlantFORM import DriverPlantFORM

from in_range import in_range

pname = 'plantform1'

#def give_position(rate, factor):
#    if rate == 1.0 * factor:
#        position = 10
#    elif rate > 0.9 * factor:
#        position = 7
#    elif rate > 0.8 * factor:
#        position = 6
#    elif rate > 0.5 * factor:
#        position = 5
#    elif rate > 0.2 * factor:
#        position = 3
#    elif rate > 0.1 * factor:
#        position = 2
#    else:
#        position = 1
#    return int(position)

def give_position(rate, factor):
    if rate == 1.0 * factor:
        position = 10
    elif rate > 0.9 * factor:
        position = 7
    elif rate > 0.8 * factor:
        position = 6
    elif rate > 0.5 * factor:
        position = 5
    elif rate > 0.2 * factor:
        position = 4
    elif rate > 0.1 * factor:
        position = 3
    else:
        position = 0
    return int(position)

def give_color(rate, factor):
    if rate == 1.0 * factor:
        luminosity = 245
        saturation = 255
    elif rate > 0.9 * factor:
        luminosity = 196
        saturation = 196
    elif rate > 0.8 * factor:
        luminosity = 164
        saturation = 180
    elif rate > 0.5 * factor:
        luminosity = 128
        saturation = 164
    elif rate > 0.2 * factor:
        luminosity = 64
        saturation = 128
    elif rate > 0.1 * factor:
        luminosity = 48
        saturation = 96
    else:
        luminosity = 0
        saturation = 0
    return (pf.H_GREEN, saturation, luminosity)

blink_color = (16, 228, 0) # 164

energy_rates = []
leaf_positions = []
led_colors = []

#                      8h     9h     10h    11h    12h    13h    14h    15h    16h    17h
energy_rates.append( [ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000 ] ) # Index 0: min prod
energy_rates.append( [ 0.595, 0.797, 0.924, 0.991, 1.000, 0.962, 0.875, 0.737, 0.524, 0.315 ] ) # Index 1: 10h
energy_rates.append( [ 0.000, 0.000, 0.052, 0.065, 0.113, 0.266, 0.296, 0.855, 1.000, 0.954 ] ) # Index 2: 8h
energy_rates.append( [ 0.768, 0.929, 0.844, 0.712, 0.125, 0.000, 0.000, 0.000, 0.000, 0.000 ] ) # Index 3: 5h
energy_rates.append( [ 0.000, 0.000, 0.000, 0.000, 0.125, 0.481, 0.694, 0.344, 0.000, 0.000 ] ) # Index 4: 4h    
energy_rates.append( [ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.344, 0.846, 0.768 ] ) # Index 5: 3h
energy_rates.append( [ 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000 ] ) # Index 6: max prod

#for rates in energy_rates:
#    leaf_positions.append( [ give_position(rate) for rate in rates ] )
#    led_colors.append( [ give_color(rate) for rate in rates ] )
    
#print(energy_rates[0])
#print(energy_rates[1])
#print(energy_rates[2])
#print(energy_rates[3])
#print(energy_rates[4])

#exit()
#quit()

colors = [
    (pf.H_GREEN, 255,   0),
    (pf.H_GREEN, 255,  64),
    (pf.H_GREEN, 255,  64),
    (pf.H_GREEN, 255, 128),
    (pf.H_GREEN, 255, 255),
    (pf.H_GREEN, 255, 128),
    (pf.H_GREEN, 255,  64),
    (pf.H_GREEN, 255,   0),
    (pf.H_GREEN, 255, 255),
    (pf.H_GREEN, 255, 255)
]

positions = [0, 10, 20, 20, 50, 50, 30, 10, 0, 0]

def get_factor(variation):
    idem = True
    for i in range(1, len(variation)):
        if variation[i] != variation[0]:
            idem = False
    return 1.0 if idem else max(variation)

def play_variation(PF, variation, illuminated):
    hour = 8 # if pname == 'plantform' else 9
    print(variation)
    for rate in variation:
        print(f'move {hour}h at {rate}')
        position = give_position(rate, get_factor(variation))
        if illuminated:
            color = give_color(rate, get_factor(variation))
            PF.set_led_color(hour, color)
            PF.blink_led(hour, blink_color)
        PF.move_motor_to_position(hour, position)
        num = PF.wait_end_of_motion()
        print(f'motion done: {num}')
        #time.sleep(0.02)
        hour += 1

def set_variation_values(PF, variation, illuminated):
    hour = 8
    print(f'set values {variation}')
    for rate in variation:
        position = give_position(rate, get_factor(variation))
        if illuminated:
            color = give_color(rate, get_factor(variation))
            PF.set_led_color(hour, color)
            time.sleep(0.03)
        PF.set_motor_position_value(hour, position)
        time.sleep(0.02)
        hour += 1

def play_reset(PF):
    for hour in range(17, 7, -1):
        print(f'reset {hour}h')
        color = (0, 0, 0)
        PF.set_led_color(hour, color)
        PF.blink_led(hour, blink_color)
        PF.reset_motor_to_zero_position(hour)
        num = PF.wait_end_of_motion()
        print(f'motion done: {num}')
        #time.sleep(0.2)

def play_init(PF):
    for hour in range(17, 7, -1):
        print(f'init {hour}h')
        PF.blink_led(hour, blink_color)
        PF.move_motor_to_position(hour, 0)
        num = PF.wait_end_of_motion()
        PF.set_led_color(hour, (0, 0, 0))
        print(f'motion done: {num}')
        #time.sleep(0.2)

def treat(PF, msg):
    msg = msg.strip()
    if msg[0] == '<' and msg[-1] == '>':
        buf = msg[1:-1].split('|')
        prototype = buf[0]
        if prototype == pname or prototype == 'all':
            action = buf[1]
            if action == 'shutdown' or action == 'poweroff' or action == 'off':
                import os
                PF.save()
                os.system('sudo shutdown -h now')
            elif action == 'reboot':
                import os
                PF.save()
                os.system('sudo reboot')
            elif action == 'sleep':
                duration = buf[2]
                time.sleep(float(duration))
            elif action == 'supply':
                enable = (buf[2] == 'on')
                PF.switch_power_supply(enable)
            elif action == 'supply5':
                enable = (buf[2] == 'on')
                PF.switch_power_supply5(enable)
            elif action == 'supply220':
                enable = (buf[2] == 'on')
                PF.switch_power_supply220(enable)
            elif action == 'variation':
                index = in_range(int(buf[2]), 0, len(energy_rates))
                mode = buf[3]
                illuminated = (buf[4] == 'light_on') if len(buf) >= 5 else True
                print(f'set variation {index} {mode}')
                if mode == 'play':
                    play_variation(PF, energy_rates[index], illuminated)
                elif mode == 'values':
                    set_variation_values(PF, energy_rates[index], illuminated)
            elif action == 'gain':
                value = int(buf[2])
                PF.set_energyshape_gain(value)
            elif action == 'brightness':
                value = int(buf[2])
                PF.set_energyshape_brightness(value)
            elif action == 'update-play' or action == 'update-values':
                rates = [ float(buf[2]), float(buf[3]), float(buf[4]), float(buf[5]), float(buf[6]), float(buf[7]), float(buf[8]), float(buf[9]), float(buf[10]), float(buf[11]) ]
                #mode = buf[12]
                #illuminated = (buf[13] == 'light_on')
                illuminated = False
                print(f'set variation {action} {rates}')
                if action == 'update-play':
                    play_variation(PF, rates, illuminated)
                elif action == 'update-values':
                    set_variation_values(PF, rates, illuminated)
                PF.save()
            elif action == 'fold':
                hour = int(buf[2])
                position = int(buf[3])
                print(f'fold {hour} {position}')
                PF.blink_led(hour, blink_color)
                PF.move_motor_to_position(hour, position)
            elif action == 'color':
                hour = int(buf[2])
                h = int(buf[3])
                s = int(buf[4])
                l = int(buf[5])
                print(f'color {hour} {h} {s} {l}')
                PF.set_led_color(hour, (h, s, l))
            elif action == 'reset':
                hour = int(buf[2])
                print(f'reset {hour}')
                if hour == 0:
                    play_reset(PF)
                else:
                    PF.blink_led(hour, blink_color)
                    PF.reset_motor_to_zero_position(hour)
            elif action == 'init':
                hour = int(buf[2])
                print(f'init {hour}')
                if hour == 0:
                    play_init(PF)
                else:
                    PF.set_led_color(hour, (0, 0, 0))
                    PF.blink_led(hour, blink_color)
                    PF.move_motor_to_position(hour, 0)
            elif action == 'microstepping':
                delay_us = int(buf[2])
                PF.set_motors_delay_us(delay_us)
                time.sleep(0.03)
            elif action == 'blink':
                period_ms = int(buf[2])
                PF.set_blink_period_ms(period_ms)
                time.sleep(0.03)
            elif action == 'pmax':
                num = int(buf[2])
                pos_max = int(buf[3])
                if num == 0:
                    PF.set_max_positions(pos_max)
                else:
                    PF.set_max_position(num, pos_max)
                time.sleep(0.03)
    else:
        print('Bad message format.')
        
def run_from_mqtt(host, PF):
    import paho.mqtt.client as mqtt
    import json
    
    # The callback for when the client receives a CONNACK response from the server.
    def on_connect(client, userdata, flags, rc):
        print("Connected with result code "+str(rc))
        print(f'{pname} is listening...')
        #client.subscribe("$SYS/#")  # Subscribe here
        client.subscribe('topic-prototypes', qos=2) # Subscribe here
        msg = {'type': 'message', 'dest': 'controlcenter', 'value': f'{pname} is ready'}
        data = json.dumps(msg)
        client.publish('topic-prototypes', data, qos=2)

    # The callback for when a PUBLISH message is received from the server.
    def on_message(client, userdata, databytes):
        msg = str(databytes.payload.decode())
        print(f'[{databytes.topic}] {msg}')
        if msg[0] == '<': 
            print(datagram)
            treat(PF, datagram)
        elif msg[0] == '{':
            data = json.loads(msg)
            if data['type'] == 'action':
                prototype_name = data['device']
                if prototype_name == pname:
                    command = data['command']
                    params = '|'.join(data['params'])
                    datagram = f'<{prototype_name}|{command}|{params}>'
                    print(datagram)
                    treat(PF, datagram)
            elif data['type'] == 'message':
                if data['dest'] == pname or data['dest'] == '*':                
                    print(data['value'])
            elif data['type'] == 'ping':
                if data['dest'] == pname or data['dest'] == '*':
                    print('Received ping request. Sending reply.')
                    msg = {'type': 'ping-reply', 'value': f'{pname} is awake'}
                    data = json.dumps(msg)
                    client.publish('topic-prototypes', data, qos=2)

    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    print(f"connecting to MQTT host: {host}")
    client.connect(host, 1883, 60)
    client.loop_forever() # Blocking call: see loop*() functions
    
def get_program_parameters():
    import argparse
    parser = argparse.ArgumentParser(
        prog='RPI Client',
        description='This program is an example of use of PlantSCREEN\'s driver.',
        epilog='Guillaume RIVIERE, 2023')

    subparsers = parser.add_subparsers(dest="subparser_name", help='sub-command help')

    # SETUP
    #parser_f = subparsers.add_parser('setup', help='Setup.')    
    #parser_f.add_argument('--position', type=int, nargs=1, required=True, help='Folding position in [1..10].')
    #parser_f.add_argument('--hour', type=int, nargs=1, required=True, help='Hour in [8..17] or 0 for all.')
    
    # FOLD
    parser_f = subparsers.add_parser('fold', help='Leaf folding.')    
    parser_f.add_argument('--position', type=int, nargs=1, required=True, help='Folding position in [1..10].')
    parser_f.add_argument('--hour', type=int, nargs=1, required=True, help='Hour in [8..17] or 0 for all.')

    # LED COLOR
    parser_c = subparsers.add_parser('color', help='LED color.')    
    parser_c.add_argument('--color', type=int, nargs=3, required=True, help='Color given as three integers in [0..255]: Hue Saturation Luminosity.')
    parser_c.add_argument('--hour', type=int, nargs=1, required=True, help='Hour in [8..17] or 0 for all.')

    # RESET
    parser_r = subparsers.add_parser('reset', help='Reset motors and LEDs.')
    parser_r.add_argument('--hour', type=int, nargs=1, required=True, help='Hour in [8..17] or 0 for all.')

    # INIT
    parser_i = subparsers.add_parser('init', help='Init motors and LEDs.')
    parser_i.add_argument('--hour', type=int, nargs=1, required=True, help='Hour in [8..17] or 0 for all.')

    # VARIATIONS
    parser_v = subparsers.add_parser('variation', help='Set variation.')
    parser_v.add_argument('--index', type=int, nargs=1, required=True, help='Variation in [0..6].')
    parser_v.add_argument('--values', action='store_true', help='Set position values only.')
    parser_v.add_argument('--illuminated', action='store_true', help='Set illumination on.')

    # MQTT
    parser_m = subparsers.add_parser('mqtt', help='Run from MQTT messages.')
    parser_m.add_argument('--host', type=str, nargs=1, required=False, help='MQTT host.')

    args = parser.parse_args()
    
    return args

def run_from_prompt(PF):
    print('>> PROMPT MODE <<')
    time.sleep(10)
    while (True):
        prompt = input('Give bytes: ')
        messages = prompt.split('&')
        for message in messages:
            print(f'Sending command = {message}')
            treat(PF, message)
        
def run_test(PF):
    time.sleep(1)
    
    #print('Sending...')
    #PF.send_led_color(0, (0, 0, 0))
    #PF.send_reset_motors_to_zero_position()
        
    #time.sleep(3)
    
    #for i in range(100):
    #    PF.send_led_color(8, (pf.H_BLUE, pf.S_MAX, pf.L_MAX))
    #    PF.send_led_wait(400)
    #    PF.send_led_color(8, (pf.H_GREEN, pf.S_MAX, pf.L_MAX))
    #    PF.send_led_wait(400)
    #    time.sleep(1)
    
    #PF.send_led_color(8, (pf.H_RED, pf.S_MED, pf.L_MED))
    #
    #PF.send_motors_delay_us(500)
    #PF.send_microstepping(pf.MS_SIXTEENTH)
    #
    #PF.send_leds_colors(colors)
    
    #PF.send_led_color(1, (pf.H_RED, pf.S_MAX, pf.L_MAX))
    
    #PF.move_motor_to_position(8, 3)
    #PF.move_motor_to_position(9, 3)
    #PF.move_motor_to_position(10, 3)
    #PF.move_motor_to_position(11, 3)
    #PF.move_motor_to_position(12, 6)
    #PF.move_motor_to_position(17, 6)
    
    #time.sleep(20)
    
    #hour = 8
    #
    #for i in range(10):
    #    hour = i+1
    #    #PF.send_reset_motor_to_zero_position(hour)
    #    #PF.move_motor_to_position(hour, 6)
    #    PF.move_motor_to_position(hour, 7)
    #    time.sleep(2)
    #    PF.move_motor_to_position(hour, 4)
    #    time.sleep(2)
    #    PF.move_motor_to_position(hour, 10)
    #    time.sleep(2)
    #    PF.move_motor_to_position(hour, 2)
    #    time.sleep(2)
    
    
    # Pos 0 to 220
    # at microstepping 1/16 
    #
    #  delay (us)      time (ms)
    #        150            5581
    #        160            5906
    #        161            5981
    #        162            5978
    #        163            6013 / 6063
    #
    
    i = 1
    
    hour = 8
    
    #if i == 0:
    #    PF.send_motors_delay_us(163)
    #    PF.send_microstepping(pf.MS_SIXTEENTH)
    #    PF.send_reset_motor_to_zero_position(hour)
    #elif i == 1:
    #    PF.send_motors_delay_us(163)
    #    PF.send_microstepping(pf.MS_SIXTEENTH)
    #    PF.move_motor_to_position(hour, 1)
    #else:
    #    PF.send_motors_delay_us(10000)
    #    PF.send_microstepping(pf.MS_SIXTEENTH)
    #    PF.move_motor_to_position(hour, 1)
        
    #PF.move_motors_to_positions(positions)
    
    #PF.move_motor_to_position_and_send_led_color(2, 5, (pf.H_GREEN, pf.S_MAX, pf.L_MED))
    
    #PF.move_motors_to_positions_and_send_leds_colors(positions, colors)
    
    #PF.send_reset_motor_to_zero_position(8)
    #PF.send_reset_motor_to_zero_position(9)
    #PF.send_reset_motor_to_zero_position(10)
    #PF.send_reset_motor_to_zero_position(11)
    #PF.send_reset_motor_to_zero_position(12)
    #PF.send_reset_motor_to_zero_position(17)
    
    #PF.send_reset_motors_to_zero_position()
    
    #PF.send_motors_delay_us(100)
    
    #PF.send_microstepping(pf.MS_FULL)

        
def main():
    args = get_program_parameters()
    from params import max_positions
    from params import id_number
    
    PF = DriverPlantFORM()
    PF.set_motors_delay_us(80)  
    PF.set_microstepping(pf.MS_SIXTEENTH)
    PF.set_max_positions(220)
    for (num, steps) in max_positions:
        PF.set_max_position(num, steps)
    PF.set_max_failed_steps(500)
    PF.set_blink_period_ms(200)

    print(PF.pos_max)
    
    if len(vars(args)) > 1:
        if args.subparser_name == 'mqtt':
            from get_ip import get_access_point_ip
            host = args.host[0] if args.host is not None else get_access_point_ip() # '192.168.0.10' # 'rpi-mqtt-server'
            run_from_mqtt(host, PF)
        elif args.subparser_name == 'fold':
            position = args.position[0]
            hour = args.hour[0]
            PF.blink_led(hour, blink_color)
            PF.move_motor_to_position(hour, position)
            num = PF.wait_end_of_motion()
            print(f'motion done: {num}')
        elif args.subparser_name == 'color':
            h, s, l = args.color
            hour = args.hour[0]
            PF.set_led_color(hour, (h, s, l))
        elif args.subparser_name == 'reset':
            hour = args.hour[0]
            if hour == 0:
                #for hour in range(8, 18):
                #    PF.send_reset_motor_to_zero_position(hour)
                #    num = PF.wait_end_of_motion()
                #    print(f'reset done: {num}')
                play_reset(PF)
            else:
                PF.blink_led(hour, blink_color)
                PF.reset_motor_to_zero_position(hour)
        elif args.subparser_name == 'init':
            hour = args.hour[0]
            if hour == 0:
                play_init(PF)
            else:
                PF.set_led_color(hour, (0, 0, 0))
                PF.blink_led(hour, blink_color)
                PF.move_motor_to_position(hour, 0)
        elif args.subparser_name == 'variation':
            index = args.index[0]
            if index > 6:
                index = 6
            elif index < 0:
                index = 0
            if args.values:
                set_variation_values(PF, energy_rates[index], args.illuminated)
            else:
                play_variation(PF, energy_rates[index], args.illuminated)
        else:
            print('Unknown command.')
    else:
        run_from_prompt(PF)
        
if __name__ == '__main__':
    import sys
    main()
    sys.exit(0)

