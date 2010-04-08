#!/bin/sh
if test -f Makefile; then
  make distclean
fi

rm -f *.tar.* *.tgz
rm -Rf autom4te.cache
rm -f jpiicsv.pro.user Makefile.Debug Makefile.Release Makefile.in aclocal.m4 configure depcomp install-sh missing
