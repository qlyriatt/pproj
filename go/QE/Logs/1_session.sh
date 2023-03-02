#!/bin/bash

session=asdfadfasas3432423ewd3da

if [ $# != 0 ]
then
    session=$1
fi

grep "session=\"$session\"" logs.txt -n | cut -d: -f1 | awk -f print.awk logs.txt
