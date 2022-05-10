/*
 * Timer Service for SCTUnit
 */

#ifndef SC_TIMER_SERVICE_H_
#define SC_TIMER_SERVICE_H_

#include <list>

#include "sc_types.h"
#include "sc_statemachine.h"
#include "sc_timer.h"

class TimedSctUnitRunner : public sc::timer::TimerServiceInterface {
	public:
		TimedSctUnitRunner(sc::StatemachineInterface * statemachine, bool event_driven, sc::integer cycle_period);
		virtual ~TimedSctUnitRunner(){};
		void proceed_time(sc::integer time_ms);
		void proceed_cycles(sc::integer cycles);
		virtual void setTimer(sc::timer::TimedInterface* statemachine, sc::eventid event, sc::integer time_ms, bool isPeriodic);
		virtual void unsetTimer(sc::timer::TimedInterface* statemachine, sc::eventid event);
		virtual void cancel();
	private:
		class SctTimer;
		sc::StatemachineInterface * statemachine;
		
		bool event_driven;
		sc::integer cycle_period;
		sc::integer current_time_ms;

		std::list<SctTimer> timer_queue;
		void insert_timer(SctTimer timer);
};

class TimedSctUnitRunner::SctTimer {
	friend class TimedSctUnitRunner;
	public:
		SctTimer(sc::timer::TimedInterface * tsi, sc::integer time_ms, bool periodic, sc::eventid evid, sc::integer priority, bool is_runcycle);
		~SctTimer(){}
		
		sc::integer compare(SctTimer * other);
		
	private:
		sc::timer::TimedInterface * tsi;
		sc::integer rel_time_ms;
		sc::integer abs_time_ms;
		bool periodic;
		sc::eventid pt_evid;
		sc::integer priority;
		bool is_runcycle;
};

#endif /* SC_TIMER_SERVICE_H_ */

