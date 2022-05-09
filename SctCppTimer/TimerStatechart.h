//
//  TimerStatechart.hpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#pragma once

#ifndef TIMERSTATECHART_H
#define TIMERSTATECHART_H

#include <stdio.h>

#include "src-gen/AbstractTimerStatechart.h"

namespace sc::timer
{
	class SctCppTimerService;
}

/**
 * This class simply implements an example statemachine for testing the
 * C++ timer service.
 */
class TimerStatechart :
	public AbstractTimerStatechart,
	protected AbstractTimerStatechart::OperationCallback
{
public:
	explicit TimerStatechart(sc::timer::SctCppTimerService & service);
	virtual ~TimerStatechart() = default;

private:
	void dump(std::string text) override;
};

#endif /* TimerStatechart_hpp */
