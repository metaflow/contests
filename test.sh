#!/bin/bash
# set -x
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
RUN_TESTS=1 timeout 15s $1/$2
if [ $? -eq 124 ];
then
    echo "TLE"
fi
