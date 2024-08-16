//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2022-2024 Steffen A. Mork
//

#include <stdlib.h>
#include <iostream>
#include <iomanip>

#include <QCoreApplication>
#include <QTimer>

#include "src-gen/QTimerStatechart.h"
#include "src-lib/sc_qt_timerservice.h"

using sc::qt::SCTimerService;
using namespace sc::timer;
using namespace std::chrono;

class Dump : public QTimerStatechart::OperationCallback
{
public:
	inline void dump(std::string text) override
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
};

int main(int argc, char * argv[])
{
	QCoreApplication app(argc, argv);
	std::shared_ptr<SCTimerService>    timer_service = std::make_shared<SCTimerService>(nullptr);
	std::shared_ptr<Dump>              dumper        = std::make_shared<Dump>();
	std::shared_ptr<QTimerStatechart>  statechart    = std::make_shared<QTimerStatechart>(nullptr);

	statechart->setTimerService(timer_service);
	statechart->setOperationCallback(dumper);
	statechart->enter();

	QTimer::singleShot(12000, []
	{
		QCoreApplication::quit();
	});

	return app.exec();
}
