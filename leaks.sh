#!/bin/bash

if [[ -z "$1" ]]; then
	NAME="a.out"
else
	NAME="$1"
fi

NC='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'

MEMCHECK=""

find_memcheck()
{
	if [[ "$OSTYPE" == "darwin"* ]] && which leaks; then
			MEMCHECK="leaks"
	elif which valgrind; then
		MEMCHECK="valgrind"
	else
		echo "Could not find memcheck, please install valgrind!" 1>&2
		exit 1
	fi
}

find_memcheck

"$MEMCHECK" "$NAME"\
	&& echo -e "${GREEN}No leaks found!${NC}"\
	|| echo -e "${RED}Leaks! ($?) ${NC}"
