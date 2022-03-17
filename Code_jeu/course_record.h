#ifndef COURSE_RECORD_H
#define COURSE_RECORD_H

#include "position.h"
#include <vector>
#include <iostream>

using namespace std;

struct CourseRecordEntry{
	Position position;
	unsigned long time;
};

class CourseRecord : public vector<CourseRecordEntry> {
public:
	CourseRecord ();
	~CourseRecord ();

	friend std::istream& operator>>(std::istream&, CourseRecord&);
	friend std::ostream& operator<<(std::ostream&, const CourseRecord&);
};

#endif // COURSE_RECORD_H
