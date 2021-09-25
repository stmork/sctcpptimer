//
//  SctCppTimerService.hpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#ifndef SctCppTimerService_hpp
#define SctCppTimerService_hpp

#include <stdio.h>
#include <unordered_map>

#include "src-lib/sc_timer.h"

namespace sc::timer
{
    class SctCppTimer;

    class SctCppTimerService : public TimerServiceInterface
    {
        std::unordered_map<sc_eventid, SctCppTimer *> timer_map;
        
    public:
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
    };
}
#endif /* SctCppTimerService_hpp */
