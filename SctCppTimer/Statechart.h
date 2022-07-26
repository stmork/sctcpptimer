//
//  TimerStatechart.hpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 25.09.21.
//

#pragma once

#include "src-gen/AbstractTimerStatechart.h"

#ifndef STATECHART_H
#define STATECHART_H

class Statechart : public AbstractTimerStatechart
{
public:
	virtual ~Statechart() = default;
};

#endif
