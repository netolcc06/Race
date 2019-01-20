#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>

#include <fstream>
#include <sstream>
#include <math.h>

#include "Utils.h"
#include "Pilot.h"
#include "Race.h"
#include "TestPilot.h"
#include "TestRace.h"

using namespace std;

int main(int argc, char* argv[]) {

	string path(argv[1]);
	string out_path(argv[2]);

	Race race;	
	race.run(path);
	race.toFile(out_path);

	TestPilot testPilot;
	testPilot.runTests();

	TestRace testRace;
	testRace.runTests();

	return 0;
}