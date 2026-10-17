#!/bin/sh

. ./mqtt_params.sh
. ./utils.sh
. ./pname.sh

echodate "[$pname] Set variations"

echodate "==V0==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation-play|0>"    ; sleep 40 ;  bip
echodate "==V1==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation-play|1>"    ; sleep 40 ;  bip
echodate "==V2==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation-play|2>"    ; sleep 40 ;  bip
echodate "==V3==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation-play|3>"    ; sleep 40 ;  bip
echodate "==V4==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation-play|4>"    ; sleep 40 ;  bip
echodate "==V5==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation-play|5>"    ; sleep 40 ;  bip
echodate "==V6==" ; mosquitto_pub -h $HOST -q 2 -t "$TOPIC" -m "<"$pname"|variation-play|6>"    ; sleep 40 ;  bip
