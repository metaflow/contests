#!/bin/bash
HAS_INPUT=false
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
for i in `find $1 -regex ".*/$2\.in[^.]*"`
do
  HAS_INPUT=true
  START_TIME=`date +%s%N`
  timeout 5s $1/$2 < $i > $i.o
  # /usr/bin/time --format "time %U" $1/$2 < $i > $i.o
  if [ $? -eq 0 ];
  then
      if [ -f $i.out ];
      then
          if diff --strip-trailing-cr $i.o $i.out > /dev/null
          then
              END_TIME=`date +%s%N`
              echo "OK " $(((END_TIME - START_TIME)/1000000)) "ms " $i;
          else
              echo "FAILED " $i;
              $SCRIPT_DIR/smartdiff.sh $i.o $i.out
          fi
      else
          echo $i
          cat $i.o
      fi
  else
      echo "TLE " $i
  fi
done
if [ ! "$HAS_INPUT" = true ];
then
    $1/$2
fi
