#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <fstream>
#include <filesystem>
#include "best_time.h"

using namespace std;

class Leaderboard
{
public:
	Leaderboard();
	Leaderboard(string mapName);
	~Leaderboard();

	BestTime getTime(int index);

	void newTime(BestTime time);

	bool isBestTime(unsigned long time);

	bool loadFromMap(string _mapName);

	int getLength();

	bool save();

	friend std::istream& operator>>(std::istream&, Leaderboard&);
	friend std::ostream& operator<<(std::ostream&, const Leaderboard&);



private:
	BestTime bestTimes[5];
	string mapName;
};

#endif // !LEADERBOARD_H
