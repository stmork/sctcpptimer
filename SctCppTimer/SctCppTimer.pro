QT       += core
QT       -= gui widgets
CONFIG   += c++17
TEMPLATE  = app

SOURCES += main.cpp \
	CppTimer.cpp \
	SctCppTimer.cpp \
	SctCppTimerService.cpp \
	TimerStatechart.cpp \
	src-gen/AbstractTimerStatechart.cpp

HEADERS += \
	CppTimer.h \
	SctCppTimer.h \
	SctCppTimerService.h \
	TimerStatechart.h \
	src-gen/AbstractTimerStatechart.h \
	src-lib/sc_statemachine.h \
	src-lib/sc_timer.h \
	src-lib/sc_types.h

QMAKE_CLEAN += cppcheck.xml

#####################################################################
#
# Extra targets.
#
#####################################################################

QMAKE_EXTRA_TARGETS += astyle cppcheck

astyle.commands = astyle *.cpp *.h
cppcheck.commands = cppcheck \
	--language=c++ --std=c++14 \
	--xml-version=2 --force -q -j 3 \
	*.cpp *.h 2>cppcheck.xml
