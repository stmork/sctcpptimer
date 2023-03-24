QT       += core
QT       -= gui widgets
CONFIG   += c++17
TEMPLATE  = app

HEADERS += \
	src-gen/QTimerStatechart.h \
	src-lib/sc_qt_timerservice.h \
	src-lib/sc_statemachine.h \
	src-lib/sc_timer.h \
	src-lib/sc_types.h

SOURCES += \
	qt_main.cpp \
	src-gen/QTimerStatechart.cpp \
	src-lib/sc_qt_timerservice.cpp

QMAKE_CXXFLAGS += -Wextra -fstack-protector-strong
QMAKE_CXXFLAGS += -Wshadow
QMAKE_CXXFLAGS += -Wsuggest-override

QMAKE_CLEAN    += $$TARGET
