//
//  TimerStatechart.cpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#include <iostream>
#include <iomanip>

#include "TimerStatechart.h"
#include "SctCppTimerService.h"

using namespace sc::timer;
using namespace std::chrono;

TimerStatechart::TimerStatechart(SctCppTimerService & service) :
	AbstractTimerStatechart()
{
	setTimerService(&service);
	setOperationCallback(this);
}

void TimerStatechart::dump(sc_string text)
{
	const time_point    now     = steady_clock::now();
	const unsigned long ms      = duration_cast<milliseconds>(now.time_since_epoch()).count();
	const unsigned long seconds = ms / 1000;
	const unsigned long millies = ms % 1000;

	std::cout.setf(std::ios::dec);
	std::cout.fill('0');
	std::cout << this << ": " << seconds << "." << std::setw(3) << millies <<
		" # " << text << std::endl << std::flush;
}
