//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2021 Steffen A. Mork
//

#include "SctCppTimer.h"

using namespace sc::timer;
using namespace std::chrono;

SctCppTimer::SctCppTimer(const eventid id) : event_id(id)
{
}

void SctCppTimer::start(
	TimedInterface * timed_interface,
	integer          time_ms,
	bool             is_periodic)

{
	statemachine = timed_interface;
	duration     = milliseconds(time_ms);
	repeating    = is_periodic;
	time_point   = steady_clock::now() + duration;
}
