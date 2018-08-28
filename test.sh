#!/bin/bash
# set -x
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
# RUN_TESTS=1 py $DIR/memory_usage.py 5000000 $1/$2
RUN_TESTS=1 timeout 15s $1/$2
if [ $? -eq 124 ];
then
    echo "TLE"
fi
