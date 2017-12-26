#!/bin/bash
export DYLD_INSERT_LIBRARIES="$HOME/Documents/SimCity 4/Plugins/libinjector.dylib"
CURDIR=$(dirname "$0")

mkdir -p "$HOME/Documents/SimCity 4"
LOGPATH="$HOME/Documents/SimCity 4/libinjector.log"
echo "$CURDIR" > "$LOGPATH"
echo "$@" >> "$LOGPATH"
echo >> "$LOGPATH"
env >> "$LOGPATH"
echo >> "$LOGPATH"

"$CURDIR/Sim City 4 Deluxe Editionsub2" "$@" >> "$LOGPATH" 2>&1 &
