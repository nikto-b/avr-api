#!/bin/bash

if [[ $1 == "" ]]; then
    echo "Usage:"
    echo "mypin2portpin.sh [MYPIN]"
    echo "mypin2portpin.sh [BEGIN_PORT] [MYPIN]"
    exit
fi

if [[ $1 == *'usage'* || $1 == *'help'* ]]; then
    echo "Usage:"
    echo "mypin2portpin.sh [MYPIN]"
    echo "mypin2portpin.sh [BEGIN_PORT] [MYPIN]"
    exit
fi
START=0
if [[ $2 != '' ]]; then
    START=$(printf "%d\n" \'$1)
    START=$(((START - 65)))
    MYPIN=$2
else
    MYPIN=$1
fi



PORT=$((($MYPIN / 8)))

PIN=$((($MYPIN % 8)))

PORT=$((($PORT + 65 + $START)))

PORTCHAR=$(printf "\x$(printf %x $PORT)")

echo "PORT: $PORTCHAR; PIN: $PIN"
