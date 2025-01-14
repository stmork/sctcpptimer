/* #
# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: Copyright (C) 2022-2025 Steffen A. Mork
# */

#include "AbstractTimerStatechart.h"

/*! \file
Implementation of the state machine 'Statechart'
*/




AbstractTimerStatechart::AbstractTimerStatechart() noexcept
{
	for (sc::ushort state_vec_pos = 0; state_vec_pos < maxOrthogonalStates; ++state_vec_pos)
		stateConfVector[state_vec_pos] = AbstractTimerStatechart::State::NO_STATE;
	
	clearInEvents();
}

AbstractTimerStatechart::~AbstractTimerStatechart()
{
}



std::unique_ptr<AbstractTimerStatechart::EventInstance> AbstractTimerStatechart::getNextEvent() noexcept
{
	std::unique_ptr<AbstractTimerStatechart::EventInstance> nextEvent = 0;

	if(!incomingEventQueue.empty()) {
		nextEvent = std::move(incomingEventQueue.front());
		incomingEventQueue.pop_front();
	}
	
	return nextEvent;
	
}					


template<typename EWV, typename EV>
std::unique_ptr<EWV> cast_event_pointer_type (std::unique_ptr<EV>&& event){
    return std::unique_ptr<EWV>{static_cast<EWV*>(event.release())};
}
	
bool AbstractTimerStatechart::dispatchEvent(std::unique_ptr<AbstractTimerStatechart::EventInstance> event) noexcept
{
	if(event == nullptr) {
		return false;
	}
								
	switch(event->eventId)
	{
		
		
		case AbstractTimerStatechart::Event::_te0_main_region_First_:
		case AbstractTimerStatechart::Event::_te1_main_region_First_:
		case AbstractTimerStatechart::Event::_te2_main_region_First_:
		case AbstractTimerStatechart::Event::_te3_main_region_Second_:
		case AbstractTimerStatechart::Event::_te4_main_region_Second_:
		case AbstractTimerStatechart::Event::_te5_main_region_Second_:
		case AbstractTimerStatechart::Event::_te6_main_region_Second_:
		{
			timeEvents[static_cast<sc::integer>(event->eventId) - static_cast<sc::integer>(AbstractTimerStatechart::Event::_te0_main_region_First_)] = true;
			break;
		}
		default:
			//pointer got out of scope
			return false;
	}
	//pointer got out of scope
	return true;
}



bool AbstractTimerStatechart::isActive() const noexcept
{
	return stateConfVector[0] != AbstractTimerStatechart::State::NO_STATE;
}

bool AbstractTimerStatechart::isFinal() const noexcept
{
		return (stateConfVector[0] == AbstractTimerStatechart::State::main_region__final_);
}

bool AbstractTimerStatechart::check() const noexcept{
	if(timerService == nullptr) {
		return false;
	}
	if (this->ifaceOperationCallback == nullptr) {
		return false;
	}
	return true;
}


void AbstractTimerStatechart::setTimerService(std::shared_ptr<sc::timer::TimerServiceInterface> timerService_) noexcept
{
	this->timerService = timerService_;
}

std::shared_ptr<sc::timer::TimerServiceInterface> AbstractTimerStatechart::getTimerService() noexcept
{
	return timerService;
}

sc::integer AbstractTimerStatechart::getNumberOfParallelTimeEvents() noexcept {
	return parallelTimeEventsCount;
}

void AbstractTimerStatechart::raiseTimeEvent(sc::eventid evid)
{
	if (evid < timeEventsCount)
	{
		incomingEventQueue.push_back(std::unique_ptr< EventInstance>(new EventInstance(static_cast<AbstractTimerStatechart::Event>(evid + static_cast<sc::integer>(AbstractTimerStatechart::Event::_te0_main_region_First_)))));
		runCycle();
	}
}


bool AbstractTimerStatechart::isStateActive(State state) const noexcept
{
	switch (state)
	{
		case AbstractTimerStatechart::State::main_region_First :
		{
			return  (stateConfVector[scvi_main_region_First] == AbstractTimerStatechart::State::main_region_First);
			break;
		}
		case AbstractTimerStatechart::State::main_region_Second :
		{
			return  (stateConfVector[scvi_main_region_Second] == AbstractTimerStatechart::State::main_region_Second);
			break;
		}
		case AbstractTimerStatechart::State::main_region__final_ :
		{
			return  (stateConfVector[scvi_main_region__final_] == AbstractTimerStatechart::State::main_region__final_);
			break;
		}
		default:
		{
			/* State is not active*/
			return false;
			break;
		}
	}
}

