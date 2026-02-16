#
#  SPDX-License-Identifier: MIT
#  SPDX-FileCopyrightText: Copyright (C) 2021-2026 Steffen A. Mork
#

TEMPLATE = subdirs
SUBDIRS  = \
	SctCppTimer \
	SctQtTimer \
	SctUnitTimer

SctCppTimer.file  = SctCppTimer/SctCppTimer.pro
SctQtTimer.file   = SctCppTimer/SctQtTimer.pro
SctUnitTimer.file = SctCppTimer/SctUnitTimer.pro

SctQtTimer.depends   = SctCppTimer
SctUnitTimer.depends = SctQtTimer

QMAKE_CLEAN += cppcheck.xml
QMAKE_CLEAN += gtest-results.xml

#####################################################################
#
# Extra targets.
#
#####################################################################

QMAKE_EXTRA_TARGETS += astyle cppcheck

astyle.commands = astyle */*.cpp */*.h
cppcheck.commands = cppcheck \
	--suppress=preprocessorErrorDirective\
	--language=c++ --std=c++20 \
	--xml-version=2 --force -q -j 3 \
	*/*.cpp */*.h 2>cppcheck.xml
 
