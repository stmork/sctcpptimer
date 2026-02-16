/*
 * Timer Service Implementation for SCTUnit
 */

#include "sc_runner_timed.h"

/**
 * Implementation of a timer service that uses _virtual_ time to raise time events.
 * It is solely meant for use with sctunit.
 */

TimedSctUnitRunner::TimedSctUnitRunner(
	size_t maximal_parallel_time_events_
) :
	timerServiceImplementation(std::unique_ptr<sc::timer::TimerTask[]>(new sc::timer::TimerTask[maximal_parallel_time_events_]), maximal_parallel_time_events_)
{
}

void TimedSctUnitRunner::proceed_time(sc::time time_ms)
{
	timerServiceImplementation.proceed(time_ms);
}

void TimedSctUnitRunner::proceed_cycles(sc::integer cycles)
{
	(void) cycles;
}
void TimedSctUnitRunner::setTimer(std::shared_ptr<sc::timer::TimedInterface> statemachine_, sc::eventid event, sc::time time_ms, bool isPeriodic)
{
	timerServiceImplementation.setTimer(statemachine_, event, time_ms, isPeriodic);
}

void TimedSctUnitRunner::unsetTimer(std::shared_ptr<sc::timer::TimedInterface> statemachine_, sc::eventid event) noexcept
{
	timerServiceImplementation.unsetTimer(statemachine_, event);
}
void TimedSctUnitRunner::unsetTimerRaw(sc::timer::TimedInterface * statemachine_, sc::eventid event) noexcept
{
	timerServiceImplementation.unsetTimerRaw(statemachine_, event);
}

void TimedSctUnitRunner::cancel() noexcept
{
	timerServiceImplementation.cancel();
}
