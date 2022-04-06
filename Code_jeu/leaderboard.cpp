#include "leaderboard.h"

Leaderboard::Leaderboard() {
	mapName = "";
}

Leaderboard::Leaderboard(string mapName) : Leaderboard() {
	loadFromMap(mapName);
}

Leaderboard::~Leaderboard() {
}

//Retourne le BestTime à l'index
BestTime Leaderboard::getTime(int index) {
	return bestTimes[index];
}

//Sauvegarde un nouveau temps si il est meilleur qu'un autre
void Leaderboard::newTime(BestTime time) {
	for (int i = 0; i < 5; i++) {
		if (time > bestTimes[i]) {
			BestTime temp = bestTimes[i];
			bestTimes[i] = time;
			for (int j = i+1; j < 5; j++) {
				BestTime temp2 = bestTimes[i];
				bestTimes[j] = temp;
				temp = temp2;
			}
			break;
		}
	}
}

//Retourne vrai si le temps en paramètre est plus grand ou égal au temps le plus haut dans le leaderboard
bool Leaderboard::isBestTime(unsigned long time) {
	return time >= bestTimes[0].time;
}

//Load le leaderboard d'une map en prenant en paramètre le nom de la map (nom du dossier). Retourne false si la map n'existe pas
bool Leaderboard::loadFromMap(string _mapName) {
	mapName = _mapName;

	ifstream file;
	file.open(".\\maps\\" + mapName + "\\leaderboard.lb");

	if (!file.is_open()) return false;

	file >> *this;

	return true;
}

//Retourne le nombre d'entrée de leaderboard qui sont non null
int Leaderboard::getLength() {
	for (int i = 0; i < 5; i++) {
		if (bestTimes[i].name.empty() && bestTimes[i].time <=0) return i + 1;
	}
	return 5;
}

//Sauvegarde le leaderboard dans un fichier. Retourne false si aucune map n'est sélectionnée ou si la map n'existe pas
bool Leaderboard::save() {
	if (mapName == "") return false;

	if (!filesystem::is_directory(".\\maps\\" + mapName)) return false;

	ofstream ofs(".\\maps\\" + mapName + "\\leaderboard.lb", ofstream::trunc);

	ofs << *this;

	return true;
}

//Lit un leaderboard à partir d'un stream
std::istream& operator>>(std::istream& is, Leaderboard& l) {
	
	for (int i = 0; i < 5; i++) {
		is >> l.bestTimes[i];
	}

	return is;
}

//Écrit un leaderBoard dans un stream
std::ostream& operator<<(std::ostream& os, const Leaderboard& l) {
	
	for (int i = 0; i < 5; i++) {
		os << l.bestTimes[i];
	}

	return os;
}
