TEMPLATE = subdirs
SUBDIRS  = \
   SctCppTimer \
   SctCppUnit

SctCppTimer.file = SctCppTimer/SctCppTimer.pro
SctCppUnit.file  = SctCppTimer/SctCppUnit.pro

QMAKE_CLEAN += cppcheck.xml

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
 
