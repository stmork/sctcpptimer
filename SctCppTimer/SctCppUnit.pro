TEMPLATE = app

HEADERS += \
	src-gen/AbstractTimerStatechart.h \
	src-test/sc_runner_timed.h

SOURCES += \
	src-gen/AbstractTimerStatechart.cpp \
	src-test/StatechartTest.cc \
	src-test/sc_runner_timed.cpp

QMAKE_CXXFLAGS    += -Wextra -fstack-protector-strong
#QMAKE_CXXFLAGS    += -Wshadow
#QMAKE_CXXFLAGS    += -Wsuggest-override

INCLUDEPATH += src-gen/ src-lib/
LIBS        += -lgtest -lgtest_main
QMAKE_CLEAN += $$TARGET gtest-results.xml
