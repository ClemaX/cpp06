#!/bin/sh

# Abort on error
set -e

TEMPLATECPP='#include "$CLASSNAME.hpp"

$CLASSNAME::$CLASSNAME()
{
	// TODO: Implement default contructor
}

$CLASSNAME::~$CLASSNAME()
{
	// TODO: Implement default destructor
}

$CLASSNAME::$CLASSNAME($CLASSNAME const& src)
{
	// TODO: Implement copy contructor
}

$CLASSNAME&		$CLASSNAME::operator=($CLASSNAME const& src)
{
	// TODO: Implement = operator
	return *this;
}

std::ostream&	operator<<(std::ostream& os, $CLASSNAME const& src)
{
	// TODO: Implement << operator
	return os;
}'

TEMPLATEHPP='#pragma once

#include <iostream>
#include <string>

class $CLASSNAME
{
private:

public:
	$CLASSNAME();
	~$CLASSNAME();

	$CLASSNAME($CLASSNAME const& src);

	$CLASSNAME&	operator=($CLASSNAME const& rhs);
};

std::ostream&	operator<<(std::ostream& os, $CLASSNAME const& src);
'

# subst
if ! type envsubst > /dev/null 2>&1; then
	subst()
	{
		sed "s/\$CLASSNAME/$CLASSNAME/g"
	}
else
	subst()
	{
		envsubst
	}
fi

generate_cpp()
{
	if [ -f "$1" ]; then
		echo "generate_cpp: $1: File exists!"
	else
		cat <<-EOF | subst > "$1"
			$TEMPLATECPP
		EOF
	fi
}

generate_hpp()
{
	if [ -f "$1" ]; then
		echo "generate_hpp: $1: File exists!"
	else
		cat <<-EOF | subst > "$1"
			$TEMPLATEHPP
		EOF
	fi
}

generate_srcs()
{
	CLASSNAME="$1"

	export CLASSNAME
	generate_cpp "$CLASSNAME.cpp"
	generate_hpp "$CLASSNAME.hpp"
}


if [ -z "$1" ]; then
	echo "Usage:	$0 DEST [CLASS]..." >&2
	exit 1
fi

cd "$1"; shift

while [ ! -z "$1" ]; do
	generate_srcs "$1"; shift
done
