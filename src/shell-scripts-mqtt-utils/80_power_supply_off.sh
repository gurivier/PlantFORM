#!/bin/sh

. ./mqtt_params.sh
. ./utils.sh
. ./pname.sh

echodate "[$pname] Power supply OFF"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|supply|off>"
