//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2021 Steffen A. Mork
//

#pragma once

#ifndef CPPTIMER_H
#define CPPTIMER_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

namespace sc::timer
{
	/**
	 * This class implements a timer which is not usable for Yakindu SCT since
	 * the generated statemachine code is not thread safe. One instance of this
	 * class starts its own thread for signalling timer events. Which causes
	 * recursive race condition inside the statemachine.
	 */
	class CppTimer
	{
		std::thread             thread;
		std::mutex              mutex;
		std::condition_variable wait;

		std::chrono::time_point<std::chrono::steady_clock> time_point;
		std::chrono::milliseconds                          duration;

	public:
		CppTimer();
		virtual ~CppTimer();

		void start(
			const std::chrono::milliseconds timeout,
			const bool                      singleshot = true);
		void stop();

	protected:
		virtual void signal();

	private:
		void singleshot();
		void repeated();
	};
}

#endif /* sc__timer__CppTimer_hpp */
