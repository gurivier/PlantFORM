#!/bin/sh

mosquitto_sub -F '[@Y-@m-@d @H:@M:@S] [%t] %p ' -h 192.168.0.10 -q 2 -t topic-prototypes