sc::integer AbstractTimerStatechart::getCounter() const noexcept
{
	return counter
	;
}

void AbstractTimerStatechart::setCounter(sc::integer counter_) noexcept
{
	this->counter = counter_;
}
sc::integer AbstractTimerStatechart::getMax() noexcept
{
	return max
	;
}

sc::integer AbstractTimerStatechart::getExit12() noexcept
{
	return exit12
	;
}

sc::integer AbstractTimerStatechart::getExit21() noexcept
{
	return exit21
	;
}

sc::integer AbstractTimerStatechart::getA1() const noexcept
{
	return a1
	;
}

void AbstractTimerStatechart::setA1(sc::integer a1_) noexcept
{
	this->a1 = a1_;
}
sc::integer AbstractTimerStatechart::getB1() const noexcept
{
	return b1
	;
}

void AbstractTimerStatechart::setB1(sc::integer b1_) noexcept
{
	this->b1 = b1_;
}
sc::integer AbstractTimerStatechart::getA2() const noexcept
{
	return a2
	;
}

void AbstractTimerStatechart::setA2(sc::integer a2_) noexcept
{
	this->a2 = a2_;
}
sc::integer AbstractTimerStatechart::getB2() const noexcept
{
	return b2
	;
}

void AbstractTimerStatechart::setB2(sc::integer b2_) noexcept
{
	this->b2 = b2_;
}
sc::integer AbstractTimerStatechart::getC2() const noexcept
{
	return c2
	;
}

void AbstractTimerStatechart::setC2(sc::integer c2_) noexcept
{
	this->c2 = c2_;
}
void AbstractTimerStatechart::setOperationCallback(std::shared_ptr<OperationCallback> operationCallback) noexcept
{
	ifaceOperationCallback = operationCallback;
}

// implementations of all internal functions
/* Entry action for state 'First'. */
void AbstractTimerStatechart::enact_main_region_First()
{
	/* Entry action for state 'First'. */
	timerService->setTimer(shared_from_this(), 0, (static_cast<sc::time> (AbstractTimerStatechart::exit12)), false);
	timerService->setTimer(shared_from_this(), 1, (static_cast<sc::time> (301)), true);
	timerService->setTimer(shared_from_this(), 2, (static_cast<sc::time> (749)), false);
	ifaceOperationCallback->dump("Enter first state");
}

/* Entry action for state 'Second'. */
void AbstractTimerStatechart::enact_main_region_Second()
{
	/* Entry action for state 'Second'. */
	timerService->setTimer(shared_from_this(), 3, (static_cast<sc::time> (AbstractTimerStatechart::exit21)), false);
	timerService->setTimer(shared_from_this(), 4, (static_cast<sc::time> (250)), true);
	timerService->setTimer(shared_from_this(), 5, (static_cast<sc::time> (150)), true);
	timerService->setTimer(shared_from_this(), 6, (static_cast<sc::time> (350)), false);
	ifaceOperationCallback->dump("Enter second state");
}

/* Exit action for state 'First'. */
void AbstractTimerStatechart::exact_main_region_First()
{
	/* Exit action for state 'First'. */
	timerService->unsetTimer(shared_from_this(), 0);
	timerService->unsetTimer(shared_from_this(), 1);
	timerService->unsetTimer(shared_from_this(), 2);
	ifaceOperationCallback->dump("Exit first state");
}

/* Exit action for state 'Second'. */
void AbstractTimerStatechart::exact_main_region_Second()
{
	/* Exit action for state 'Second'. */
	timerService->unsetTimer(shared_from_this(), 3);
	timerService->unsetTimer(shared_from_this(), 4);
	timerService->unsetTimer(shared_from_this(), 5);
	timerService->unsetTimer(shared_from_this(), 6);
	ifaceOperationCallback->dump("Exit second state");
}

/* 'default' enter sequence for state First */
void AbstractTimerStatechart::enseq_main_region_First_default()
{
	/* 'default' enter sequence for state First */
	enact_main_region_First();
	stateConfVector[0] = AbstractTimerStatechart::State::main_region_First;
}

/* 'default' enter sequence for state Second */
void AbstractTimerStatechart::enseq_main_region_Second_default()
{
	/* 'default' enter sequence for state Second */
	enact_main_region_Second();
	stateConfVector[0] = AbstractTimerStatechart::State::main_region_Second;
}

/* Default enter sequence for final state */
void AbstractTimerStatechart::enseq_main_region__final__default()
{
	/* Default enter sequence for final state */
	stateConfVector[0] = AbstractTimerStatechart::State::main_region__final_;
}

