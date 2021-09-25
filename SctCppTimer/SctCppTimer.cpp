//
//  SctCppTimer.cpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#include "SctCppTimer.hpp"

using namespace sc::timer;

void SctCppTimer::signal()
{
    statemachine->raiseTimeEvent(event_id);
}
