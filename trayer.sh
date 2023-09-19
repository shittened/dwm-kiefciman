#~ /bin/bash

checktrayer=$(ps | grep trayer | wc -l)

if [ "$checktrayer" = "0" ]
then
	trayer &
else
	pkill trayer
fi
