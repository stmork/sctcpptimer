//
//  SctCppTimerService.cpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#include "SctCppTimerService.h"
#include "SctCppTimer.h"

using namespace sc::timer;
using namespace std::chrono;

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
	sc_eventid       event,
	sc_integer       time_ms,
	sc_boolean       is_periodic)
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
	timer->start(time_ms, is_periodic);
	queue.insert(timer);
	wait.notify_all();
}

void SctCppTimerService::unsetTimer(
	TimedInterface * statemachine,
	sc_eventid       event)
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

			// If no timer is in the queue simply wait
			// for something.
			wait.wait(lock);
		}
		else
		{
			std::unique_lock<std::mutex> lock(mutex);

			SctCppTimerInfo *                info = *queue.begin();
			const time_point<steady_clock> & tp   = info->clock();

			// If timer info is in the past or wait for
			// nearest time point
			if ((tp <= steady_clock::now()) ||
				(wait.wait_until(lock, tp) == std::cv_status::timeout))
			{
				// Raise time event
				info->call();

				// Remove anyway
				queue.erase(info);
				if (*info)
				{
					// If periodic add duration and reschedule timer
					info->add();
					queue.insert(info);
				}
			}
		}
	}
	while (loop);
}
