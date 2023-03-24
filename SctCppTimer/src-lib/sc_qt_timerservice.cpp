/* #
# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: Copyright (C) 2022 Steffen A. Mork
# */

#include "sc_qt_timerservice.h"

		
using namespace sc::qt;


SCTimer::SCTimer(QObject *parent, sc::timer::TimedInterface *machine, const sc::eventid id) :
    QTimer(parent),
    machine(machine),
    eventId(id)
{
    connect(this, SIGNAL(timeout()), this, SLOT(triggerTimeEvent()));
}

void SCTimer::triggerTimeEvent()
{
    emit fireTimeEvent(machine, eventId);
}



SCTimerService::SCTimerService(QObject *parent) : QObject(parent)
{
}


void SCTimerService::setTimer(sc::timer::TimedInterface *statemachine, sc::eventid event, int time_ms, bool isPeriodic)
{
    SCTimer *timer = nullptr;

    // retrieve the timer map for the state machine
    QMap<sc::eventid, SCTimer*> *eventTimerMap = machineTimerMapMap.value(statemachine);

    // retrieve and stop a timer if it already exists for the event.
    if (eventTimerMap != nullptr) {

        if (eventTimerMap->contains(event)) {
           SCTimer *timer = eventTimerMap->value(event);
           timer->stop();
        }
    }

    //setup the event timer map for the state machine if it not alrewady exists
    if ( eventTimerMap == nullptr) {
        eventTimerMap = new QMap<sc::eventid, SCTimer*>();
        machineTimerMapMap.insert(statemachine, eventTimerMap);
    }

    // create a timer if it not already exists
    if (timer == nullptr) {
		timer = new SCTimer(this, statemachine, event);
        eventTimerMap->insert(event, timer);
        timer->connect(timer, SIGNAL(fireTimeEvent(sc::timer::TimedInterface*,sc::eventid)), this, SLOT(raiseTimeEvent(sc::timer::TimedInterface*,sc::eventid)));
    }

    // amor the timer
    timer->setTimerType(Qt::TimerType::PreciseTimer);
    timer->setInterval(time_ms);
    timer->setSingleShot(!isPeriodic);
    timer->start();

}


SCTimer* SCTimerService::getTimer(sc::timer::TimedInterface *machine, sc::eventid event)
{
    SCTimer *timer = nullptr;

    // retrieve the timer map for the state machine
    QMap<sc::eventid, SCTimer*> *eventTimerMap = machineTimerMapMap.value(machine);

    // retrieve and a timer registered for the event.
    if (eventTimerMap != nullptr) {

        if (eventTimerMap->contains(event)) {
            timer = eventTimerMap->value(event);
        }
    }

    return timer;
}


void SCTimerService::unsetTimer(sc::timer::TimedInterface *statemachine, sc::eventid event)
{
    SCTimer *timer = this->getTimer(statemachine, event);

    if (timer != nullptr) {
        timer->stop();
    }

    // do nothing else as the timer may be reused...
}


void SCTimerService::raiseTimeEvent(sc::timer::TimedInterface *machine, sc::eventid event)
{
    SCTimer *timer = this->getTimer(machine, event);
    if (timer != nullptr && timer->isSingleShot()) {
        timer->stop();
    }

    if (machine != nullptr) {
        machine->raiseTimeEvent(event);
    }
}


void SCTimerService::cancel()
{
}


