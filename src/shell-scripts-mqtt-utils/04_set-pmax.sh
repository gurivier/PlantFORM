#!/bin/sh

. mqtt_params.sh
. utils.sh

pname='plantform1'

echodate "[$pname] Set pmax"

#if [ $# -eq 2 ];
#then
#    num=$1
#    pmax=$2
#else
#    echo 'Usage: '$0' <num> <pmax>'
#fi
#
#mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|"$num"|"$pmax">"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|1|260>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|2|260>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|3|260>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|4|260>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|5|260>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|6|260>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|7|260>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|8|260>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|9|260>"
sleep 0.03s
mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|pmax|10|260>"
sleep 0.03s

