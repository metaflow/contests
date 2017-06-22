#!/bin/bash
DIR=$(dirname "$(readlink -f "$0")")
# RUN_TESTS=1 py $DIR/memory_usage.py 5000000 $1/$2
RUN_TESTS=1 timeout 5s $1/$2
if [ $? -eq 124 ];
then
    echo "TLE"
fi
