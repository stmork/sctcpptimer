//
//  sc::timer::CppTimer.hpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 24.09.21.
//

#pragma once

#ifndef sc__timer__CppTimer_hpp
#define sc__timer__CppTimer_hpp

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

namespace sc::timer
{
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
