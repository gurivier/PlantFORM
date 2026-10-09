#!/bin/sh

. mqtt_params.sh
. utils.sh

pname='plantform1'

echodate "[$pname] Setup"

motor_delay_us=250
step_pos_max=20
blink_period_ms=200

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|setup|"$motor_delay_us"|"$step_pos_max"|"$blink_period_ms">"
