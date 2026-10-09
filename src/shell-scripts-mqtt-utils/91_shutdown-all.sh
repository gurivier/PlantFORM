#!/bin/sh

. mqtt_params.sh
. utils.sh

echodate "Powering off all the prototypes"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<all|shutdown>"
