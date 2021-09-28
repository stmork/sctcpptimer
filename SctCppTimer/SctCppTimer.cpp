//
//  SctCppTimer.cpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#include "SctCppTimer.h"

using namespace sc::timer;

SctCppTimerInfo::SctCppTimerInfo(
	TimedInterface * timed_interface,
	const sc_eventid id) :
	statemachine(timed_interface),
	event_id(id)
{
}

void SctCppTimerInfo::start(
	sc_integer time_ms,
	sc_boolean is_periodic)

{
	duration   = std::chrono::milliseconds(time_ms);
	repeating  = is_periodic;
	time_point = std::chrono::steady_clock::now() + duration;
}
