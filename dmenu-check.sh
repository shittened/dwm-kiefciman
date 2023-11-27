#! /bin/bash

while true
do
	if [ "$(ps -e | grep dmenu | wc -l)" == "3" ] || [ "$(ps -e | grep dmenu | wc -l)" == "4" ]
	then
		eww open dmenu && dmenu_run
	else
		eww close dmenu
	fi
	sleep 1
	echo "$(ps -e | grep dmenu | wc -l)"
done
