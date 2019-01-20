#ifndef __TESTPILOT__ 
#define __TESTPILOT__

#include "Pilot.h"
#include <assert.h>
#include <string>

using namespace std;

class TestPilot {

public:
	
	TestPilot(){}

	void runTests() {
		this->testGetId();
		this->testGetName();
		this->testGetLapsCompleted();
		this->testUpdate();
		this->testGetTotalTime();
		this->testGetAvgSpeed();
		this->testGetBestLap();
		this->testOperatorLeast();
	}

	void testGetId() {
		Pilot pilot("1","test");
		string expected = "1";
		assert(pilot.getId() == expected);
	}
	
	void testGetName() {
		Pilot pilot("1", "test");
		string expected = "test";
		assert(pilot.getName() == expected);
	}

	void testGetLapsCompleted() {
		Pilot pilot("1", "test");
		pilot.Update(4, 1.0f, 1.0f);
		int expected = 4;
		assert(pilot.getLapsCompleted() == expected);
	}

	void testUpdate() {
		Pilot pilot("1", "test");
		pilot.Update(4, 1.0f, 1.0f);
		pilot.Update(5, 1.0f, 1.0f);
		int expected = 4;
		// Since the race has only 4 laps, trying to update it with a greater number (5 in this example)
		// should return 4.
		assert(pilot.getLapsCompleted() == expected);
	}

	void testGetTotalTime() {
		Pilot pilot("1", "test");
		pilot.Update(1, 1.0f, 1.0f);
		pilot.Update(2, 2.5f, 1.0f);
		float expected = 3.5f;
		assert(pilot.getTotalTime() == expected);
	}

	void testGetAvgSpeed() {
		Pilot pilot("1", "test");
		pilot.Update(1, 1.0f, 2.0f);
		pilot.Update(2, 1.0f, 3.0f);
		float expected = 2.5f;
		assert(pilot.getAvgSpeed() == expected);
	}

	void testGetBestLap() {
		Pilot pilot("1", "test");
		pilot.Update(1, 1.0f, 2.0f);
		pilot.Update(2, 2.0f, 3.0f);
		float expected = 1.0f;
		assert(pilot.getBestLap() == expected);
	}

	void testOperatorLeast(){
		Pilot pilotA("1", "test");
		Pilot pilotB("2", "test");
		pilotA.Update(1, 1.0f, 2.0f);
		pilotB.Update(1, 0.8f, 3.0f);
		assert(pilotB<pilotA);
	}

private:

};

#endif // !__TESTPILOT__
