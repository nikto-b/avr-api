#!/bin/bash

if [[ -z "$1" ]]; then
    CERT=$(cppcheck cppcheck --force --addon=cert -q ./Src/*.cpp ./Include/*.hpp 2>&1)
    INFO="Checked all"
else
    CERT=$(cppcheck cppcheck --addon=cert -q $1 2>&1)
    INFO="Checked $1"
fi

if [[ -z "$CERT" ]]; then
    printf '\033[1;32m'
    CERT="OK"
else
    printf '\033[1;34m'
fi

echo -e "CODE CHECK: \n$INFO\n"$CERT'\033[0m'
