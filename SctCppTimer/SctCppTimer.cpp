//
//  SctCppTimer.cpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#include "SctCppTimer.h"

using namespace sc::timer;

void SctCppTimer::signal()
{
	static std::mutex raise_mutex;

//	std::lock_guard<std::mutex> lock(raise_mutex);

    statemachine->raiseTimeEvent(event_id);
}
