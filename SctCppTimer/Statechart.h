//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2021-2023 Steffen A. Mork
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
