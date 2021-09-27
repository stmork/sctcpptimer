//
//  SctCppTimer.hpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#pragma once

#ifndef SctCppTimer_hpp
#define SctCppTimer_hpp

#include <stdio.h>
#include "src-lib/sc_timer.h"
#include "CppTimer.h"

namespace sc::timer
{
	class SctCppTimerInfo
	{
		std::chrono::time_point<std::chrono::steady_clock> time_point;
		std::chrono::milliseconds                          duration;
		bool                                               repeating;
		const sc_eventid                                   event_id;
		TimedInterface *                                   statemachine = nullptr;

	public:
		inline SctCppTimerInfo() : event_id(0)
		{
		}

		explicit inline SctCppTimerInfo(
			TimedInterface * timed_interface,
			const sc_eventid id) :
		statemachine(timed_interface),
		event_id(id)
		{
		}

		inline void start(
						  sc_integer time_ms,
						  sc_boolean is_periodic)
		{
			duration   = std::chrono::milliseconds(time_ms);
			repeating  = is_periodic;
			time_point = std::chrono::steady_clock::now() + duration;
		}

		inline void add()
		{
			time_point += duration;
		}

		inline void call()
		{
			statemachine->raiseTimeEvent(event_id);
		}

		inline bool operator()(
						const SctCppTimerInfo * left,
						const SctCppTimerInfo * right) const
		{
			return left->time_point < right->time_point;
		}

		inline operator bool () const
		{
			return repeating;
		}

		inline operator const std::chrono::time_point<std::chrono::steady_clock> & () const
		{
			return time_point;
		}
	};

    class SctCppTimer : public CppTimer
    {
        const sc_eventid event_id;
        TimedInterface * statemachine = nullptr;

    public:
        explicit inline SctCppTimer(
            TimedInterface * timed_interface,
            const sc_eventid id) :
        statemachine(timed_interface),
        event_id(id)
        {
        }
        
    protected:
        virtual void signal() override;
    };
}

#endif /* SctCppTimer_hpp */
