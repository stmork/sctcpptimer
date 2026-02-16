#
#  SPDX-License-Identifier: MIT
#  SPDX-FileCopyrightText: Copyright (C) 2021-2026 Steffen A. Mork
#

TEMPLATE = app

HEADERS += \
	src-gen/AbstractTimerStatechart.h \
	src-lib/sc_runner_timed.h \
	src-lib/sc_eventdriven.h  \
	src-lib/sc_timer.h \
	src-lib/sc_timer_service.h \
	src-lib/sc_types.h \
	Statechart.h

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
