/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (C) 2022-2026 Steffen A. Mork
 */

#ifndef SC_QT_TIMERSERVICE_H_
#define SC_QT_TIMERSERVICE_H_

#include <memory>

#include <QTimer>
#include <QHash>

#include "sc_timer.h"

namespace sc::qt
{
	class SCTimerService : public QObject, public sc::timer::TimerServiceInterface
	{
		Q_OBJECT

	public:
		explicit SCTimerService(QObject * parent = nullptr);

		virtual void setTimer(
			std::shared_ptr<sc::timer::TimedInterface> statemachine,
			sc::eventid                                event,
			sc::time                                   time_ms,
			bool                                       isPeriodic) override;
		virtual void unsetTimer(
			std::shared_ptr<sc::timer::TimedInterface> statemachine,
			sc::eventid                                event) override;
		virtual void unsetTimerRaw(
			sc::timer::TimedInterface * statemachine,
			sc::eventid                 event) override;
		virtual void cancel();

	protected:

		/**
		 * This is the two dimensional key for finding a QTimer instance.
		 */
		typedef std::pair<sc::timer::TimedInterface *, sc::eventid> TimerKey;

		/**
		 * This defines a map from a two dimensional key to a concrete
		 * QTimer instance.
		 */
		typedef QHash<TimerKey, QTimer *>                           TimerMap;

		/**
		 * The map from all statemachines and their IDs to all existing timers.
		 */
		TimerMap                                                    chart_map;

		[[nodiscard]]
		QTimer * getTimer(
			std::shared_ptr<sc::timer::TimedInterface> & statemachine,
			sc::eventid                                  event);
	};
}

#endif // SC_QT_TIMERSERVICE_H_


