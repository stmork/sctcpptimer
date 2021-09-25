//
//  TimerStatechart.cpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#include <iostream>

#include "TimerStatechart.h"
#include "SctCppTimerService.h"

using namespace sc::timer;

TimerStatechart::TimerStatechart(SctCppTimerService & service) :
    AbstractTimerStatechart()
{
    setTimerService(&service);
    setOperationCallback(this);
}

void TimerStatechart::dump(sc_string text)
{
	std::cout << text << std::endl;
}
