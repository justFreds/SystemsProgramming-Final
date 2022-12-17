#!/bin/bash
INPUT="sub.out"
while true
do
    $INPUT | while read -r payload
    do
        if [[ "$payload" == "1" ]]; then
            echo "Input detected"
            ./npc.sh
        fi
    done    
done