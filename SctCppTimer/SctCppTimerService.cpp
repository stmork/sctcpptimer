//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2021-2023 Steffen A. Mork
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
	for (auto it : timer_map)
	{
		delete it.second;
	}
	timer_map.clear();
}

void SctCppTimerService::setTimer(
	std::shared_ptr<TimedInterface> statemachine,
	sc::eventid                     event,
	sc::time                        time_ms,
	bool                            is_periodic)
{
	SctCppTimer * timer = findTimer(statemachine, event);

	timer->start(statemachine.get(), time_ms, is_periodic);
	queue.insert(timer);
	wait.notify_all();
}

void SctCppTimerService::unsetTimer(
	std::shared_ptr<TimedInterface> statemachine,
	sc::eventid                     event)
{
	SctCppTimer * timer = findTimer(statemachine, event);

	queue.erase(timer);
	wait.notify_all();
}

void SctCppTimerService::unsetTimerRaw(
	TimedInterface * statemachine,
	sc::eventid      event)
{
	TimerKey           key(statemachine, event);
	TimerMap::iterator it = timer_map.find(key);

	if (it != timer_map.end())
	{
		SctCppTimer * timer = it->second;

		queue.erase(timer);
		timer_map.erase(it);
		delete timer;

		wait.notify_all();
	}
}

SctCppTimer * SctCppTimerService::findTimer(
	std::shared_ptr<TimedInterface> & statemachine,
	sc::eventid                       event)
{
	SctCppTimer    *   timer;
	TimerKey           key(statemachine.get(), event);
	TimerMap::iterator it = timer_map.find(key);

	if (it == timer_map.end())
	{
		timer = new SctCppTimer(event);

		timer_map.emplace(key, timer);
	}
	else
	{
		timer = it->second;
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
