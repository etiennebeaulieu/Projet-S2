#include <String>
#include "position.h"

class Model_auto {


public :
	Model_auto();
	Model_auto(int pSpeed, int pHandling, String pName);
	~Model_auto();

	void setSpeed(int pSpeed);
	int getSpeed();
	void setHandling(int pHandling);
	int getHandling();
	void setName(String pName);
	String getName();
	void setPostion(int x, int y);
	Position getPosition();

	


private:
	int speed;
	int handling;
	String name;

	Position position;



};


