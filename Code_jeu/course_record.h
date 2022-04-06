#ifndef COURSE_RECORD_H
#define COURSE_RECORD_H

#include "position.h"
#include <vector>
#include <iostream>
#include <string>

#include <fstream>
#include <filesystem>

using namespace std;

struct CourseRecordEntry{
	Position position;
	unsigned long time;
};

class CourseRecord : public vector<CourseRecordEntry> {
public:
	CourseRecord();
	~CourseRecord();

	void recordTimeAndPosition(Position position, unsigned long time);

	bool loadFromMap(string _mapName);

	void setMapName(string _mapName);

	bool save();

	Position getPositionAtTime(unsigned long time);

	friend std::istream& operator>>(std::istream&, CourseRecord&);
	friend std::ostream& operator<<(std::ostream&, const CourseRecord&);

private:
	string mapName;

	//Permet de faire des check de position à des temps plus rapidement:
	int lastCheckedPositionIndex;
	unsigned long lastCheckedPositionTime;
};

#endif // COURSE_RECORD_H
