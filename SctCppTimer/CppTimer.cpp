//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2021-2023 Steffen A. Mork
//

#include "CppTimer.h"

#include <iostream>
#include <iomanip>

using namespace sc::timer;
using namespace std::chrono;

CppTimer::CppTimer()
{
}

CppTimer::~CppTimer()
{
	stop();
}

void CppTimer::start(
	const std::chrono::milliseconds timeout,
	const bool                      singleshot)
{
	time_point = steady_clock::now();
	duration   = timeout;

	if (singleshot)
	{
		thread = std::thread(&CppTimer::singleshot, this);
	}
	else
	{
		thread = std::thread(&CppTimer::repeated, this);
	}
}

void CppTimer::stop()
{
	if (thread.joinable() &&
		(std::this_thread::get_id() != thread.get_id()))
	{
		wait.notify_all();
		thread.join();
	}
}

void CppTimer::signal()
{
	const auto ms = duration_cast<milliseconds>(time_point.time_since_epoch()).count();

	std::cout.fill('0');
	std::cout << this << ": " << ms / 1000 << "." << std::setw(3) << ms % 1000 << std::endl << std::flush;
}

void CppTimer::singleshot()
{
	std::unique_lock<std::mutex> lock(mutex);

	time_point += duration;
	if (wait.wait_until(lock, time_point) == std::cv_status::timeout)
	{
		signal();
	}
}

void CppTimer::repeated()
{
	bool timed_out;

	do
	{
		std::unique_lock<std::mutex> lock(mutex);

		time_point += duration;
		timed_out   = wait.wait_until(lock, time_point) == std::cv_status::timeout;
		if (timed_out)
		{
			signal();
		}
	}
	while (timed_out);
}
