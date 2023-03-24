#!/bin/bash

set -e

test -e Makefile && make clean distclean
qmake -r

make -j 4
make cppcheck

SctCppTimer/SctUnitTimer --gtest_output="xml:gtest-results.xml"
SctCppTimer/SctCppTimer
SctCppTimer/SctQtTimer
