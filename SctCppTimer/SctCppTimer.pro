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

#####################################################################
#
# Extra targets.
#
#####################################################################

QMAKE_EXTRA_TARGETS += astyle

astyle.commands = astyle *.cpp *.h
