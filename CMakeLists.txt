#
#  SPDX-License-Identifier: MIT
#  SPDX-FileCopyrightText: Copyright (C) 2008-2026 Steffen A. Mork
#

cmake_minimum_required(VERSION 3.16)
project(SCT-Timer VERSION 1.0.0 LANGUAGES CXX)

enable_testing()

add_subdirectory(SctCppTimer)

add_custom_target(astyle
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND astyle */*.cpp */*.h
)

add_custom_target(cppcheck
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND cppcheck --language=c++ --std=c++14
        --xml-version=2 --force -q -j `nproc`
        */*.cpp */*.h 2>cppcheck.xml
)

set_property(
    TARGET cppcheck
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_SOURCE_DIR}/cppcheck.xml
)
