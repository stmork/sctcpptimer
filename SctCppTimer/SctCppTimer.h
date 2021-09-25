//
//  SctCppTimer.hpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#ifndef SctCppTimer_hpp
#define SctCppTimer_hpp

#include <stdio.h>
#include "src-lib/sc_timer.h"
#include "CppTimer.h"

namespace sc::timer
{
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
