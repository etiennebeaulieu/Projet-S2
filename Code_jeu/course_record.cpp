#include "course_record.h"

std::istream& operator>>(std::istream& i, CourseRecord& courseRecord) {
	
	unsigned long time;

	while (i >> time) {
		CourseRecordEntry cre;
		cre.time = time;
		i >> cre.position.x;
		i >> cre.position.y;
		i >> cre.position.angle;
		courseRecord.push_back(cre);
	}

	return i;
}

std::ostream& operator<<(std::ostream& o, const CourseRecord& courseRecord) {
	for (int i = 0; i < courseRecord.size(); i++) {
		const CourseRecordEntry* cre = &courseRecord.at(i);
		o << cre->time << " " << cre->position.x << " " << cre->position.y << " " << cre->position.angle;
	}
	return o;
}
