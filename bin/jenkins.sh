#!/bin/bash

set -e

test -e Makefile && make clean distclean
qmake -r

make -j 4
make cppcheck

SctCppTimer/SctCppUnit
SctCppTimer/SctCppTimer
