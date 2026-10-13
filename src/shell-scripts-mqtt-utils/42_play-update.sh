#!/bin/sh

. ./mqtt_params.sh
. ./utils.sh

pname='plantform1'

echodate "[$pname] Update forecasts"

#mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|update-play|0.595|0.797|0.924|0.991|1.000|0.962|0.875|0.737|0.524|0.315>"

json='{ "type": "action", "device": "'$pname'", "command": "update-play", "params": [ "0.595", "0.797", "0.924", "0.991", "1.000", "0.962", "0.875", "0.737", "0.524", "0.315" ] }'

echo $json | json_pp

mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m $json

