#! bin/bash

i=0
while [ "$i" -lt "$1" ];
do
	printf "$((i + 1)) -> $(cat log | grep -c $i)\n"
	((i=i+1))
done

