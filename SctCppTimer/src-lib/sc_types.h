/* #
# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: Copyright (C) 2022-2026 Steffen A. Mork
# */

#pragma once

#ifndef SC_TYPES_H_
#define SC_TYPES_H_

#include <cstdint>
#include <string>

#ifndef SC_UNUSED
#define SC_UNUSED(x) (void)(x)
#endif

namespace sc
{
	typedef uint16_t   ushort;
	typedef int        integer;
	typedef int        errorCode;
	typedef double     real;
	typedef int        time;
	typedef unsigned   eventid;
}

#endif /* SC_TYPES_H_ */
