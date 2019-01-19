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

using namespace std;

int main(int argc, char* argv[]) {

	string path("C:\\Users\\netolcc06\\Documents\\Visual Studio 2015\\Projects\\Race\\race.txt");
	string out_path("raceOut.txt");

	Race race;	
	race.run(path);
	race.toFile(out_path);

	return 0;
}