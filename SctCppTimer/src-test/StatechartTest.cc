/** *
//
// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright (C) 2022-2024 Steffen A. Mork
//
* */
#include <string>
#include <list>
#include <algorithm>
#include "gtest/gtest.h"
#include "Statechart.h"
#include "sc_runner_timed.h"
#include "sc_types.h"

#define SC_UNUSED(P) (void)P

namespace  {

std::shared_ptr<Statechart> statechart;


class DumpMock{
	struct parameters {
		std::string text;
		int callCount;
		inline bool operator==(const parameters& other) {
			return (this->text == other.text);
		}
	};
	public:
	std::list<DumpMock::parameters> paramCount;
	int callCount;

	bool calledAtLeast(const int times){
		return (callCount >= times);
	}
	
	bool calledAtLeastOnce(){
		return (callCount>0);
	}

	bool calledAtLeast(const int times, const std::string text){
		parameters p;
		p.text = text;
		
		std::list<DumpMock::parameters>::iterator i = std::find(paramCount.begin(), paramCount.end(), p);
		if(i != paramCount.end()) {
			return (i->callCount >= times);
		}else{
			return false;
		}
	}
	
	bool calledAtLeastOnce(const std::string text){
		parameters p;
		p.text = text;
		
		std::list<DumpMock::parameters>::iterator i = std::find(paramCount.begin(), paramCount.end(), p);
		if(i != paramCount.end()) {
			return (i->callCount > 0);
		}else{
			return false;
		}
	}

	void dump(const std::string text) {
		++callCount;
		
		parameters p;
		p.text = text;
		
		std::list<DumpMock::parameters>::iterator i = std::find(paramCount.begin(), paramCount.end(), p);
		if(i != paramCount.end()) {
			p.callCount = (++i->callCount);
			paramCount.erase(i);
			
		}else{
			p.callCount = 1;
		}
		paramCount.push_back(p);
	}
	void reset() {
		callCount = 0;
		paramCount.clear();
	}
};
static DumpMock* dumpMock;

class MockDefault : public Statechart::OperationCallback {
	public:
	void dump(std::string text) {
		dumpMock->dump(text);
	}
};

//! The timers are managed by a timer service. */
static std::shared_ptr<TimedSctUnitRunner > runner;

class StatechartTest : public ::testing::Test{
	protected:
	std::shared_ptr<MockDefault> defaultMock = std::make_shared<MockDefault>();
	virtual void SetUp() {
		statechart = std::make_shared<Statechart>();
		size_t maximalParallelTimeEvents = (size_t)statechart->getNumberOfParallelTimeEvents();
		runner = std::make_shared<TimedSctUnitRunner>(
			maximalParallelTimeEvents
		);
		statechart->setTimerService(runner);
		dumpMock = new DumpMock();
		statechart->setOperationCallback(defaultMock);
	}
	virtual void TearDown() {
		delete dumpMock;
		 statechart.reset();
		 runner.reset();
	}
};


TEST_F(StatechartTest, testFirst) {
	statechart->enter();
	
	EXPECT_TRUE(dumpMock->calledAtLeastOnce());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_First));
	
	runner->proceed_time(400);
	
	EXPECT_TRUE((statechart->getA1()) == (1));
	
	EXPECT_TRUE((statechart->getB1()) == (0));
	
	runner->proceed_time(400);
	
	EXPECT_TRUE((statechart->getA1()) == (2));
	
	EXPECT_TRUE((statechart->getB1()) == (1));
	
}
TEST_F(StatechartTest, testSecond) {
	statechart->enter();
	
	EXPECT_TRUE(dumpMock->calledAtLeastOnce());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_First));
	
	runner->proceed_time(statechart->getExit12());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_Second));
	
	runner->proceed_time(300);
	
	EXPECT_TRUE((statechart->getA2()) == (1));
	
	EXPECT_TRUE((statechart->getB2()) == (2));
	
	EXPECT_TRUE((statechart->getC2()) == (0));
	
}
TEST_F(StatechartTest, testReenterFirst) {
	statechart->enter();
	
	EXPECT_TRUE(dumpMock->calledAtLeastOnce());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_First));
	
	runner->proceed_time(statechart->getExit12());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_Second));
	
	statechart->enter();
	
	runner->proceed_time(statechart->getExit21());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_First));
	
	EXPECT_TRUE((statechart->getCounter()) == (1));
	
}
TEST_F(StatechartTest, testLeave) {
	statechart->enter();
	
	sc::integer i = statechart->getCounter();
	
	while ((i) <= (statechart->getMax())) {
		EXPECT_TRUE((statechart->getCounter()) == (i));
		EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_First));
		runner->proceed_time(statechart->getExit12());
		EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_Second));
		runner->proceed_time(statechart->getExit21());
		i++;
	}
	
	EXPECT_TRUE((statechart->getA1()) == (statechart->getExit12()/301*statechart->getMax()));
	
	EXPECT_TRUE((statechart->getB1()) == (statechart->getMax()));
	
	EXPECT_TRUE((statechart->getA2()) == (statechart->getExit21()/250*statechart->getMax()));
	
	EXPECT_TRUE((statechart->getB2()) == (statechart->getExit21()/150*statechart->getMax()));
	
	EXPECT_TRUE((statechart->getC2()) == (statechart->getMax()));
	
	EXPECT_TRUE((statechart->getCounter()) == (statechart->getMax()));
	
}

}

