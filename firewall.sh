#!/bin/bash

sed 's/ //g' "$1" | grep -o '^[^#]*' |sort |uniq > filters-list.txt 

final=""


while read packet;
do
	while read filter;
	do
		pack="$packet"
		pack=`echo "$pack" | sed 's/ //g'`
		IFS=','
		 read -ra  filter_field <<< "$filter"
		 for field in "${filter_field[@]}"; do
	


			pack=$(echo "$pack" | ./firewall.exe "$field" ) 

			if [ -z "$pack" ];
			then 
				break
			fi

		done
		newline=$'\n'
		final+="$pack"
		final+="$newline" 
		
	done < "filters-list.txt"
done 

echo "$final" | sed 's/ //g' | grep -o '^[^#]*' | sort |uniq