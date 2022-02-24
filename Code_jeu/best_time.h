#include <string>
using namespace std;
struct BestTime {
	string name;
	string time;
};

istream& operator>>(istream& is, BestTime& bestTime) {
	is >> bestTime.name >> bestTime.time;
}
ostream& operator<<(ostream& os, const BestTime& bestTime) {
	os << bestTime.name << " " << bestTime.time << endl;
}
