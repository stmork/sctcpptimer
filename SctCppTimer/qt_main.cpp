//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2022 Steffen A. Mork
//

#include <stdlib.h>
#include <iostream>

#include <QCoreApplication>
#include <QTimer>

#include "src-gen/QTimerStatechart.h"
#include "src-lib/sc_qt_timerservice.h"

using sc::qt::SCTimerService;

class Dump : public QTimerStatechart::OperationCallback
{
public:
	inline void dump(std::string message) override
	{
		std::cout << message << std::endl;
	}
};

int main(int argc, char * argv[])
{
	QCoreApplication app(argc, argv);
	SCTimerService   timer_service(nullptr);
	QTimerStatechart statechart(nullptr);
	Dump             dumper;

	statechart.setTimerService(&timer_service);
	statechart.setOperationCallback(&dumper);
	statechart.enter();

	QTimer::singleShot(20000, []
	{
		std::terminate();
		QCoreApplication::quit();
	});

	return app.exec();
}
