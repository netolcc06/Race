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

	cout << "teste" << endl;

	std::string path("C:\\Users\\netolcc06\\Documents\\Visual Studio 2015\\Projects\\Race\\race.txt");

	std::ifstream in_file(path);
	std::string line, op;
	std::stringstream linestream;
	Race race;

	//skip first line
	std::getline(in_file, line);

	while (std::getline(in_file, line))
	{
		//enum PARSER { TIME, PILOT_ID, SKIP, PILOT_NAME, LAP, LAP_TIME, AVG_SPEED };
		std::istringstream ss(line);
		//linestream << line;
		//linestream >> op;
		PARSER it = TIME;		

		int laps_completed_ = 0;
		string id_, name_;
		float time_ = 0.0f, avg_speed_ = 0.0f;

		while (!ss.eof()) {
			// class race has many pilots
			// pilot has (string)id, (float)time, (int)laps_comleted, (float)velcidade media
			// faz o parse, le o id, atualiza dados
			// se ainda nao existir, inserir piloto [ID]
			// no fim, ordenar vetor de acordo com o tempo
			//TIME         ID     NAME  LAP LAP_TIME VELOCIDADE MEDIA DA VOLTA
			//23:49:08.277 038 – F.MASSA 1 1:02.852 44,275
			// hora e tempo precisam ser colocadas em 
			ss >> op;
			
			//enum PARSER { TIME, PILOT_ID, SKIP, PILOT_NAME, LAP, LAP_TIME, AVG_SPEED };
			//23:49:08.277 038 – F.MASSA 1 1:02.852 44, 275

			switch (it) {
				case TIME:
				{
					//We do not need to store the beginning of the LAP
					it = PILOT_ID;
					break;
				}
				case PILOT_ID: 
				{
					id_ = op;
					it = SKIP;
					break;
				}
					
				case SKIP:
				{
					it = PILOT_NAME;
					break;
				}
					
				case PILOT_NAME:
				{
					name_ = op;
					it = LAP;
					break;
				}
					
				case LAP:
				{
					laps_completed_ = stoi(op);
					it = LAP_TIME;
					break;
				}
				case LAP_TIME:
				{
					//1:02.852
					int mins_ = 0, seconds_ = 0, miliseconds_ = 0;
					string helper="";

					for (unsigned int i = 0; i < op.size(); i++) {
						if (op[i] == ':') {
							mins_ = stoi(helper);
							helper.clear();
						}
						else if (op[i] == '.') {
							seconds_ = stoi(helper);
							helper.clear();
						}
						else {
							helper += op[i];
							if (i == op.size() - 1) {
								miliseconds_ = stoi(helper);
								time_ = (float)mins_ * 60.0f + (float)seconds_ + (float)miliseconds_ / (float)(pow(10, helper.size()));
								helper.clear();
							}
						}
					}

					helper.clear();

					it = AVG_SPEED;
					break;
				}
				case AVG_SPEED:
				{
					//44,275

					int integer_ = 0, decimal_ = 0;
					string helper = "";

					for (unsigned int i = 0; i < op.size(); i++) {
						if (op[i] == ',') {
							integer_ = stoi(helper);
							helper.clear();
						}
						else {
							helper += op[i];
							if (i == op.size() - 1) {
								decimal_ = stoi(helper);
								avg_speed_ = (float)integer_ + (float)decimal_ / (float)(float)(pow(10, helper.size()));
								helper.clear();
							}
						}
					}

					helper.clear();

					int pos = race.pilotExists(id_);
					if (pos == -1) {
						race.insertPilot(id_, name_, laps_completed_, time_, avg_speed_);
					}
					else {
						race.update(pos, laps_completed_, time_, avg_speed_);
					}


					it = TIME;
					break;
				}
					
				default:
					break;
			}
		}
		cout << endl;

		linestream.clear();
	}

	in_file.close();
	race.endOfLine();
	race.toFile("raceOut.txt");
	system("pause");

	return 0;
}