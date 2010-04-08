#!/bin/sh
aclocal
automake -ac
autoconf
echo "run ./configure"
