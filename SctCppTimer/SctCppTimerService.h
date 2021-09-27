//
//  SctCppTimerService.hpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#pragma once

#ifndef SctCppTimerService_hpp
#define SctCppTimerService_hpp

#include <stdio.h>
#include <unordered_map>
#include <set>
#include <thread>

#include "src-lib/sc_timer.h"
#include "SctCppTimer.h"

namespace sc::timer
{
	class SctCppTimerInfo;

    class SctCppTimerService : public TimerServiceInterface
    {
        std::unordered_map<sc_eventid, SctCppTimerInfo *> timer_map;
		std::set<SctCppTimerInfo *, SctCppTimerInfo>      queue;
		std::mutex              mutex;
		std::condition_variable wait;
		std::thread             thread;

		bool                    loop = true;

	public:
		SctCppTimerService();
        virtual ~SctCppTimerService();
        
        virtual void setTimer(
                              TimedInterface* statemachine,
                              sc_eventid event,
                              sc_integer time_ms,
                              sc_boolean isPeriodic) override;
        
        /*! Unsets the given time event.
         */
        virtual void unsetTimer(
                                TimedInterface* statemachine, sc_eventid event) override;
    
        /*! Cancel timer service. Use this to end possible timing threads and free
              memory resources.
         */
        virtual void cancel() override
        {
            // Intentionally do nothing!
        }

		void eventLoop();
    };
}
#endif /* SctCppTimerService_hpp */
