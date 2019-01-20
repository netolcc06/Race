#ifndef __PILOT__
#define __PILOT__

#include<string>

using namespace std;

class Pilot {
	public:
		Pilot(string id_, string name_){
			this->id = id_;
			this->name = name_;
			this->laps_completed = 0;
			this->time = 0.0f;
			this->avg_speed = 0.0f;
		}
		void Update(int laps_completed_, float lap_time_, float avg_speed_) {
			// The race contains only 4 laps.
			if(laps_completed_<=4){
				this->laps_completed = laps_completed_;
				this->time += lap_time_;
				// Still need Proof check
				this->avg_speed = (avg_speed_ + this->avg_speed) / 2; 
				
				if (laps_completed_ == 1)
					this->best_lap = lap_time_;
				else
					this->best_lap = (lap_time_ < this->best_lap) ? lap_time_ : this->best_lap;
			}

		}

		bool operator<(Pilot rhs)const {
			return this->time < rhs.getTotalTime();
		}

		string getId() { return this->id; }
		string getName() { return this->name; }
		int getLapsCompleted() { return this->laps_completed; }
		float getTotalTime() { return this->time; }
		float getAvgSpeed() { return this->avg_speed; }
		float getBestLap() { return this->best_lap; }

	private:	
		int laps_completed;
		string id, name;
		float time, avg_speed, best_lap;

};

#endif

