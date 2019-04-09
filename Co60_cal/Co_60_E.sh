#!/b=efficiency_Co60_X.mac
count=6
COUNTER=0
         until [  $COUNTER -gt $count ]; do
             ../build/ge-detector ../macros/${mac/X/$COUNTER}
             let COUNTER+=1
         done

