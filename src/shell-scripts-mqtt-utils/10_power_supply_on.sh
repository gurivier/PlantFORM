#!/bin/sh

. ./mqtt_params.sh
. ./utils.sh
. ./pname.sh

echodate "[$pname] Power supply ON"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|supply|on>"
