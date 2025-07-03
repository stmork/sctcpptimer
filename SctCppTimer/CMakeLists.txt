#
#  SPDX-License-Identifier: MIT
#  SPDX-FileCopyrightText: Copyright (C) 2008-2025 Steffen A. Mork
#

cmake_minimum_required(VERSION 3.16)
project(SctCppTimer VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6    REQUIRED COMPONENTS Core)
find_package(GTest  REQUIRED)

set(CMAKE_AUTOMOC ON) 
set(CMAKE_AUTORCC ON) 
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_compile_options(-Wextra -Wpedantic)
add_compile_options(-Wshadow)
add_compile_options(-Wsuggest-override)

add_executable(SctCppTimer
	main.cpp
	CppTimer.cpp
	SctCppTimer.cpp
	SctCppTimerService.cpp
	TimerStatechart.cpp
	src-gen/AbstractTimerStatechart.cpp
	CppTimer.h
	SctCppTimer.h
	SctCppTimerService.h
	TimerStatechart.h
	src-gen/AbstractTimerStatechart.h
	src-lib/sc_eventdriven.h 
	src-lib/sc_statemachine.h
	src-lib/sc_timer.h
	src-lib/sc_types.h
)

add_executable(SctQtTimer
	src-gen/QTimerStatechart.h
	src-lib/sc_qt_timerservice.h
	src-lib/sc_eventdriven.h 
	src-lib/sc_statemachine.h
	src-lib/sc_timer.h
	src-lib/sc_types.h
	qt_main.cpp
	src-gen/QTimerStatechart.cpp
	src-lib/sc_qt_timerservice.cpp
)

add_executable(SctUnitTimer
	src-gen/AbstractTimerStatechart.h
	src-lib/sc_runner_timed.h
	src-lib/sc_eventdriven.h 
	src-lib/sc_timer.h
	src-lib/sc_timer_service.h
	src-lib/sc_types.h
	Statechart.h
	src-gen/AbstractTimerStatechart.cpp
	src-lib/sc_timer_service.cpp
	src-test/StatechartTest.cc
	src-lib/sc_runner_timed.cpp
)

target_include_directories(SctUnitTimer PRIVATE src-lib)

target_link_libraries(SctCppTimer)
target_link_libraries(SctQtTimer PRIVATE Qt6::Core)
target_link_libraries(SctUnitTimer PRIVATE GTest::gtest_main)

add_test(
	NAME sctunit
	COMMAND ${PROJECT_BINARY_DIR}/SctUnitTimer --gtest_output=xml:gtest-results.xml
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set_property(
    TARGET SctUnitTimer
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_SOURCE_DIR}/gtest-results.xml
)
