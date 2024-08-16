/* #
# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: Copyright (C) 2022-2024 Steffen A. Mork
# */

#ifndef SC_CYCLEBASED_H_
#define SC_CYCLEBASED_H_

#include "sc_statemachine.h"

namespace sc
{

	/*! \file
	Interface for cycle-based state machines.
	*/
	class CycleBasedInterface : public sc::StatemachineInterface
	{
	public:

		virtual ~CycleBasedInterface() = 0;

		/*! Start a run-to-completion cycle.
		*/
		virtual void runCycle() = 0;
	};

	inline CycleBasedInterface::~CycleBasedInterface() {}

} /* namespace sc */

#endif /* SC_CYCLEBASED_H_ */
