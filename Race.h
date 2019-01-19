#ifndef __RACE__
#define __RACE__

#include <vector>
#include <string>
#include "Pilot.h"

using namespace std;

class Race {
	public:
		
		Race() {}

		void insertPilot(string id_, string name_, int laps_completed_, float lap_time_, float avg_speed_) {
			Pilot newPilot(id_, name_);
			newPilot.Update(laps_completed_, lap_time_, avg_speed_);
			pilots.push_back(newPilot);
		}

		int pilotExists(string id_){

			for (unsigned int i = 0; i < pilots.size(); i++) {
				if (pilots[i].getId() == id_)
					return i;
			}

			return -1;
		}

		void update(int pos, int laps_completed_, float lap_time_, float avg_speed_){
			pilots[pos].Update(laps_completed_, lap_time_, avg_speed_);
		}

		void endOfLine() {
			sort(pilots.begin(), pilots.end());
		}

		void toFile(string path) {
			std::ofstream file_out;
			file_out.open(path);
			int finalPos = 1;
			
			for (Pilot p : pilots) {
				int integerTime = (int)(p.getTotalTime()), helper = 0;
				int hours = 0, minutes = 0, seconds = 0, miliseconds = (p.getTotalTime()-integerTime)*1000;

				hours = integerTime / 3600;
				helper = integerTime % 3600;
				minutes = helper / 60;
				seconds = helper % 60;
				
				file_out << finalPos << "\t" << p.getId() << "\t" << p.getName()<< " " << "\t" << p.getLapsCompleted()
					<< "\t" << hours <<":"<< minutes<<":"<< seconds<<"."<<miliseconds << endl;
				
				finalPos++;
			}

			file_out.close();

		}

	private:
		vector<Pilot> pilots;


};
#endif // !__RACE__
