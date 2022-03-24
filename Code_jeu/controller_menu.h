#ifndef CONTROLLER_MENU_H
#define CONTROLLER_MENU_H

#include "model_auto.h"
#include "model_circuit.h"
#include "best_time.h"
#include "controller_course.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;


class ControllerMenu {

public:
	ControllerMenu();
	~ControllerMenu();

	void printMenu();

	void openSettings();
	void startGame();
	void nextCar();
	void previousCar();
	void nextCircuit();
	void previousCircuit();
	void updateData();
	std::string printLeaderboard();

	void gotoXY(int x, int y);

	void menuThread(int selected);


private:
	BestTime leaderboard[5];
	ModelAuto* carList[5];
	std::vector<ModelCircuit*> circuitList;
	int currentCar;
	int currentCircuit;
	Controller_course* controllerCourse;
	


};

#endif