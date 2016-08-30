#!/bin/bash
HAS_INPUT=false
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
for i in `find $1 -regex ".*/$2\.in[^.]*"`
do
  HAS_INPUT=true
  echo $i
  $1/$2 < $i > $i.o
  #$SCRIPT_DIR/test_timeout -t 10 -m 200000 $1/$2 < $i > $i.o
  # /usr/bin/time --format "time %U" $1/$2 < $i > $i.o
  cat $i.o
  if [ -f $i.out ];
  then
    echo '------------------'
    if diff $i.o $i.out; then echo "OK $i"; fi
    echo '------------------'
  fi  
done
if [ ! "$HAS_INPUT" = true ];
then
  $1/$2
fi
