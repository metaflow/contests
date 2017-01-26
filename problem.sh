#!/bin/sh
DIR=$(dirname "$(readlink -f "$0")")
if (! [ -f "$1.cpp" ]) && (! [ -f "$1.cpp" ]);
then
  cp "$DIR/template.cpp" "$1.cpp"
fi
#"C:\Program Files\Sublime Text 3\subl.exe" $1.cpp $1.in.out $1.in
"C:\Users\mgoncharov\bin\emacs-25.1\bin\emacsclient.exe" $1.cpp $1.in.out $1.in
