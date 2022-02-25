#ifndef BEST_TIME_H
#define BEST_TIME_H

#include <string>
struct BestTime {
	std::string name;
	std::string time;

	friend std::istream& operator>>(std::istream& is, BestTime& bestTime) {
		std::string pName, pTime;
		is >> pName >> pTime;
		bestTime.name = pName;
		bestTime.time = pTime;
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const BestTime& bestTime) {
		os << bestTime.name << " " << bestTime.time << std::endl;
		return os;
	}
};



#endif