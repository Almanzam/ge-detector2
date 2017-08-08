#!/bin/bash
COUNTER=0
         until [  $COUNTER -gt 24 ]; do
             ../build/ge-detector ../macros/Copper_cobalt.mac
             let COUNTER+=1
         done

