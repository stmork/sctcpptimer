//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2021-2023 Steffen A. Mork
//

#pragma once

#ifndef SCTCPPTIMERSERVICE_H
#define SCTCPPTIMERSERVICE_H

#include <stdio.h>
#include <unordered_map>
#include <set>
#include <thread>
#include <condition_variable>

#include "src-lib/sc_timer.h"
#include "SctCppTimer.h"

namespace sc::timer
{
	/**
	 * This typedef declares the ordered set of active SctCppTimer
	 * instances.
	 */
	typedef std::set<SctCppTimer *, SctCppTimer>           TimerSet;

	/**
	 * This map represents the mapping from an event ID to a unique
	 * SctCppTimer instance.
	 */
	typedef std::unordered_map<TimerKey, SctCppTimer *, SctCppTimer>  TimerMap;

	/**
	 * This class implements the sc::timer::TimerServiceInterface class
	 * generated from the Yakindu SCT. It uses standard C++11 classes to
	 * implement a full fletched timer service. It uses its own thread to
	 * signal a time event. The timer themself are SctCppTimer classes which
	 * hold the information of one single SCT timer.
	 *
	 * The timer service uses the std::chrono::steady_clock since it is not
	 * adjusted during lifetime from the OS which is good enough for our
	 * purposes. We need only durations which are added to the actual time
	 * point. So even if the normal clock is adjusted this timer keeps always
	 * accurate.
	 *
	 * The timer service computes for each timer the next time point to wait
	 * until. The SctCppTimer class holds this time point for a single
	 * SCT timer. A sorted set keeps pointers to these active SctCppTimer
	 * instances. So the set acts as a priority queue. Since there may timers
	 * removed from this queue a sorted set is chosen aqainst a priority queue
	 * because a set allows the removal of mid elements from inside the set.
	 *
	 * The timer service thread waits for changes and time points. Changes may
	 * be adding or removing timer by using the setTimer() unsetTimer() methods.
	 * Since both methods force a sorted reordering a timer wait may change
	 * to another timer earlier in the queue.
	 *
	 * There is not need to map event IDs to statemachines since all event IDs
	 * are under the hood pointers inside the common process address space. So
	 * there is only a need to map event IDs to SctCppTimer class instances.
	 */
	class SctCppTimerService : public TimerServiceInterface
	{
		TimerMap                timer_map;
		TimerSet                queue;

		std::mutex              mutex;
		std::condition_variable wait;
		std::thread             thread;

		bool                    loop = true;

	public:
		/**
		 * The constructor starts the timer service thread for processing.
		 */
		SctCppTimerService();

		/**
		 * The destructor deactivates all services and stops the timer service
		 * thread gracefully.
		 */
		virtual ~SctCppTimerService();

		virtual void setTimer(
			std::shared_ptr<TimedInterface> statemachine,
			sc::eventid                     event,
			sc::time                        time_ms,
			bool                            is_periodic) override;

		virtual void unsetTimer(
			std::shared_ptr<TimedInterface> statemachine,
			sc::eventid                     event) override;

	protected:
		/**
		 * This method finds a specific SctCppTimer instance depending on
		 * the statemachine instance and its event ID.
		 *
		 * @param statechart The statemachine
		 * @param event The event ID of the given statemachine.
		 * @return The found SctCppTimer instance
		 */
		SctCppTimer * findTimer(
			std::shared_ptr<TimedInterface> & statechart,
			sc::eventid                       event);

	private:
		/**
		 * This is the timer service thread event loop.
		 */
		void eventLoop();
	};
}

#endif /* SctCppTimerService_hpp */
