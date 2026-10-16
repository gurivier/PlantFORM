#!/bin/sh

. ./mqtt_params.sh
. ./utils.sh
. ./pname.sh

echodate "[$pname] Gain OFF"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|gain|0|64>"
