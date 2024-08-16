TEMPLATE = app

HEADERS += \
	src-gen/AbstractTimerStatechart.h \
	src-lib/sc_runner_timed.h \
	Statechart.h \
	src-lib/sc_timer_service.h

SOURCES += \
	src-gen/AbstractTimerStatechart.cpp \
	src-lib/sc_timer_service.cpp \
	src-test/StatechartTest.cc \
	src-lib/sc_runner_timed.cpp

QMAKE_CXXFLAGS += -Wextra -fstack-protector-strong
QMAKE_CXXFLAGS += -Wshadow
QMAKE_CXXFLAGS += -Wsuggest-override

INCLUDEPATH    += src-gen/ src-lib/
LIBS           += -lgtest -lgtest_main
QMAKE_CLEAN    += $$TARGET gtest-results.xml
