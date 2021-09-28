//
//  SctCppTimerService.cpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#include "SctCppTimerService.h"
#include "SctCppTimer.h"

using namespace sc::timer;

SctCppTimerService::SctCppTimerService() :
	thread(&SctCppTimerService::eventLoop, this)
{
}

SctCppTimerService::~SctCppTimerService()
{
	loop = false;
	wait.notify_all();
	thread.join();
}

void SctCppTimerService::setTimer(
	TimedInterface * statemachine,
	sc_eventid event,
	sc_integer time_ms,
	sc_boolean isPeriodic)
{
	SctCppTimerInfo * timer;
	auto it = timer_map.find(event);

	if (it == timer_map.end())
	{
		timer = new SctCppTimerInfo(statemachine, event);
		timer_map[event] = timer;
	}
	else
	{
		timer = it->second;
	}
	timer->start(time_ms, isPeriodic);
	queue.insert(timer);
	wait.notify_all();
}

void SctCppTimerService::unsetTimer(
	TimedInterface * statemachine, sc_eventid event)
{
	SctCppTimerInfo * timer = timer_map[event];

	queue.erase(timer);
	wait.notify_all();
}

void SctCppTimerService::eventLoop()
{
	do
	{
		if (queue.empty())
		{
			std::unique_lock<std::mutex> lock(mutex);

			wait.wait(lock);
		}
		else
		{
			std::unique_lock<std::mutex> lock(mutex);
			SctCppTimerInfo * info = *queue.begin();

			if (wait.wait_until(lock, info->clock()) == std::cv_status::timeout)
			{
				info->call();
				queue.erase(info);
				if (*info)
				{
					info->add();
					queue.insert(info);
				}
			}
		}
	}
	while (loop);
}
