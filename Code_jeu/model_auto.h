#include <string>
#include <math.h>
#include "position.h"
using namespace std;


const float  PI = 3.14159265358979f;
const int DEFAULT_SPEED = 1;
const int DEFAULT_HANDLING = 1;
const string DEFAULT_NAME = "auto_base";

const float TURNING_RATIO = 1;
const float MOVEMENT_RATIO = 1;

class Model_auto {


public :
	Model_auto();
	Model_auto(int pSpeed, int pHandling, string pName);
	~Model_auto();

	void setSpeed(int pSpeed);
	int getSpeed();
	void setHandling(int pHandling);
	int getHandling();
	void setName(string pName);
	string getName();
	void setPostion(Position pPosition);
	Position getPosition();
	


	Position move(float pAngle, int pMovement);

	


private:
	int speed;
	int handling;
	string name;

	Position position;



};


