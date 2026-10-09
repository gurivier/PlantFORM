#!/bin/sh

. mqtt_params.sh
. utils.sh

pname='plantform1'

echodate "[$pname] Gain values"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|gain|-3>"  ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|gain|-5>"  ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|gain|-7>"  ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|gain|-10>" ; sleep 2

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|gain|3>"   ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|gain|5>"   ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|gain|7>"   ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|gain|10>"  ; sleep 2

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|gain|0>"
