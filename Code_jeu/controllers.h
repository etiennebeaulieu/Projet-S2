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
#include "serial_communication.h"
#include "SerialPort.hpp"
#include <fstream>
#include <filesystem>
#include <vector>

using json = nlohmann::json;
#define BAUD 115200

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



	SerialPort* arduino;
	std::string raw_msg;
private:
	BestTime leaderboard[5];
	ModelAuto* carList[5];
	std::vector<ModelCircuit*> circuitList;
	int currentCar;
	int currentCircuit;
	int optionSelected;
	Controller_course* controllerCourse;
	



	// Structure de donnees JSON pour reception
	int bouton1 = 0;
	int bouton2 = 0;
	int bouton3 = 0;
	int bouton4 = 0;
	float joyStickX = 0;
	int joyStickY = 0;
	float acc_Value = 0;
	// Structure de donnees pour Envoie JSON
	int led_state_GREEN = 0;
	int led_state_RED1 = 0;
	int led_state_RED2 = 0;
	int led_state_RED3 = 0;
	long segment_Value = 0;
	int moteur_vibrant = 0;

	json j_msg_send, j_msg_rcv;



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
	bool move(float pAngle, int pMovement);

	void updateScreenConsole();
	void updateScreenGUI();

	void gotoXY(int x, int y);
	void demoConsole();


	void saveLeaderboard();


	static void menuThread(Controller_course* controller);
	static void courseThread(Controller_course* controller);

	SerialPort* arduino;
	std::string raw_msg;
	
private:
	ModelAuto car;
	ModelCircuit circuit;
	ControllerMenu* menuControleur;
	int optionSelected;
	int sorteControle = 0; //0 pour joystick, 1 pour accéléromère, autre pour clavier
	unsigned long time;
	int demo[1024][2];
	Timer timer;
	



	// Structure de donnees JSON pour reception
	int bouton1 = 0;
	int bouton2 = 0;
	int bouton3 = 0;
	int bouton4 = 0;
	float joyStickX = 0;
	int joyStickY = 0;
	float acc_Value = 0;
	// Structure de donnees pour Envoie JSON
	int led_state_GREEN = 0;
	int led_state_RED1 = 0;
	int led_state_RED2 = 0;
	int led_state_RED3 = 0;
	long segment_Value = 0;
	int moteur_vibrant = 0;

	json j_msg_send, j_msg_rcv;
};

#endif
