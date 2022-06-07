#!/bin/bash

set -e

cd SctCppTimer
test -e Makefile && make clean distclean
qmake -r

make -j 4
make cppcheck

SctCppTimer
