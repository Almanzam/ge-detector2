#!/bin/bash
mac=efficiency_Co60_X.mac
count=12
COUNTER=0
         until [  $COUNTER -gt $count ]; do
             ../build/ge-detector ../macros/${mac/X/$COUNTER}
             let COUNTER+=1
         done

