#!/bin/bash

read -p "Do you want to remove old key files? " -n 1 -r
echo

if [[ $REPLY =~ ^[Yy]$ ]]
then
        read -p "Are you sure? " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
        dir=$(pwd)
        find $dir -type f -name "*.pem" -exec rm -rf {} \;
        fi
fi

rm -f key.c

read -p 'Enter Device Name: ' devicename
echo

read -p "Are you sure? " -n 1 -r
echo

if [[ $REPLY =~ ^[Yy]$ ]]
then
        python3 create_keys.py -d $devicename -e
        echo Created $devicename certificates
        exit 1
fi