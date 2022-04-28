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

	queue.clear();
	for (auto chart_it : chart_map)
	{
		for (auto timer_it : chart_it.second)
		{
			delete timer_it.second;
		}
		chart_it.second.clear();
	}
	chart_map.clear();
}

void SctCppTimerService::setTimer(
	TimedInterface * statemachine,
	sc_eventid       event,
	sc_integer       time_ms,
	sc_boolean       is_periodic)
{
	SctCppTimer * timer = findTimer(statemachine, event);

	timer->start(statemachine, time_ms, is_periodic);
	queue.insert(timer);
	wait.notify_all();
}

void SctCppTimerService::unsetTimer(
	TimedInterface * statemachine,
	sc_eventid       event)
{
	SctCppTimer * timer = findTimer(statemachine, event);

	(void)statemachine;
	queue.erase(timer);
	wait.notify_all();
}

SctCppTimer * SctCppTimerService::findTimer(
		TimedInterface * statemachine,
		sc_eventid       event)
{
	ChartMap::iterator chart_it = chart_map.find(statemachine);
	TimerMap *         timer_map;

	if (chart_it == chart_map.end())
	{
		chart_map.emplace(statemachine, TimerMap());

		timer_map = &chart_map[statemachine];
	}
	else
	{
		timer_map = &chart_it->second;
	}

	TimerMap::iterator timer_it = timer_map->find(event);
	SctCppTimer *      timer;

	if (timer_it == timer_map->end())
	{
		timer = new SctCppTimer(event);

		timer_map->emplace(event, timer);
	}
	else
	{
		timer = timer_it->second;
	}
	return timer;
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

			SctCppTimer           *          info = *queue.begin();
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
