#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
if (! [ -f "$1.cc" ]) && (! [ -f "$1.cc" ]);
then
  cp "$DIR/template.cc" "$1.cc"
fi
"${EDITOR}" -n --eval "(open-problem \"${1}.cc\" \"${1}.in\" \"${1}.out\")"
