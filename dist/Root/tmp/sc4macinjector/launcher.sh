#!/bin/bash
LIBS="$HOME/Documents/SimCity 4/Plugins/libinjector.dylib"
if [ ! -z "$DYLD_INSERT_LIBRARIES" ]; then
	LIBS="$LIBS:$DYLD_INSERT_LIBRARIES"
fi

export DYLD_INSERT_LIBRARIES="$LIBS"
CURDIR=$(dirname "$0")

mkdir -p "$HOME/Documents/SimCity 4"
LOGPATH="$HOME/Documents/SimCity 4/libinjector.log"
echo "$CURDIR" > "$LOGPATH"
echo "$@" >> "$LOGPATH"
echo >> "$LOGPATH"
env >> "$LOGPATH"
echo >> "$LOGPATH"

"$CURDIR/Sim City 4 Deluxe Editionsub2" "$@" >> "$LOGPATH" 2>&1 &
