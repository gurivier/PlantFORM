#!/bin/sh

. ./mqtt_params.sh
. ./utils.sh
. ./pname.sh

echodate "[$pname] Set pmax"

#if [ $# -eq 2 ];
#then
#    hour=$1
#    pmax=$2
#else
#    echo 'Usage: '$0' <hour> <pmax>'
#fi
#
#mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|"$hour"|"$pmax">"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|8|80>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|9|80>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|10|80>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|11|80>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|12|80>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|13|80>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|14|80>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|15|80>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|16|80>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|17|80>"
sleep 0.03s

