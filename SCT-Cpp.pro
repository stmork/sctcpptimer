TEMPLATE = subdirs
SUBDIRS  = \
	SctCppTimer \
	SctCppTimerQt \
	SctCppUnit

SctCppTimer.file   = SctCppTimer/SctCppTimer.pro
SctCppTimerQt.file = SctCppTimer/SctCppTimerQt.pro
SctCppUnit.file    = SctCppTimer/SctCppUnit.pro

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
 
