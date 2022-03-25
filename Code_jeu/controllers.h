#ifndef CONTROLLERS_H
#define CONTROLLERS_H
#include <Windows.h>
#include <thread>
#include <iostream>
#include <future>
#include "model_auto.h"
#include "model_circuit.h"
#include "position.h"
#include "timer.h"
#include "best_time.h"
#include <fstream>
#include <filesystem>
#include <vector>

class Controller_course;

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

	static void menuThread(ControllerMenu* controller);


private:
	BestTime leaderboard[5];
	ModelAuto* carList[5];
	std::vector<ModelCircuit*> circuitList;
	int currentCar;
	int currentCircuit;
	int optionSelected;
	Controller_course* controllerCourse;



};


class Controller_course {

public:
	Controller_course();
	Controller_course(ModelAuto* pCar, ModelCircuit* pCircuit, ControllerMenu* pControllerMenu);
	~Controller_course();

	void setAuto(ModelAuto pCar);
	ModelAuto getAuto();
	void setCircuit(ModelCircuit pCircuit);
	ModelCircuit getCircuit();

	void startRace();
	void move(float pAngle, int pMovement);

	void updateScreenConsole();
	void updateScreenGUI();

	void gotoXY(int x, int y);
	void demoConsole();


	void saveLeaderboard();


	static void menuThread(Controller_course* controller);
	void courseThread();

private:
	ModelAuto car;
	ModelCircuit circuit;
	ControllerMenu* menuControleur;
	int optionSelected;
	bool sorteControle = true;
	unsigned long time;
	int demo[1024][2];
	Timer timer;
};

#endif
