//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2021 Steffen A. Mork
//

#include <iostream>
#include <iomanip>
#include <unistd.h>

#include "CppTimer.h"
#include "SctCppTimerService.h"
#include "TimerStatechart.h"

using namespace sc::timer;
using namespace std::chrono;

static void dump(
	const std::string & comment,
	const int           expected,
	const int           actual)
{
	std::cout.fill(' ');
	std::cout << comment << ": ";
	std::cout << " expected: " << std::setw(3) << expected;
	std::cout << " actual: "   << std::setw(3) << actual;
	std::cout << std::endl << std::flush;
}

int main()
{
	SctCppTimerService timer_service;
	TimerStatechart    statechart(timer_service);
	CppTimer a;
	CppTimer b;
	CppTimer c;

	statechart.enter();
	std::cout << "--------------------------" << std::endl << std::flush;
	a.start(2s);
	b.start(700ms, false);
	sleep(3);

	std::cout << "--------------------------" << std::endl << std::flush;
	a.stop();
	a.start(2500ms, false);
	sleep (7);

	std::cout << "--------------------------" << std::endl << std::flush;
	a.stop();
	b.stop();

	const int max    = statechart.getMax();
	const int exit12 = statechart.getExit12();
	const int exit21 = statechart.getExit21();

	sleep((exit12 + exit21) / 1000 * max + 3);
	std::cout << "final: " << statechart.isFinal() << std::endl << std::flush;
	statechart.exit();

	dump("counter", max, statechart.getCounter());
	dump("a1", exit12 / 301 * max, statechart.getA1());
	dump("b1", max, statechart.getB1());

	dump("a2", exit21 / 250 * max, statechart.getA2());
	dump("b2", exit21 / 150 * max, statechart.getB2());
	dump("c2", max, statechart.getC2());

	return 0;
}
