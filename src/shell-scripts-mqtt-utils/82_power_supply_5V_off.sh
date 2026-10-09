#!/bin/sh

. mqtt_params.sh
. utils.sh

pname='plantform1'

echodate "[$pname] Power supply 5V OFF"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|supply5|off>"
