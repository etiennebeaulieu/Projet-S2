#include "model_auto.h"
#include "model_circuit.h"
#include "best_time.h"
#include <fstream>


class ControllerMenu {

public:
	ControllerMenu();

	void printMenu();

	void openSettings();
	void startGame();
	void nextCar();
	void previousCar();
	void nextCircuit();
	void previousCircuit();
	void updateData();
	string printLeaderboard();


private:
	BestTime leaderboard[5];
	Model_auto carList[5];
	ModelCircuit circuitList[5];
	int currentCar;
	int currentCircuit;


};
