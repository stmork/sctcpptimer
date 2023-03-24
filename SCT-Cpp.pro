TEMPLATE = subdirs
SUBDIRS  = \
	SctCppTimer \
	SctQtTimer \
	SctUnitTimer

SctCppTimer.file  = SctCppTimer/SctCppTimer.pro
SctQtTimer.file   = SctCppTimer/SctQtTimer.pro
SctUnitTimer.file = SctCppTimer/SctUnitTimer.pro

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
	--language=c++ --std=c++14 \
	--xml-version=2 --force -q -j 3 \
	*/*.cpp */*.h 2>cppcheck.xml
 
