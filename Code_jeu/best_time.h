#ifndef BEST_TIME_H
#define BEST_TIME_H

#include <string>
#include <iostream>
struct BestTime {
	std::string name;
	unsigned long time;

	friend std::istream& operator>>(std::istream& is, BestTime& bestTime) {
		std::string pName;
		unsigned long pTime;
		is >> pName >> pTime;
		bestTime.name = pName;
		bestTime.time = pTime;
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const BestTime& bestTime) {
		os << bestTime.name << " " << bestTime.time << std::endl;
		return os;
	}

	//Retourne vai si les TEMPS sont égals
	friend bool operator==(const BestTime& bt1, const BestTime& bt2) {
		return (bt1.time == bt2.time);
	}

	//Retourne vrai si le temps est plus petit
	friend bool operator<(const BestTime& bt1, const BestTime& bt2) {
		return (bt1.time < bt2.time);
	}

	//Retourne vrai si le temps est plus grand
	friend bool operator>(const BestTime& bt1, const BestTime& bt2) {
		return (bt1.time > bt2.time);
	}

	//Retourne vrai si le temps est plus grand ou égal
	friend bool operator>=(const BestTime& bt1, const BestTime& bt2) {
		return (bt1.time > bt2.time || bt1.time == bt2.time);
	}

	//Retourne vrai si le temps est plus petit ou égal
	friend bool operator<=(const BestTime& bt1, const BestTime& bt2) {
		return (bt1.time < bt2.time || bt1.time == bt2.time);
	}

};



#endif