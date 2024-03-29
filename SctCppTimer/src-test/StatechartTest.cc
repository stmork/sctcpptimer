/** *
//
// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright (C) 2021-2023 Steffen A. Mork
//
* */
#include <string>
#include "gtest/gtest.h"
#include "Statechart.h"
#include "sc_runner_timed.h"
#include "sc_types.h"

#define SC_UNUSED(P) (void)P

namespace  {

Statechart* statechart;


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
	void dump(std::string text) override {
		dumpMock->dump(text);
	}
};

//! The timers are managed by a timer service. */
static TimedSctUnitRunner * runner;

class StatechartTest : public ::testing::Test{
	protected:
	virtual void SetUp() override {
		statechart = new Statechart();
		runner = new TimedSctUnitRunner(
			statechart,
			true,
			200
		);
		statechart->setTimerService(runner);
	}
	virtual void TearDown() override {
		delete statechart;
		delete runner;
	}
};


TEST_F(StatechartTest, testFirst) {
	dumpMock = new DumpMock();
	
	MockDefault defaultMock;
	statechart->setOperationCallback(&defaultMock);
	statechart->enter();
	
	EXPECT_TRUE(dumpMock->calledAtLeastOnce());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_First));
	
	runner->proceed_time(400);
	
	EXPECT_TRUE((statechart->getA1()) == (1));
	
	EXPECT_TRUE((statechart->getB1()) == (0));
	
	runner->proceed_time(400);
	
	EXPECT_TRUE((statechart->getA1()) == (2));
	
	EXPECT_TRUE((statechart->getB1()) == (1));
	
	
	dumpMock->reset();
}
TEST_F(StatechartTest, testSecond) {
	dumpMock = new DumpMock();
	
	MockDefault defaultMock;
	statechart->setOperationCallback(&defaultMock);
	statechart->enter();
	
	EXPECT_TRUE(dumpMock->calledAtLeastOnce());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_First));
	
	runner->proceed_time(statechart->getExit12());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_Second));
	
	runner->proceed_time(300);
	
	EXPECT_TRUE((statechart->getA2()) == (1));
	
	EXPECT_TRUE((statechart->getB2()) == (2));
	
	EXPECT_TRUE((statechart->getC2()) == (0));
	
	
	dumpMock->reset();
}
TEST_F(StatechartTest, testReenterFirst) {
	dumpMock = new DumpMock();
	
	MockDefault defaultMock;
	statechart->setOperationCallback(&defaultMock);
	statechart->enter();
	
	EXPECT_TRUE(dumpMock->calledAtLeastOnce());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_First));
	
	runner->proceed_time(statechart->getExit12());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_Second));
	
	statechart->enter();
	
	runner->proceed_time(statechart->getExit21());
	
	EXPECT_TRUE(statechart->isStateActive(Statechart::State::main_region_First));
	
	EXPECT_TRUE((statechart->getCounter()) == (1));
	
	
	dumpMock->reset();
}
TEST_F(StatechartTest, testLeave) {
	
	MockDefault defaultMock;
	statechart->setOperationCallback(&defaultMock);
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

