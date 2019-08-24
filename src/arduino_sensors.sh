#!/bin/sh
. /usr/share/libubox/jshn.sh
bletool on
bletool connect e0:50:41:45:7b:d2 0 1
while true
do
json_load "$(bletool read_value 1 14)"
json_get_var pressure value
pressure=`str2float $pressure`" kPa"
json_load "$(bletool read_value 1 16)"
json_get_var tempreture value
tempreture=`str2float $tempreture`" C"
json_load "$(bletool read_value 1 18)"
json_get_var humidity value
humidity=`str2float $humidity`" %"
json_load "$(bletool read_value 1 20)"
json_get_var AccelerationX value
AccelerationX=`str2float $AccelerationX`
json_load "$(bletool read_value 1 22)"
json_get_var AccelerationY value
AccelerationY=`str2float $AccelerationY`
json_load "$(bletool read_value 1 24)"
json_get_var AccelerationZ value
AccelerationZ=`str2float $AccelerationZ`
date=`date +"%Y%m%d%H%M%S"`
json_init
json_add_string "api" "/user/data"
json_add_object "data"
json_add_string "date" "$date"
json_add_string "Atmospheric pressure" "$pressure"
json_add_string "Temperature" "$tempreture"
json_add_string "Humidity" "$humidity"
json_add_string "X" "$AccelerationX"
json_add_string "Y" "$AccelerationY"
json_add_string "Z" "$AccelerationZ"
json_close_object
json_close_object
data=`json_dump`
echo $data
bletool write_value 1 12 11         
sleep 0.1                           
bletool write_value 1 12 00
ubus call mqtt pub "$data" 
sleep 4                    
done           