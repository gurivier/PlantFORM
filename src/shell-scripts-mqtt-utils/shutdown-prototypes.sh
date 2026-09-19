#!/bin/sh

ip=192.168.0.10

echo "Powering off prototypes"

mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<all|shutdown>"


