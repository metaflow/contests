#!/bin/zsh
DIR=$(dirname "$(readlink -f "$0")")
if ! [ -f "$1.cc" ];
then
  cp "$DIR/template.cpp" "$1.cc"
fi
subl "$1.cc" "$1.in.out" "$1.in"
