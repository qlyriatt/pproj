#!/bin/bash
f='logs.txt'
if [ $# != 0 ]
then
	f=$1
fi

uniques=$(grep '<type>' $f | cut -d'>' -f2 | cut -d'<' -f1 | uniq -c)
echo "$uniques" | while NFS="\n" read -r num name; do
	echo $name": "$num
done
