#!/bin/sh

ip=192.168.0.10

echo "Set pmax"

#if [ $# -eq 2 ];
#then
#    num=$1
#    pmax=$2
#else
#    echo 'Usage: '$0' <num> <pmax>'
#fi
#
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|pmax|"$num"|"$pmax">"

mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|pmax|1|260>"
sleep 0.03s
mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|pmax|2|260>"
sleep 0.03s
mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|pmax|3|260>"
sleep 0.03s
mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|pmax|4|260>"
sleep 0.03s
mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|pmax|5|260>"
sleep 0.03s
mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|pmax|6|260>"
sleep 0.03s
mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|pmax|7|260>"
sleep 0.03s
mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|pmax|8|260>"
sleep 0.03s
mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|pmax|9|260>"
sleep 0.03s
mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|pmax|10|260>"
sleep 0.03s

