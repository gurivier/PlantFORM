#!/bin/sh

. mqtt_params.sh
. utils.sh

pname='plantform1'

echodate "Reboot $pname"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|reboot>"


