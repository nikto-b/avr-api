#!/bin/bash

if [[ $1 == "" || $2 == "" ]]; then
    echo "Usage:"
    echo "portpin2mypin.sh [PORT] [PIN_NUM]"
    echo "portpin2mypin.sh [BEGIN_PORT] [PORT] [PIN_NUM]"
    exit
fi

if [[ $1 == *'usage'* || $1 == *'help'* ]]; then
    echo "Usage:"
    echo "portpin2mypin.sh [PORT] [PIN_NUM]"
    echo "portpin2mypin.sh [BEGIN_PORT] [PORT] [PIN_NUM]"
    exit
fi

if [[ $3 == "" ]]; then
    A=$(printf "%d\n" \'$1)
    echo "$((((((($A - 65)) * 8)) + $2)))"
else
    A=$(printf "%d\n" \'$2)
    B=$(printf "%d\n" \'$1)
   echo "$((((((($A - 65 - (($B - 65)))) * 8)) + $3)))"
fi
printf "\n";
