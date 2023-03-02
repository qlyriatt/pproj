#!/bin/bash

# сессия по умолчанию
session=asdfadfasas3432423ewd3da

# сессия параметром
if [ $# != 0 ]
then
    session=$1
fi

# все <Request> данной сессии с тегом <type>Balance
sessions=$(grep "session=\"$session\"" logs.txt -A1 -n | grep Balance -B1 | grep session)

# для данной сессии нет данных
if [ "$sessions" == "" ]
then
    exit
fi

# номера строк <Request> данной сессии с тегом <type>Balance
# printSurely=$(echo "$sessions" | cut -d':' -f1 -)

# id сообщений, <Request> которых содержит тег <type>Balance
ids=$(echo "$sessions" | cut -d' ' -f3 | cut -d'=' -f2 | cut -d'>' -f1)

# получить номера строк для печати по каждому id
getNums()
{
    while IFS="\n" read -r id
    do
        echo $(grep "id=$id" -n logs.txt | cut -d':' -f1)
    done
}

# номера строк для печати по каждому id
nums=$(echo "$ids" | getNums)

# вывод сообщений с тегом <type>Balance для данной сессии в порядке появления в logs.txt
echo "$nums" | cut -d' ' -f1- --output-delimiter=$'\n' | sort -n | awk -f print.awk logs.txt
