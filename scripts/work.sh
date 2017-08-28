#!/bin/bash
mac=$1
count=$2
COUNTER=0
         until [  $COUNTER -gt $count ]; do
             ../build/ge-detector ../macros/$mac
             let COUNTER+=1
         done

