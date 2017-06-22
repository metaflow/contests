#!/bin/bash

DIRECTORY=$( cd "$( dirname $0 )" && pwd )
PYTHON="py -2 "

$PYTHON $DIRECTORY/dcj.py $@
