#!/bin/sh

. mqtt_params.sh
. utils.sh

pname='plantform1'

echodate "Set color to $pname"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|color|8|96|255|255>"  ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|color|9|96|255|255>"  ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|color|10|96|255|255>" ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|color|11|96|255|255>" ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|color|12|96|255|255>" ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|color|13|96|255|255>" ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|color|14|96|255|255>" ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|color|15|96|255|255>" ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|color|16|96|255|255>" ; sleep 2
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|color|17|96|255|255>" ; sleep 2

sleep 5

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|color|0|0|0|0>"


