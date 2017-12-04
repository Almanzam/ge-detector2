#!/bin/bash
count=$1
COUNTER=0
         until [  $COUNTER -gt $count ]; do
             qsub ./efficiency.pbs
             let COUNTER+=1
         done

