//
//  SctCppTimerService.hpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
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
	class SctCppTimer;

	/**
	 * This class implements the sc::timer::TimerServiceInterface class
	 * generated from the Yakindu SCT. It uses standard C++11 classes to
	 * implement a full fletched timer service. It uses its own thread to
	 * signal a time event. The timer themself are SctCppTimer classes
	 * which hold the information of one single SCT timer.
	 *
	 * The timer service uses the std::chrono::steady_clock since it is not
	 * adjusted during lifetime which is good enough for our purposes. We need
	 * only durations which are added to the actual time point. So even the
	 * normal clock is adjusted this timer is always accurate.
	 *
	 * The timer service computes for each timer the next time point to wait
	 * until. The SctCppTimer class holds this time point for a single
	 * SCT timer. A sorted set keeps pointers to these active SctCppTimer
	 * instances. So the set acts as a priority queue. Since there may timers
	 * removed from this queue a sorted set is chosen aqainst a priority queue
	 * because a set allows the removal from elements other than front or back.
	 *
	 * The timer service thread waits for changes and time points. Changes may
	 * be adding or removing timer by using the setTimer() unsetTimer() methods.
	 * Since both methods force a sorted reordering a timer wait may change
	 * to another timer earlier in the queue.
	 *
	 * There is not need to map event IDs to statemachines since all event IDs
	 * are under the hood pointers inside the common address space. So there
	 * is only a need to map event IDs to SctCppTimer class instances.
	 */
	class SctCppTimerService : public TimerServiceInterface
	{
		std::unordered_map<sc_eventid, SctCppTimer *> timer_map;
		std::set<SctCppTimer *, SctCppTimer>          queue;

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
			TimedInterface * statemachine,
			sc_eventid       event,
			sc_integer       time_ms,
			sc_boolean       is_periodic) override;

		/*! Unsets the given time event.
		 */
		virtual void unsetTimer(
			TimedInterface * statemachine,
			sc_eventid       event) override;

		/*! Cancel timer service. Use this to end possible timing threads and free
		      memory resources.
		 */
		virtual void cancel() override
		{
			// Intentionally do nothing!
		}

	private:
		/**
		 * This is the timer service thread event loop.
		 */
		void eventLoop();
	};
}

#endif /* SctCppTimerService_hpp */
