#!/bin/bash
RUN_TESTS=1 timeout 5s $1/$2
if [ $? -ne 0 ];
then
    echo "TLE"
fi
