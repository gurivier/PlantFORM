#!/bin/sh

ip=192.168.0.10

echo "Ping"

mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|ping>"
