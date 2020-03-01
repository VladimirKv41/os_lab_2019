#!/bin/bash

cat /dev/random | od -w2 -An -d | head -150 > numbers.txt
declare -a arr[150]
count=1
while read LINE
do
arr[$count]=$(($LINE))
count=$(( $count + 1 ))
done < numbers.txt
./average.sh ${arr[@]}
echo ${arr[1]}
echo ${arr[@]}