#!/bin/bash

count=0
#let "count++"
while true 
do 
    let "count++"
    echo "running count = $count"
    #./reset_usb_port.sh
    ./simple-viewer-recoder
    #sleep 10
    #kill -9 $(pidof simple-viewer-recoder)
done
