#include "course_record.h"

std::istream& operator>>(std::istream& i, CourseRecord& courseRecord) {
	
	unsigned long time;

	while (i >> time) {
		CourseRecordEntry cre;
		cre.time = time;
		i >> cre.position.x;
		i >> cre.position.y;
		i >> cre.position.angle;
		courseRecord.entries.push_back(cre);
	}

	return i;
}

std::ostream& operator<<(std::ostream& o, const CourseRecord& courseRecord) {
	for (int i = 0; i < courseRecord.entries.size(); i++) {
		const CourseRecordEntry* cre = &courseRecord.entries.at(i);
		o << cre->time << " " << cre->position.x << " " << cre->position.y << " " << cre->position.angle << std::endl;
	}
	return o;
}

CourseRecord::CourseRecord() {
	lastCheckedPositionIndex = 0;
	lastCheckedPositionTime = 0;
}

CourseRecord::~CourseRecord()
{
}

//Ajoute une position ? un temps dans le vecteur
void CourseRecord::recordTimeAndPosition(Position position, unsigned long time) {
	CourseRecordEntry cre;
	cre.position = position;
	cre.time = time;
	entries.push_back(cre);
}

//Load un record existant avec le nom de la map
bool CourseRecord::loadFromMap(string _mapName) {
	mapName = _mapName;

	ifstream file;
	file.open(".\\maps\\" + mapName + "\\record.courserecord");

	if (!file.is_open()) return false;

	file >> *this;

	return true;
}

//Set le nom de la map
void CourseRecord::setMapName(string _mapName) {
	mapName = _mapName;
}

bool CourseRecord::save() {
	if (mapName == "") return false;

	if (!filesystem::is_directory(".\\maps\\" + mapName)) return false;

	ofstream ofs(".\\maps\\" + mapName + "\\record.courserecord", ofstream::trunc);

	ofs << *this;

	return true;
}

//Reset le record
void CourseRecord::reset() {
	lastCheckedPositionIndex = 0;
	lastCheckedPositionTime = 0;
	entries.clear();
}

//Clear le vecteur de entries
void CourseRecord::clear() {
	entries.clear();
}

//Reset le record et load la map ? partir du fichier
void CourseRecord::resetAndLoadFromFile() {
	reset();
	loadFromMap(mapName);
}

//Retourne la position qu'on ?tait ? un temps. Essaie d'?tre le plus efficace possible
Position CourseRecord::getPositionAtTime(unsigned long time) {
	if (lastCheckedPositionTime > time) {
		lastCheckedPositionTime = time;
		lastCheckedPositionIndex = 0;
	}

	for (int i = lastCheckedPositionIndex + 1; i < entries.size(); i++) {
		if (entries.at(i).time > time) {
			lastCheckedPositionIndex = i - 1;
			lastCheckedPositionTime = time;
			return entries.at(i - 1).position;
		}
	}

	return Position();
}
