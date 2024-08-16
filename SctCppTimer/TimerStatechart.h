//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2021-2024 Steffen A. Mork
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
	public AbstractTimerStatechart::OperationCallback
{
public:
	explicit TimerStatechart();
	virtual ~TimerStatechart() = default;

private:
	void dump(std::string text) override;
};

#endif /* TimerStatechart_hpp */
