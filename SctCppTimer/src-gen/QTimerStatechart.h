/* #
# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: Copyright (C) 2022-2025 Steffen A. Mork
# */

#ifndef QTIMERSTATECHART_H_
#define QTIMERSTATECHART_H_

/*!
Forward declaration for the QTimerStatechart state machine.
*/
class QTimerStatechart;


#include <deque>
#include "../src-lib/sc_types.h"
#include "../src-lib/sc_statemachine.h"
#include "../src-lib/sc_eventdriven.h"
#include "../src-lib/sc_timer.h"
#include <memory>
#include <string.h>
#include <QObject>

/*! \file
Header of the state machine 'Statechart'.
*/


class QTimerStatechart : public QObject, public sc::timer::TimedInterface, public std::enable_shared_from_this<sc::timer::TimedInterface>, public sc::EventDrivenInterface
{
	public:
		explicit QTimerStatechart(QObject *parent) noexcept;
		
		virtual ~QTimerStatechart();
		
		
		
		/*! Enumeration of all states. */
		enum class State
		{
			NO_STATE,
			main_region_First,
			main_region_Second,
			main_region__final_
		};
		
		/*! The number of states. */
		static constexpr const sc::integer numStates {3};
		static constexpr const sc::integer scvi_main_region_First {0};
		static constexpr const sc::integer scvi_main_region_Second {0};
		static constexpr const sc::integer scvi_main_region__final_ {0};
		
		/*! Enumeration of all events which are consumed. */
		enum class Event
		{
			NO_EVENT,
			_te0_main_region_First_,
			_te1_main_region_First_,
			_te2_main_region_First_,
			_te3_main_region_Second_,
			_te4_main_region_Second_,
			_te5_main_region_Second_,
			_te6_main_region_Second_
		};
		
		class EventInstance
		{
			public:
				explicit  EventInstance(Event id) noexcept : eventId(id){}
				virtual ~EventInstance() = default;
				const Event eventId;
		};
		
		
		/*! Gets the value of the variable 'counter' that is defined in the default interface scope. */
		sc::integer getCounter() const noexcept;
		/*! Sets the value of the variable 'counter' that is defined in the default interface scope. */
		void setCounter(sc::integer counter) noexcept;
		/*! Gets the value of the variable 'max' that is defined in the default interface scope. */
		static sc::integer getMax()  noexcept;
		/*! Gets the value of the variable 'exit12' that is defined in the default interface scope. */
		static sc::integer getExit12()  noexcept;
		/*! Gets the value of the variable 'exit21' that is defined in the default interface scope. */
		static sc::integer getExit21()  noexcept;
		/*! Gets the value of the variable 'a1' that is defined in the default interface scope. */
		sc::integer getA1() const noexcept;
		/*! Sets the value of the variable 'a1' that is defined in the default interface scope. */
		void setA1(sc::integer a1) noexcept;
		/*! Gets the value of the variable 'b1' that is defined in the default interface scope. */
		sc::integer getB1() const noexcept;
		/*! Sets the value of the variable 'b1' that is defined in the default interface scope. */
		void setB1(sc::integer b1) noexcept;
		/*! Gets the value of the variable 'a2' that is defined in the default interface scope. */
		sc::integer getA2() const noexcept;
		/*! Sets the value of the variable 'a2' that is defined in the default interface scope. */
		void setA2(sc::integer a2) noexcept;
		/*! Gets the value of the variable 'b2' that is defined in the default interface scope. */
		sc::integer getB2() const noexcept;
		/*! Sets the value of the variable 'b2' that is defined in the default interface scope. */
		void setB2(sc::integer b2) noexcept;
		/*! Gets the value of the variable 'c2' that is defined in the default interface scope. */
		sc::integer getC2() const noexcept;
		/*! Sets the value of the variable 'c2' that is defined in the default interface scope. */
		void setC2(sc::integer c2) noexcept;
		//! Inner class for default interface scope operation callbacks.
		class OperationCallback
		{
			public:
				virtual ~OperationCallback() = 0;
				
