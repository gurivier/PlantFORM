#!/bin/sh

ip=192.168.0.10

echo "Set color"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|color|12|0|128|255>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|color|12|0|0|0>"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|color|13|0|255|255>"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|color|0|0|0|0>"

mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|color|5|96|255|255>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|color|6|96|255|255>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|color|7|96|255|255>"

#sleep 1

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|color|0|0|0|0>"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|color|0|0|0|0>"


