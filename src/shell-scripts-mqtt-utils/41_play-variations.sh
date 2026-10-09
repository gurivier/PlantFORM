#!/bin/sh

. mqtt_params.sh
. utils.sh

pname='plantform1'

echodate "[$pname] Set variations"

echodate "==V0==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation|0|play>"    ; sleep 40 ;  bip
echodate "==V1==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation|1|play>"    ; sleep 40 ;  bip
echodate "==V2==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation|2|play>"    ; sleep 40 ;  bip
echodate "==V3==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation|3|play>"    ; sleep 40 ;  bip
echodate "==V4==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation|4|play>"    ; sleep 40 ;  bip
echodate "==V5==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation|5|play>"    ; sleep 40 ;  bip
echodate "==V6==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation|6|play>"    ; sleep 40 ;  bip
