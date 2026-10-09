#!/bin/sh

. mqtt_params.sh
. utils.sh

pname='plantform1'

echodate "Ping $pname"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|ping>"
