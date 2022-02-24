#include "model_auto.h"
#include "model_circuit.h"
#include "best_time.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
using namespace std;
namespace fs = std::filesystem;


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
	Model_auto* carList[5];
	vector<ModelCircuit*> circuitList;
	int currentCar;
	int currentCircuit;


};
