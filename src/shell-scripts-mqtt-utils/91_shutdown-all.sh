#!/bin/sh

. mqtt_params.sh
. utils.sh

echodate "[all] Shutdown"

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<all|shutdown>"
