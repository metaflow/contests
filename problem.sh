#!/bin/sh
DIR=$(dirname "$(readlink -f "$0")")
if (! [ -f "$1.cpp" ]) && (! [ -f "$1.cpp" ]);
then
  cp "$DIR/template.cpp" "$1.cpp"
fi
"${EDITOR}" -n --eval "(open-problem \"${1}.cpp\" \"${1}.in\" \"${1}.in.out\")"
