//
//  SctCppTimer.hpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#pragma once

#ifndef SCTCPPTIMER_H
#define SCTCPPTIMER_H

#include <stdio.h>
#include <chrono>
#include <mutex>

#include "src-lib/sc_timer.h"

namespace sc::timer
{
	/**
	 * This class represents one single Yakindu SCT timer. It contains
	 * information about the causing statemachine, its duration and if the
	 * timer is periodic. Each instance keeps the next time point to wait
	 * until if the timer is active.
	 */
	class SctCppTimer
	{
		std::chrono::time_point<std::chrono::steady_clock> time_point;
		std::chrono::milliseconds                          duration;
		bool                                               repeating;
		const sc_eventid                                   event_id;
		TimedInterface                  *                  statemachine = nullptr;

	public:
		explicit SctCppTimer(const sc_eventid id = 0);

		/**
		 * This method starts a timer by taking the actual time point and
		 * adding the given duration. The timer service then has to wait
		 * until this time point.
		 *
		 * @param timed_interface The statemachine the timer belongs to. This
		 * is necessary for raising the timer event appropriately.
		 * @param time_ms The duration of the timer in milli seconds.
		 * @param is_periodic A flag that shows that the timer is periodic.
		 */
		void start(
			TimedInterface * timed_interface,
			sc_integer       time_ms,
			sc_boolean       is_periodic);

		/**
		 * This method adds the timer duration to the waiting time point. So
		 * this method call occurs only in case the timer is periodic.
		 */
		inline void add()
		{
			time_point += duration;
		}

		/**
		 * This method raises the timer event in the statemachine.
		 */
		inline void call()
		{
			statemachine->raiseTimeEvent(event_id);
		}

		/**
		 * The function call operator acts as the comparator for the sorted
		 * set to sort increasingly all time points to wait for.
		 *
		 * @param left The left instance to compare.
		 * @param right The right instance to compare.
		 * @return True if the time point of the left instance is before the
		 * time point of the right instance causing to sort the SctCppTimer
		 * instances in ascending order.
		 */
		inline bool operator()(
			const SctCppTimer * left,
			const SctCppTimer * right) const
		{
			return left->time_point < right->time_point;
		}

		/**
		 * The bool cast operator returns the state whether the timer info
		 * is periodic.
		 */
		inline operator bool () const
		{
			return repeating;
		}

		/**
		 * This method returns the next time point to wait until to.
		 *
		 * @return The time point to wait until.
		 */
		inline const std::chrono::time_point<std::chrono::steady_clock> & clock() const
		{
			return time_point;
		}
	};
}

#endif /* SctCppTimer_hpp */
