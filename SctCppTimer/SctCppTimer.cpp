//
//  SctCppTimer.cpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#include "SctCppTimer.h"

using namespace sc::timer;

SctCppTimer::SctCppTimer(const eventid id) : event_id(id)
{
}

void SctCppTimer::start(
	TimedInterface * timed_interface,
	integer          time_ms,
	bool             is_periodic)

{
	statemachine = timed_interface;
	duration     = std::chrono::milliseconds(time_ms);
	repeating    = is_periodic;
	time_point   = std::chrono::steady_clock::now() + duration;
}
