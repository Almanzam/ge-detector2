#!/bin/bash
mac=Cs137_X.mac
count=2
COUNTER=0
         until [  $COUNTER -gt $count ]; do
             ../build/ge-detector ../macros/${mac/X/$COUNTER}
             let COUNTER+=1
         done