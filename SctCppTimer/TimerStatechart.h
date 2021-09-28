//
//  TimerStatechart.hpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#pragma once

#ifndef TimerStatechart_hpp
#define TimerStatechart_hpp

#include <stdio.h>

#include "src-gen/AbstractTimerStatechart.h"

namespace sc::timer
{
	class SctCppTimerService;
}

class TimerStatechart :
	public AbstractTimerStatechart,
	protected AbstractTimerStatechart::OperationCallback
{
public:
	explicit TimerStatechart(sc::timer::SctCppTimerService & service);
	virtual ~TimerStatechart() = default;

private:
	void dump(sc_string text) override;
};

#endif /* TimerStatechart_hpp */
