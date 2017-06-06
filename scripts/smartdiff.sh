#!/bin/bash
LC1=$(wc -l $1 | sed 's/^\([0-9]*\) .*/\1/');
LC2=$(wc -l $2 | sed 's/^\([0-9]*\) .*/\1/');
if [ "$LC1" == "$LC2" ];
then
    i=0
    while read left <&3 && read right <&4; do
        ((i++));
        diff --side-by-side --strip-trailing-cr -t --width=40 <(echo ${left}) <(echo ${right}) | sed "s/^/${i} | /";
    done 3<$1 4<$2
else
    diff --side-by-side --strip-trailing-cr -t --width=40 $1 $2 | cat -n | sed 's/^ *\([[:digit:]]*\) */\1 | /';
fi
