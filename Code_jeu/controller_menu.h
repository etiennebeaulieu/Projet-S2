#include "model_auto.h"


class ControllerMenu {

public:
	ControllerMenu();

	void printMenu();
	void waitForAnswer();

	void openSettings();
	void startGame();
	void nextCar();
	void previousCar();


private:
	Model_auto carList[5];
	int currentCar;


};