/* 'default' enter sequence for region main region */
void AbstractTimerStatechart::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state First */
void AbstractTimerStatechart::exseq_main_region_First()
{
	/* Default exit sequence for state First */
	stateConfVector[0] = AbstractTimerStatechart::State::NO_STATE;
	exact_main_region_First();
}

/* Default exit sequence for state Second */
void AbstractTimerStatechart::exseq_main_region_Second()
{
	/* Default exit sequence for state Second */
	stateConfVector[0] = AbstractTimerStatechart::State::NO_STATE;
	exact_main_region_Second();
}

/* Default exit sequence for final state. */
void AbstractTimerStatechart::exseq_main_region__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[0] = AbstractTimerStatechart::State::NO_STATE;
}

/* Default exit sequence for region main region */
void AbstractTimerStatechart::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of Statechart.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case AbstractTimerStatechart::State::main_region_First :
		{
			exseq_main_region_First();
			break;
		}
		case AbstractTimerStatechart::State::main_region_Second :
		{
			exseq_main_region_Second();
			break;
		}
		case AbstractTimerStatechart::State::main_region__final_ :
		{
			exseq_main_region__final_();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* The reactions of state null. */
void AbstractTimerStatechart::react_main_region__choice_0()
{
	/* The reactions of state null. */
	if ((counter) >= (AbstractTimerStatechart::max))
	{ 
		ifaceOperationCallback->dump("Exit");
		enseq_main_region__final__default();
	}  else
	{
		counter++;
		enseq_main_region_First_default();
	}
}

/* Default react sequence for initial entry  */
void AbstractTimerStatechart::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	ifaceOperationCallback->dump("Start");
	enseq_main_region_First_default();
}

sc::integer AbstractTimerStatechart::main_region_First_react(const sc::integer transitioned_before) {
	/* The reactions of state First. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (timeEvents[0])
		{ 
			exseq_main_region_First();
			ifaceOperationCallback->dump("1 -> 2");
			timeEvents[0] = false;
			enseq_main_region_Second_default();
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		if (timeEvents[1])
		{ 
			a1++;
			ifaceOperationCallback->dump("Timer 301ms");
		} 
		if (timeEvents[2])
		{ 
			b1++;
			ifaceOperationCallback->dump("Single shot");
		} 
		transitioned_after = transitioned_before;
	} 
	return transitioned_after;
}

sc::integer AbstractTimerStatechart::main_region_Second_react(const sc::integer transitioned_before) {
	/* The reactions of state Second. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (timeEvents[3])
		{ 
			exseq_main_region_Second();
			ifaceOperationCallback->dump("2 -> choice");
			timeEvents[3] = false;
			react_main_region__choice_0();
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		if (timeEvents[4])
		{ 
			a2++;
		} 
		if (timeEvents[5])
		{ 
			b2++;
		} 
		if (timeEvents[6])
		{ 
			c2++;
		} 
		transitioned_after = transitioned_before;
	} 
	return transitioned_after;
}

void AbstractTimerStatechart::clearInEvents() noexcept {
	timeEvents[0] = false;
	timeEvents[1] = false;
	timeEvents[2] = false;
	timeEvents[3] = false;
	timeEvents[4] = false;
	timeEvents[5] = false;
	timeEvents[6] = false;
}

void AbstractTimerStatechart::microStep() {
	switch(stateConfVector[ 0 ])
	{
		case AbstractTimerStatechart::State::main_region_First :
		{
			main_region_First_react(-1);
			break;
		}
		case AbstractTimerStatechart::State::main_region_Second :
		{
			main_region_Second_react(-1);
			break;
		}
		case AbstractTimerStatechart::State::main_region__final_ :
		{
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

void AbstractTimerStatechart::runCycle() {
	/* Performs a 'run to completion' step. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	dispatchEvent(getNextEvent());
	do
	{ 
		microStep();
		clearInEvents();
	} while (dispatchEvent(getNextEvent()));
	isExecuting = false;
}

void AbstractTimerStatechart::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart Statechart */
	enseq_main_region_default();
	isExecuting = false;
}

void AbstractTimerStatechart::exit() {
	/* Deactivates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default exit sequence for statechart Statechart */
	exseq_main_region();
	stateConfVector[0] = AbstractTimerStatechart::State::NO_STATE;
	isExecuting = false;
}

/* Can be used by the client code to trigger a run to completion step without raising an event. */
void AbstractTimerStatechart::triggerWithoutEvent() {
	runCycle();
}


