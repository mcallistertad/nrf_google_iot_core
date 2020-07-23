#!/bin/bash

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
