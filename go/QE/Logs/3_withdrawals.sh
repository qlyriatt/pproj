#!/bin/bash
grep '<type>Withdrawal' -n -C1 logs.txt | grep '<Response' -C2 | 
grep '<code>[[:digit:]]\{3\}[^0]' | cut -d'-' -f1 | awk -f print.awk logs.txt
