#!/bin/bash

echo $# parameters
sum=0
for param in $@
do
sum=$(($sum + $param))
done
echo average - $(($sum/$#))