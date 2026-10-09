#!/bin/sh

. mqtt_params.sh
. utils.sh

pname='plantform1'

echodate "[$pname] Gain ON"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|gain|0>"
