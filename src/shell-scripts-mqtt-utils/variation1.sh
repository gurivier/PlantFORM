#!/bin/sh

ip=192.168.0.10

echo "Set variation"


#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantscreen|variation|0>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantscreen|variation|1>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantscreen|variation|2>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantscreen|variation|3>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantscreen|variation|4>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantscreen|variation|5>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantscreen|variation|6>"    ; sleep 30 ;  bip

#sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnscreen|variation|0>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnscreen|variation|1>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnscreen|variation|2>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnscreen|variation|3>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnscreen|variation|4>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnscreen|variation|5>"    ; sleep 30 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnscreen|variation|6>"    ; sleep 30 ;  bip

#sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|0|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|1|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|2|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|3|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|4|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|5|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|6|play|light_off>"    ; sleep 40 ;  bip

#sleep 30 ;  bip
mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|variation|0|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|variation|1|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|variation|2|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|variation|3|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|variation|4|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|variation|5|play|light_off>"    ; sleep 40 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|variation|6|play|light_off>"    ; sleep 40 ;  bip



#var=0
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnscreen|variation|"$var">"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantscreen|variation|"$var">"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|variation|"$var"|play|light_off>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|"$var"|play|light_off>"


#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|reset|9>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|init|0>"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|variation|0|play|light_off>"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|microstepping|80>"
#sleep 0.03s
#sleep 20
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|1|play|light_off>"  ; sleep 30 ; bip  
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|2|play|light_off>"  ; sleep 30 ; bip  
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|3|play|light_off>"  ; sleep 30 ; bip  
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|4|play|light_off>"  ; sleep 30 ; bip  
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|5|play|light_off>"  ; sleep 30 ; bip  
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|6|play|light_off>"  ; sleep 30 ; bip  

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|variation|1|play|light_off>"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|variation|1|play|light_off>"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantscreen|variation|1|values>"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|8|0>"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantscreen|variation|1|play|light_off>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnscreen|variation|1|play|light_off>"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|8|0>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|5>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|10|5>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|11|7>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|12|7>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|13|7>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|14|10>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|15|7>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|16|7>"
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|17|0>"

#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|8|1>"   ; sleep 5
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|2>"   ; sleep 5
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|10|3>"  ; sleep 5
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|11|4>"  ; sleep 5
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|12|5>"  ; sleep 5
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|13|6>"  ; sleep 5
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|14|7>"  ; sleep 5
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|15|8>"  ; sleep 5
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|16|9>"  ; sleep 5
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|17|10>" ; sleep 5


# PHOTOS DEPLIEMENT
#sleep 10 ; bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|0>"   ; sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|1>"   ; sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|2>"   ; sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|3>"   ; sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|4>"   ; sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|5>"   ; sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|6>"   ; sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|7>"   ; sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|8>"   ; sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|9>"   ; sleep 10 ;  bip
#mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<plantform|fold|9|10>"  ; sleep 10 ;  bip


exit

pos=0
d=2

#echo "7"  ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|7|"$pos">"  ; sleep "$d"
#echo "8"  ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|8|"$pos">"  ; sleep "$d"
#echo "9"  ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|9|"$pos">"  ; sleep "$d"
#echo "10" ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|10|"$pos">" ; sleep "$d"
#echo "11" ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|11|"$pos">" ; sleep "$d"
#echo "12" ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|12|"$pos">" ; sleep "$d"
#echo "13" ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|13|"$pos">" ; sleep "$d"
#echo "14" ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|14|"$pos">" ; sleep "$d"
#echo "15" ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|15|"$pos">" ; sleep "$d"
#echo "16" ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|16|"$pos">" ; sleep "$d"
#echo "17" ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|17|"$pos">" ; sleep "$d"
#echo "18" ; mosquitto_pub -h $ip -q 2 -t topic-prototypes -m "<cairnform|fold|18|"$pos">" ; sleep "$d"

# hour => ring
#  7       PB
#  8          9h
#  9         17h
# 10         15h
# 11          7h
# 12          8h
# 13         11h
# 14         13h
# 15         10h
# 16         12h
# 17         16h
# 18         14h

# 11          7h
# 12          8h
#  8          9h
# 15         10h
# 13         11h
# 16         12h
# 14         13h
# 18         14h
# 10         15h
# 17         16h
#  9         17h




# 7h:  off
# 8h:  ok
# 9h:  ok
# 10h: ok
# 11h: ok
# 12h: ok
# 13h: ok
# 14h: ok
# 15h: ok
# 16h: ok
# 17h: ok
# 18h: off
