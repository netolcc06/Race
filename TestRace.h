#ifndef __TESTRACE__ 
#define __TESTRACE__

#include "Pilot.h"
#include "Race.h"
#include <assert.h>
#include <string>

using namespace std;

class TestRace{

public:

	TestRace() {}

	void runTests() {
		this->testParseTime();
		this->testParseAvgSpeed();
		this->testPilotExists();
		this->testFloatTimeToString();
	}

	void testParseTime() {
		Race race;
		string time = "2:03.342";
		float expected = 123.342f;

		assert(race.parseTime(time) == expected);
	}

	void testParseAvgSpeed() {
		Race race;
		string time = "123,342";
		float expected = 123.342f;

		assert(race.parseAvgSpeed(time) == expected);
	}

	void testPilotExists() {
		// This test implicitly tests the method insertPilot
		Race race;
		Pilot pilot("1", "Senna");
		int expected = -1;
		assert(race.pilotExists("1") == expected);
		race.insertPilot(pilot.getId(), pilot.getName(), 1,1.0f,1.0f);
		expected = 0;
		assert(race.pilotExists("1") == expected);
	}

	void testFloatTimeToString() {
		Race race;
		float time = 121.345;
		string expected = "0:02:01.345";
		assert(race.floatTimeToString(time) == expected);
	}
	
private:

};

#endif // !__TESTRACE__
