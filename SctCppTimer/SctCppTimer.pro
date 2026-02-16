#
#  SPDX-License-Identifier: MIT
#  SPDX-FileCopyrightText: Copyright (C) 2021-2026 Steffen A. Mork
#

QT       -= core
QT       -= gui widgets
CONFIG   += c++20
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
	src-lib/sc_eventdriven.h  \
	src-lib/sc_statemachine.h \
	src-lib/sc_timer.h \
	src-lib/sc_types.h

QMAKE_CXXFLAGS += -Wextra -fstack-protector-strong
QMAKE_CXXFLAGS += -Wshadow
QMAKE_CXXFLAGS += -Wsuggest-override

QMAKE_CLEAN    += $$TARGET
