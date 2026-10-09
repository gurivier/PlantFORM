#!/bin/sh

. mqtt_params.sh
. utils.sh

pname='plantform1'

echodate "Supply 220V $pname"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|supply220|on>"
