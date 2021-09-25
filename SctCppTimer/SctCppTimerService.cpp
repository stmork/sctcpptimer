//
//  SctCppTimerService.cpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#include "SctCppTimerService.h"
#include "SctCppTimer.h"

using namespace sc::timer;

SctCppTimerService::~SctCppTimerService()
{
    for(auto element : timer_map)
    {
        delete element.second;
    }
}

void SctCppTimerService::setTimer(
                      TimedInterface* statemachine,
                      sc_eventid event,
                      sc_integer time_ms,
                      sc_boolean isPeriodic)
{
    SctCppTimer * timer;
    auto it = timer_map.find(event);
    
    if (it == timer_map.end())
    {
        timer = new SctCppTimer(statemachine, event);
    }
    else
    {
        timer = it->second;
    }
    timer->start(std::chrono::milliseconds(time_ms), !isPeriodic);
}

void SctCppTimerService::unsetTimer(
                        TimedInterface* statemachine, sc_eventid event)
{
    timer_map[event]->stop();
}