				virtual void dump(std::string text) = 0;
				
				
		};
		
		/*! Set the working instance of the operation callback interface 'OperationCallback'. */
		void setOperationCallback(std::shared_ptr<OperationCallback> operationCallback) noexcept;
		
		/*! Can be used by the client code to trigger a run to completion step without raising an event. */
		void triggerWithoutEvent() override;
		
		/*
		 * Functions inherited from StatemachineInterface
		 */
		 void enter() override;
		
		 void exit() override;
		
		/*!
		 * Checks if the state machine is active (until 2.4.1 this method was used for states).
		 * A state machine is active if it has been entered. It is inactive if it has not been entered at all or if it has been exited.
		 */
		 bool isActive() const noexcept override;
		
		
		/*!
		* Checks if all active states are final. 
		* If there are no active states then the state machine is considered being inactive. In this case this method returns false.
		*/
		 bool isFinal() const noexcept override;
		
		/*! 
		 * Checks if member of the state machine must be set. For example an operation callback.
		 */
		bool check() const noexcept;
		
		/*
		 * Functions inherited from TimedStatemachineInterface
		 */
		void setTimerService(std::shared_ptr<sc::timer::TimerServiceInterface> timerService_) noexcept override;
		
		std::shared_ptr<sc::timer::TimerServiceInterface> getTimerService() noexcept override;
		
		void raiseTimeEvent(sc::eventid event) override;
		
		sc::integer getNumberOfParallelTimeEvents() noexcept override;
		
		
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		bool isStateActive(State state) const noexcept;
		
		//! number of time events used by the state machine.
		static const sc::integer timeEventsCount {7};
		
		//! number of time events that can be active at once.
		static const sc::integer parallelTimeEventsCount {4};
		
		
	protected:
		
		
		std::deque<std::unique_ptr<EventInstance>> incomingEventQueue;
		
		std::unique_ptr<EventInstance> getNextEvent() noexcept;
		
		bool dispatchEvent(std::unique_ptr<EventInstance> event) noexcept;
		
		
		
	private:
		QTimerStatechart(const QTimerStatechart &rhs);
		QTimerStatechart& operator=(const QTimerStatechart&);
		
		sc::integer counter {1};
		static constexpr const sc::integer max {2};
		static constexpr const sc::integer exit12 {3100};
		static constexpr const sc::integer exit21 {2600};
		sc::integer a1 {0};
		sc::integer b1 {0};
		sc::integer a2 {0};
		sc::integer b2 {0};
		sc::integer c2 {0};
		
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc::ushort maxOrthogonalStates {1};
		
		std::shared_ptr<sc::timer::TimerServiceInterface> timerService;
		bool timeEvents[timeEventsCount];
		
		
		State stateConfVector[maxOrthogonalStates];
		
		
		
		std::shared_ptr<OperationCallback> ifaceOperationCallback {nullptr};
		
		bool isExecuting {false};
		
		
		
		// prototypes of all internal functions
		
		void enact_main_region_First();
		void enact_main_region_Second();
		void exact_main_region_First();
		void exact_main_region_Second();
		void enseq_main_region_First_default();
		void enseq_main_region_Second_default();
		void enseq_main_region__final__default();
		void enseq_main_region_default();
		void exseq_main_region_First();
		void exseq_main_region_Second();
		void exseq_main_region__final_();
		void exseq_main_region();
		void react_main_region__choice_0();
		void react_main_region__entry_Default();
		sc::integer main_region_First_react(const sc::integer transitioned_before);
		sc::integer main_region_Second_react(const sc::integer transitioned_before);
		void clearInEvents() noexcept;
		void microStep();
		void runCycle();
		
		
		
		
		
};


inline QTimerStatechart::OperationCallback::~OperationCallback() {}


#endif /* QTIMERSTATECHART_H_ */
