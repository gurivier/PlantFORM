#!/bin/sh

. ./mqtt_params.sh
. ./utils.sh
. ./pname.sh

echodate "[$pname] Init"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|init|0>"
