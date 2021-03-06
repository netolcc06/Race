#ifndef __RACE__
#define __RACE__

#include <vector>
#include <string>
#include "Pilot.h"

using namespace std;


/** A race has many pilots.
  * Each pilot contains (string)id, (float)time, (int)laps_comleted, (float)avg_speed.
  * The function Race::run() parses the input and updates the pilots data.
  * If the pilot doesn't exist, a new pilot is inserted in vector<Pilot> pilots.
  * In the end, vector<Pilot> pilots is sorted according to the final time of the whole
  * race for each pilot in order to present the results of the race.
  **/
class Race {
	public:
		
		Race(){	}

		void run(string path_) {

			ifstream in_file(path_);
			string line, op;
			stringstream linestream;

			//Skip the first line
			getline(in_file, line);

			// Each line is used to update the data of the current pilot (identified by the id).
			while (getline(in_file, line))
			{
				// String stream to hold the whole content of a line
				istringstream ss(line);
				PARSER it = TIME;

				int laps_completed_ = 0;
				string id_, name_;
				float time_ = 0.0f, avg_speed_ = 0.0f;

				// Each line (istringstream ss) is parsed
				while (!ss.eof()) {
					
					// String stream outputs the operation to be performed / data to be saved
					ss >> op;

					// it is used as an interator for each part of the line to be parsed
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

					//Skips the character '-'
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
						time_ = parseTime(op);
						it = AVG_SPEED;
						break;
					}
					case AVG_SPEED:
					{
						avg_speed_ = parseAvgSpeed(op);

						int pos = this->pilotExists(id_);
						if (pos == -1)
							this->insertPilot(id_, name_, laps_completed_, time_, avg_speed_);
						else
							this->update(pos, laps_completed_, time_, avg_speed_);

						it = TIME;
						break;
					}

					default:
						break;
					}
				}
				linestream.clear();
			}

			in_file.close();
			// The race ends and it calculates the final positions for the pilots
			this->endOfLine();
		}

		float parseTime(string op){
			//Time is in the format h:mm:ss.mmm, such as 1:02.852
			int mins_ = 0, seconds_ = 0, miliseconds_ = 0;
			float time_ = 0.0f;
			string helper = "";

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

			return time_;
		}

		float parseAvgSpeed(string op) {
			//Average speed is in the format ii,iii. For example: 44,275
			int integer_ = 0, decimal_ = 0;
			float avg_speed_ = 0.0f;
			string helper = "";

			for (unsigned int i = 0; i < op.size(); i++) {
				// Integer part is before the ','
				if (op[i] == ',') {
					integer_ = stoi(helper);
					helper.clear();
				}
				else {
					// Decimal part is after the ','
					helper += op[i];
					if (i == op.size() - 1) {
						decimal_ = stoi(helper);
						avg_speed_ = (float)integer_ + (float)decimal_ / (float)(pow(10, helper.size()));
						helper.clear();
					}
				}
			}

			helper.clear();
			return  avg_speed_;
		}

		void insertPilot(string id_, string name_, int laps_completed_, float lap_time_, float avg_speed_) {
			Pilot newPilot(id_, name_);
			//Pilot is inserted with the name and id obtained in his first lap.
			newPilot.Update(laps_completed_, lap_time_, avg_speed_);
			pilots.push_back(newPilot);
		}

		int pilotExists(string id_){

			/** Returns the position of a pilot in the vector pilot, if there is a pilot with the id 
			 *  equivalent to the parameter string id_.
			 *  Returns -1 in case there is not a pilot with such id.
			 */
			for (unsigned int i = 0; i < pilots.size(); i++) {
				if (pilots[i].getId() == id_)
					return i;
			}

			return -1;
		}

		void update(int pos, int laps_completed_, float lap_time_, float avg_speed_){
			// Updates the data of a pilot after completed a new lap
			pilots[pos].Update(laps_completed_, lap_time_, avg_speed_);
		}

		void endOfLine() {
			/** After the laps are completed, the pilots are sorted considering the total amount of time
			  * each one of the needed to complete the race.
			  * The final classification of each pilot is inferred from its result.
			  */
			sort(pilots.begin(), pilots.end());
		}

		void toFile(string path) {
			ofstream file_out;
			file_out.open(path);
			int finalPos = 1;
			float winnerTime = pilots[0].getTotalTime();
			
			for (Pilot p : pilots) {
				/** Displays the total amount of time each pilot needed to complete the race.
				  * The total amount of time is transformed from a float to a composition of
				  * strings in the format: xx:yy:zz.mm, where: 
				  * xx := hours, yy := minutes, zz := seconds, mm := miliseconds
				  */
				string stringTotalTime = floatTimeToString(p.getTotalTime());
				
				file_out << finalPos << "\t" << p.getId() << "\t" << p.getName()<< " " << "\t" << p.getLapsCompleted()
					<< "\t" << stringTotalTime << "\t" << "+(" << floatTimeToString(p.getTotalTime()-winnerTime) 
					<< ")" << endl;
				
				finalPos++;
			}

			file_out.close();

		}


		/** 
		  * Transforms float time into a composition of strings in the format: xx:yy:zz.mm, where:
		  * xx := hours, yy := minutes, zz := seconds, mm := miliseconds
		  */
		string floatTimeToString(float time_) {
			int integerTime = (int)time_, helper = 0;
			int hours = 0, minutes = 0, seconds = 0, miliseconds = (time_ - integerTime) * 1000;
			string elapsedTime = "";

			hours = integerTime / 3600;
			helper = integerTime % 3600;
			minutes = helper / 60;
			seconds = helper % 60;

			elapsedTime += to_string(hours); 
			elapsedTime += ":"; 
			if (minutes < 10)
				elapsedTime += "0";
			elapsedTime += to_string(minutes);
			elapsedTime += ":"; 
			if (seconds < 10)
				elapsedTime += "0";
			elapsedTime += to_string(seconds); 
			elapsedTime += "."; 
			if (miliseconds < 100){
				if(miliseconds < 10)
					elapsedTime += "00";
				else
					elapsedTime += "0";
			}
			elapsedTime += to_string(miliseconds);

			return elapsedTime;
		}

	private:
		vector<Pilot> pilots;
};

#endif // !__RACE__
