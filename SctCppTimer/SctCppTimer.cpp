//
//  SctCppTimer.cpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#include "SctCppTimer.h"

using namespace sc::timer;

SctCppTimer::SctCppTimer(const sc_eventid id) : event_id(id)
{
}

void SctCppTimer::start(
	TimedInterface * timed_interface,
	sc_integer       time_ms,
	sc_boolean       is_periodic)

{
	statemachine = timed_interface;
	duration     = std::chrono::milliseconds(time_ms);
	repeating    = is_periodic;
	time_point   = std::chrono::steady_clock::now() + duration;
}
